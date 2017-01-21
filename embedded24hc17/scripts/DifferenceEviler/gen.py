#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# eviler.py
#
# Copyright © 2017 Mathieu Gaborit (matael) <mathieu@matael.org>
#
# Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
# Mathieu (matael) Gaborit wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer or coffee in return
#

"""

"""

import random
import sys

numenigm = sys.argv[1]

U  = random.randint(-1000,1000)
V = random.randint(-1000,1000)

qU  = random.randint(-100,100)
qV = random.randint(-100,100)
raisons = [qU, qV]

def next_u():
    global U
    U += qU
    return U

def next_v():
    global V
    V += qV
    return V

suites = [next_u, next_v]

final = [random.choice(suites)() for _ in range(200)]

with open('enigma%s'%(numenigm,), 'w') as fh:
    fh.write(' '.join(map(str, final)))
    fh.write('\n')

with open('answer%s'%(numenigm,), 'w') as fh:
    fh.write(' '.join(map(str, sorted(raisons))))
    fh.write('\n')


