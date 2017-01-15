import sys, re

text = ""
while True:
    line = sys.stdin.readline()
    if not line: break
    text = text + line.strip()

text = re.sub(r'^.*"(.*)".*"(.*)".*$', '\\1\\2', text)
for c in text:
    sys.stdout.write("%02X" % (ord(c),))
sys.stdout.write('\n')
