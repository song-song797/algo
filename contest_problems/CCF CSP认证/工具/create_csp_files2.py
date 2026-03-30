import os
import re
from bs4 import BeautifulSoup

# Base directory
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
CSP_DIR = os.path.dirname(SCRIPT_DIR)
BASE_DIR = os.path.join(CSP_DIR, 'round01')
HTML_DIR = os.path.join(CSP_DIR, '题目说明')

def get_html_filename(exam_num):
    pattern = re.compile(f'^第{exam_num:02d}次.*\.html$')
    for filename in os.listdir(HTML_DIR):
        if pattern.match(filename):
            return filename
    return None

def clean_text(element):
    """提取纯文本，处理特殊标签"""
    if not element:
        return ""
    
    # 移除图片
    for img in element.find_all('img'):
        img.decompose()
        
    text = element.get_text(separator='\n', strip=True)
    return text

def parse_html(filepath):
    """解析 HTML 文件提取题目信息"""
    with open(filepath, 'r', encoding='utf-8') as f:
        soup = BeautifulSoup(f.read(), 'html.parser')
        
    problems = []
    
    for div in soup.find_all('div', class_='problem'):
        # 1. 解析标题
        header = div.find('h2', class_='problem-header')
        if not header:
            continue
            
        header_text = header.get_text(strip=True)
        # 格式如：第 1 题：正态分布（100 分）
        match = re.search(r'第\s*(\d+)\s*题[：:]\s*(.*?)(?:（|\()', header_text)
        if not match:
            continue
            
        prob_num = int(match.group(1))
        name = match.group(2).strip()
        
        # 2. 解析限制
        limits_p = div.find('p', class_='limits')
        time_limit = "1.0秒"
        mem_limit = "512 MiB"
        if limits_p:
            limits_text = limits_p.get_text(strip=True)
            # 时间限制：1000 ms　|　空间限制：524288 KB
            t_match = re.search(r'时间限制[：:]\s*(\d+)\s*ms', limits_text)
            if t_match:
                time_limit = f"{int(t_match.group(1)) / 1000.0}秒"
                
            m_match = re.search(r'空间限制[：:]\s*(\d+)\s*KB', limits_text)
            if m_match:
                mem_limit = f"{int(m_match.group(1)) // 1024} MiB"
                
        # 3. 提取详细描述
        body = div.find('div', class_='question-body')
        description = ""
        input_format = ""
        output_format = ""
        samples = []
        data_range = ""
        
        if body:
            current_section = "description"
            desc_lines = []
            in_lines = []
            out_lines = []
            range_lines = []
            
            # 由于可能有多组样例，我们用列表保存
            current_sample_in = []
            current_sample_out = []
            
            for child in body.children:
                if child.name in ['h2', 'h3']:
                    title = child.get_text(strip=True)
                    if '输入格式' in title:
                        current_section = "input"
                    elif '输出格式' in title:
                        current_section = "output"
                    elif '样例输入' in title:
                        current_section = "sample_in"
                        if current_sample_in:
                            samples.append((current_sample_in, current_sample_out))
                            current_sample_in = []
                            current_sample_out = []
                    elif '样例输出' in title:
                        current_section = "sample_out"
                    elif '数据范围' in title or '子任务' in title or '评测用例' in title:
                        current_section = "range"
                    else:
                        pass
                else:
                    try:
                        text = clean_text(child)
                    except Exception:
                        continue
                    if not text:
                        continue
                        
                    if current_section == "description":
                        desc_lines.append(text)
                    elif current_section == "input":
                        in_lines.append(text)
                    elif current_section == "output":
                        out_lines.append(text)
                    elif current_section == "sample_in":
                        current_sample_in.append(text)
                    elif current_section == "sample_out":
                        current_sample_out.append(text)
                    elif current_section == "range":
                        range_lines.append(text)
            
            if current_sample_in or current_sample_out:
                samples.append((current_sample_in, current_sample_out))
                
            description = "\n * ".join(desc_lines)
            input_format = "\n * ".join(in_lines)
            output_format = "\n * ".join(out_lines)
            data_range = "\n * ".join(range_lines)
            
        # 推断英文标识
        # 这里用拼音首字母不好用，由于环境可能没装 `pypinyin`，我们用基于题名的固定或简单推断，或者统一标识
        eng_id = f"prob{prob_num}"
            
        problem_data = {
            'num': prob_num,
            'name': name,
            'eng_id': eng_id,
            'time': time_limit,
            'mem': mem_limit,
            'desc': description,
            'in': input_format,
            'out': output_format,
            'samples': samples,
            'range': data_range
        }
        problems.append(problem_data)
        
    return problems

# Template
CPP_FULL_TEMPLATE = """/*
 * {name} ({eng_id})
 * CCF CSP 第{exam_num}次认证 真题{prob_num}
 * 时间限制: {time}  内存限制: {mem}
 *
 * 题目描述：
 * {desc}
 *
 * 输入格式：
 * {inf}
 *
 * 输出格式：
 * {outf}
 *
{samples_text}
 *
 * 数据范围：
 * {range}
 */

#include <iostream>
using namespace std;
int main() {{

  return 0;
}}
"""

CPP_SIMPLE_TEMPLATE = """/*
 * {name} ({eng_id})
 * CCF CSP 第{exam_num}次认证 真题{prob_num}
 */

#include <iostream>
using namespace std;
int main() {{

  return 0;
}}
"""

def generate_samples_text(samples):
    if not samples:
        return ""
    
    lines = []
    if len(samples) == 1:
        lines.append(" * 样例输入：")
        for l in samples[0][0].split('\\n'):
            lines.append(" * " + l)
        lines.append(" * ")
        lines.append(" * 样例输出：")
        for l in samples[0][1].split('\\n'):
            lines.append(" * " + l)
    else:
        for i, (sin, sout) in enumerate(samples, 1):
            lines.append(f" * 样例输入{i}：")
            for l in sin.split('\\n'):
                lines.append(" * " + l)
            lines.append(" * ")
            lines.append(f" * 样例输出{i}：")
            for l in sout.split('\\n'):
                lines.append(" * " + l)
            lines.append(" * ")
            
    return "\n".join(lines)


def main():
    created_dirs = []
    created_files = []
    
    # From 11 to 20
    for exam_num in range(20, 10, -1):
        prefix = 41 - exam_num
        dir_name = f'{prefix}_第{exam_num}次'
        dir_path = os.path.join(BASE_DIR, dir_name)
        
        os.makedirs(dir_path, exist_ok=True)
        created_dirs.append(dir_name)
        
        html_file = get_html_filename(exam_num)
        
        if html_file:
            print(f"Parsing {html_file}...")
            filepath = os.path.join(HTML_DIR, html_file)
            problems = parse_html(filepath)
            
            for p in problems:
                filename = f"{p['num']}_{p['name']}_{p['eng_id']}.cpp"
                file_path = os.path.join(dir_path, filename)
                
                # Check if it's already modified by user, skip if user wrote something meaningful
                if os.path.exists(file_path):
                    with open(file_path, 'r', encoding='utf-8') as f:
                        if 'cin >> n >> x >> y;' in f.read():
                            print(f"Skipping modified file {file_path}")
                            continue
                            
                samples_text = generate_samples_text(p['samples'])
                
                content = CPP_FULL_TEMPLATE.format(
                    name=p['name'], eng_id=p['eng_id'],
                    exam_num=exam_num, prob_num=p['num'],
                    time=p['time'], mem=p['mem'],
                    desc=p['desc'], inf=p['in'], outf=p['out'],
                    samples_text=samples_text, range=p['range']
                )
                
                with open(file_path, 'w', encoding='utf-8') as f:
                    f.write(content)
                created_files.append(os.path.join(dir_name, filename))
        else:
            print(f"Warning: HTML file not found for Exam {exam_num}")
            # Fallback to simple template
            for p_num in range(1, 6):
                name = f"题{p_num}"
                eng_id = f"prob{p_num}"
                filename = f"{p_num}_{name}_{eng_id}.cpp"
                file_path = os.path.join(dir_path, filename)
                
                if os.path.exists(file_path):
                    continue
                    
                content = CPP_SIMPLE_TEMPLATE.format(
                    name=name, eng_id=eng_id,
                    exam_num=exam_num, prob_num=p_num
                )
                with open(file_path, 'w', encoding='utf-8') as f:
                    f.write(content)
                created_files.append(os.path.join(dir_name, filename))

    print(f"\n=== 创建完成 ===")
    print(f"创建了 {len(created_dirs)} 个目录和 {len(created_files)} 个文件\n")
    print("目录结构：")
    for d in created_dirs:
        print(f"  {d}/")
        files_in_dir = [f for f in created_files if f.startswith(d)]
        for f in files_in_dir:
            print(f"    {os.path.basename(f)}")

if __name__ == '__main__':
    main()
