import hashlib
import json
import re
import sys
from pathlib import Path

def remove_header(text):
    lines = text.splitlines(keepends=True)
    st = 0
    while st < len(lines) and not lines[st].strip():
        st += 1
    if st < len(lines) and lines[st].strip().startswith('/**'):
        while st < len(lines) and '*/' not in lines[st]:
            st += 1
        st += 1
        while st < len(lines) and not lines[st].strip():
            st += 1
    return ''.join(lines[st:])

def main():
    root = Path(__file__).resolve().parent
    document = root / (sys.argv[1] if len(sys.argv) > 1 else 'tn.tex')
    files = []
    for line in document.read_text(encoding='utf-8-sig').splitlines():
        if line.lstrip().startswith(r'\Algorithm'):
            files.extend(re.findall(r'\{(source/[^{}\r\n]+\.cpp)\}', line))
    files = list(dict.fromkeys(files))

    directory = root / 'build/stripped'
    directory.mkdir(parents=True, exist_ok=True)
    statefile = directory / 'state.json'
    version = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    state = json.loads(statefile.read_text(encoding='utf-8')) if statefile.exists() else {}
    dirty = state.get('version') != version
    if dirty:
        state = {'version': version, 'files': {}}

    changed = 0
    for name in files:
        src = root / name
        dst = directory / name
        stat = src.stat()
        stamp = [stat.st_mtime_ns, stat.st_ctime_ns, stat.st_size]
        if state['files'].get(name) == stamp and dst.exists():
            continue

        content = remove_header(src.read_text(encoding='utf-8-sig'))
        if not dst.exists() or dst.read_text(encoding='utf-8') != content:
            dst.parent.mkdir(parents=True, exist_ok=True)
            dst.write_text(content, encoding='utf-8')
            changed += 1
        state['files'][name] = stamp
        dirty = True

    if dirty:
        statefile.write_text(json.dumps(state, ensure_ascii=False), encoding='utf-8')
    print(f'teamnote: {len(files)} files, {changed} updated')

if __name__ == '__main__':
    main()