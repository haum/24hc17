import sys

tobesorted = []
while True:
    line = sys.stdin.readline()
    if not line: break
    tobesorted.append(line.strip())

def rev(seq):
    revd = []
    for a in seq:
        revd.append(a[-1::-1])
    return revd

tobesorted = rev(tobesorted)
tobesorted = sorted(tobesorted)
tobesorted = rev(tobesorted)

for a in tobesorted:
    sys.stdout.write(a + '\n')
