import os
import re

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

import html.parser
class ProblemHTMLParser(html.parser.HTMLParser):
    def __init__(self):
        super().__init__()
        self.problems = []
        self.current_problem = None
        self.in_problem = False
        self.in_header = False
        self.in_limits = False
        self.in_body = False
        self.in_h2 = False
        self.current_section = "description"
        
        self.desc_lines = []
        self.in_lines = []
        self.out_lines = []
        self.range_lines = []
        self.current_sample_in = []
        self.current_sample_out = []
        self.samples = []
        self.ignore_tags = ['img', 'script', 'style']
        self.ignore_level = 0
        self.temp_text = []

    def handle_starttag(self, tag, attrs):
        if tag in self.ignore_tags:
            self.ignore_level += 1
            return
            
        attr_dict = dict(attrs)
        classes = attr_dict.get('class', '').split()
        
        if tag == 'div' and 'problem' in classes:
            self.in_problem = True
            if self.current_problem is not None:
                self.finalize_problem()
            self.current_problem = {
                'num': 0, 'name': '未知', 'eng_id': 'prob',
                'time': '1.0秒', 'mem': '512 MiB'
            }
            self.current_section = "description"
            self.desc_lines = []
            self.in_lines = []
            self.out_lines = []
            self.range_lines = []
            self.samples = []
            self.current_sample_in = []
            self.current_sample_out = []
            
        if self.in_problem:
            if tag == 'h2' and 'problem-header' in classes:
                self.in_header = True
            elif tag == 'p' and 'limits' in classes:
                self.in_limits = True
            elif tag == 'div' and 'question-body' in classes:
                self.in_body = True
            elif self.in_body and tag in ['h2', 'h3']:
                self.in_h2 = True
                self.temp_text = []
                
        # Handle br and blocks to simulate newline
        if self.in_body and tag in ['br', 'p', 'div', 'li']:
            self.add_text('\n')

    def handle_endtag(self, tag):
        if tag in self.ignore_tags:
            self.ignore_level = max(0, self.ignore_level - 1)
            return
            
        if tag == 'div' and self.in_body:
            # We don't exactly track div depth but it's ok
            pass
            
        if self.in_problem:
            if tag == 'h2' and self.in_header:
                self.in_header = False
            elif tag == 'p' and self.in_limits:
                self.in_limits = False
            elif tag in ['h2', 'h3'] and self.in_h2:
                self.in_h2 = False
                title = "".join(self.temp_text).strip()
                if '输入格式' in title:
                    self.current_section = "input"
                elif '输出格式' in title:
                    self.current_section = "output"
                elif '样例输入' in title:
                    self.current_section = "sample_in"
                    if self.current_sample_in:
                        self.samples.append((self.current_sample_in.copy(), self.current_sample_out.copy()))
                        self.current_sample_in.clear()
                        self.current_sample_out.clear()
                elif '样例输出' in title:
                    self.current_section = "sample_out"
                elif '数据范围' in title or '子任务' in title or '评测用例' in title:
                    self.current_section = "range"
                self.temp_text = []

    def handle_data(self, data):
        if self.ignore_level > 0:
            return
            
        text = data.strip(' \t\r')
        if not text and '\n' not in data:
            return
            
        if self.in_problem:
            if self.in_header:
                # 提取题号和题名
                match = re.search(r'第\s*(\d+)\s*题[：:]\s*(.*?)(?:（|\()', text)
                if match:
                    self.current_problem['num'] = int(match.group(1))
                    self.current_problem['name'] = match.group(2).strip()
                    self.current_problem['eng_id'] = f"prob{match.group(1)}"
            elif self.in_limits:
                t_match = re.search(r'时间限制[：:]\s*(\d+)\s*ms', text)
                if t_match:
                    self.current_problem['time'] = f"{int(t_match.group(1)) / 1000.0}秒"
                m_match = re.search(r'空间限制[：:]\s*(\d+)\s*KB', text)
                if m_match:
                    self.current_problem['mem'] = f"{int(m_match.group(1)) // 1024} MiB"
            elif self.in_body:
                if self.in_h2:
                    self.temp_text.append(text)
                else:
                    self.add_text(text)
                    
    def add_text(self, text):
        # We split by \n and add non-empty
        lines = [x.strip() for x in text.split('\n') if x.strip()]
        for line in lines:
            if self.current_section == "description":
                if not self.desc_lines or line != self.desc_lines[-1]: # Deduplicate slightly
                    self.desc_lines.append(line)
            elif self.current_section == "input":
                self.in_lines.append(line)
            elif self.current_section == "output":
                self.out_lines.append(line)
            elif self.current_section == "sample_in":
                self.current_sample_in.append(line)
            elif self.current_section == "sample_out":
                self.current_sample_out.append(line)
            elif self.current_section == "range":
                self.range_lines.append(line)
                
    def finalize_problem(self):
        if self.current_sample_in or self.current_sample_out:
            self.samples.append((self.current_sample_in.copy(), self.current_sample_out.copy()))
            
        if self.current_problem:
            p = self.current_problem
            p['desc'] = "\n * ".join(self.desc_lines)
            p['in'] = "\n * ".join(self.in_lines)
            p['out'] = "\n * ".join(self.out_lines)
            p['range'] = "\n * ".join(self.range_lines)
            p['samples'] = self.samples
            self.problems.append(p)

    def close(self):
        if self.in_problem and self.current_problem:
            self.finalize_problem()
        super().close()


def parse_html(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            html_content = f.read()
            
        parser = ProblemHTMLParser()
        parser.feed(html_content)
        parser.close()
        return parser.problems
    except Exception as e:
        print(f"Error parsing {filepath}: {e}")
        return []

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
        for l in samples[0][0]:
            lines.append(" * " + l)
        lines.append(" * ")
        lines.append(" * 样例输出：")
        for l in samples[0][1]:
            lines.append(" * " + l)
    else:
        for i, (sin, sout) in enumerate(samples, 1):
            lines.append(f" * 样例输入{i}：")
            for l in sin:
                lines.append(" * " + l)
            lines.append(" * ")
            lines.append(f" * 样例输出{i}：")
            for l in sout:
                lines.append(" * " + l)
            lines.append(" * ")
            
    return "\n".join(lines)


def main():
    created_dirs = []
    created_files = []
    
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
                
                # Check user modifications
                if os.path.exists(file_path):
                    with open(file_path, 'r', encoding='utf-8') as f:
                        if 'cin >> n >> x >> y;' in f.read():
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
            # Fallback
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
    print("生成结束。可查看目录确认结果。")
    with open(os.path.join(CSP_DIR, 'py_finish.txt'), 'w', encoding='utf-8') as f:
        f.write("OK: created {} files".format(len(created_files)))

if __name__ == '__main__':
    main()
