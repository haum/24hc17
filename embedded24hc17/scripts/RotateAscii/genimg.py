from random import randrange
import sys

for i in range(20):
    for j in range(20):
        letter_rank = randrange(0, 26)
        small = chr(ord('a') + letter_rank)
        big = chr(ord('A') + letter_rank)
        upper = randrange(0, 2)
        if upper:
            sys.stdout.write(big)
        else:
            sys.stdout.write(small)
    sys.stdout.write('\n')
