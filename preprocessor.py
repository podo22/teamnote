import sys
import os

def remove_header(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except Exception as e:
        return f"Error reading file: {str(e)}"

    if not lines: return ""

    st = 0
    while st < len(lines) and not lines[st].strip(): st += 1
    
    if st < len(lines) and lines[st].strip().startswith('/**'):
        while st < len(lines) and '*/' not in lines[st]: st += 1
        st += 1
        while st < len(lines) and not lines[st].strip(): st += 1
    return ''.join(lines[st:])

if __name__ == '__main__':
    with open("python_debug.log", "a", encoding="utf-8") as log:
        log.write(f"Input: {sys.argv[1]}, Output: {sys.argv[2]}\n")

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    
    content = remove_header(input_file)
    
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(content)