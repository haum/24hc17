import sys

img = []
while True:
    line = sys.stdin.readline()
    if not line: break
    img.append(line[0:-1])

out = ["" for i in img[0]]
for line in img:
    for j in range(len(line)):
        out[j] += line[j]
out = out[-1::-1]

print("\n".join(out))
