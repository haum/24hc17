from random import randint
from sys import stdout

unmatched = []
copen = '{[(<'
cclose = '}])>'

for lin in range(80):
    for col in range(80):
        i = randint(0, 3)
        j = randint(0, 1)
        if j and len(unmatched) > 0:
            stdout.write(cclose[copen.find(unmatched[-1])])
            unmatched.pop()
        else:
            stdout.write(copen[i])
            unmatched.append(copen[i])
    stdout.write('\n')
stdout.write('\n')
print(len(unmatched))
for m in range(len(unmatched)):
    stdout.write(cclose[copen.find(unmatched[-1])])
    unmatched.pop()
stdout.write('\n')
