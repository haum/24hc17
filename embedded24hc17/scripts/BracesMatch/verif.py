from sys import stdout, stdin

unmatched = []
copen = '{[(<'
cclose = '}])>'

for line in stdin:
    for m in line:
        if m in copen:
            unmatched.append(m)
        elif len(unmatched) > 0 and cclose[copen.find(unmatched[-1])] == m:
            unmatched.pop()
        elif m != '\n':
            print('oups')

for m in range(len(unmatched)):
    stdout.write(cclose[copen.find(unmatched[-1])])
    unmatched.pop()
stdout.write('\n')
