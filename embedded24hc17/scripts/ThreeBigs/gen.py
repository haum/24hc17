import sys
from random import randrange

# used to make ThreeBigs and ThreeBigsEviler (manual split)

nbup = 0
answer = ''
for i in range(20):
    position = randrange(0, 3*80-7)
    for j in range(3*80):
        letter_rank = randrange(2, 26)
        small = chr(ord('a') + letter_rank)
        big = chr(ord('A') + letter_rank)

        upper = randrange(0, 2)
        if (upper and nbup != 2 and j != position+3) or (j in (position, position+1, position+2, position+4, position+5, position+6)):
            nbup += 1
            sys.stdout.write(big)
        else:
            nbup = 0
            sys.stdout.write(small)
            if position+3 == j:
                answer += small

        if not (j+1) % 80:
            sys.stdout.write('\n')


print('')
print(answer)

