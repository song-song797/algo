import os
import re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
CSP_DIR = os.path.dirname(SCRIPT_DIR)
BASE_DIR = os.path.join(CSP_DIR, 'round01')

def process_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    # Match the block comment
    match = re.search(r'/\*.*?\*/', content, flags=re.DOTALL)
    if not match:
        return

    comment_block = match.group(0)
    
    # Check if there is " * 题目描述：" or similar detailed sections
    # Find the limit line to keep
    limit_match = re.search(r'( \*\s*时间限制:.*?内存限制:.*?)\n', comment_block)
    
    new_comment = comment_block
    if '题目描述：' in comment_block:
        # Reconstruct comment block up to time/mem limit or title
        lines = comment_block.split('\n')
        keep_lines = []
        for line in lines:
            if '题目描述：' in line:
                break
            keep_lines.append(line)
        # Ensure it ends with */
        if not keep_lines[-1].strip() == '*/':
            keep_lines.append(' */')
        new_comment = '\n'.join(keep_lines)
        
    code_part = content[match.end():].strip()
    
    # Check if code part is exactly the template
    template_code1 = """#include <iostream>\nusing namespace std;\nint main() {\n\n  return 0;\n}"""
    template_code2 = """#include <iostream>\r\nusing namespace std;\r\nint main() {\r\n\r\n  return 0;\r\n}"""
    
    is_empty_template = code_part.replace(' ', '').replace('\n', '').replace('\r', '') == "#include<iostream>usingnamespacestd;intmain(){return0;}"
    
    new_content = new_comment + "\n"
    if not is_empty_template:
        new_content += "\n" + content[match.end():].lstrip('\n\r')
        
    if new_content != content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"Updated: {filepath}")

def main():
    for root, dirs, files in os.walk(BASE_DIR):
        # Skip 题目说明 or other non-exam dirs if needed, though exam dirs start with number
        for file in files:
            if file.endswith('.cpp'):
                process_file(os.path.join(root, file))
                
if __name__ == '__main__':
    main()
