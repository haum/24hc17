import sys

while True:
    line = sys.stdin.readline()
    if not line: break

    sys.stdout.write(line.strip()[-1::-1] + '\n')
