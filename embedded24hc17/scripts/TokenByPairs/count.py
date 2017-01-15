import sys
from pprint import pprint

tokens = {}

while True:
    line = sys.stdin.readline()
    if not line: break
    line = line.strip()

    s = line.split(' ')
    for tok in s:
        if tok in tokens:
            tokens[tok] = tokens[tok] + 1
        else:
            tokens[tok] = 1

pprint(tokens)
