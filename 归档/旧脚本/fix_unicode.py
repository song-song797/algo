import os, re

filepath = os.path.join(os.path.dirname(os.path.abspath(__file__)), 
    'CCF CSP认证', '1_第40次', '3_图片解码1_decode.cpp')

with open(filepath, 'rb') as f:
    data = f.read()

text = data.decode('utf-8')

# Find all non-ASCII chars
for i, ch in enumerate(text):
    if ord(ch) > 127:
        line_num = text[:i].count('\n') + 1
        print(f"Line {line_num}: U+{ord(ch):04X} ({repr(ch)})")

# Replace ALL non-ASCII with space (for a pure C++ file this is safe)
cleaned = re.sub(r'[^\x00-\x7E]', ' ', text)

with open(filepath, 'wb') as f:
    f.write(cleaned.encode('ascii'))

print("\nDone! All non-ASCII characters removed.")
