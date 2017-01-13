#coding utf8

from math import log10
from romanify import arabic2roman

def computeLongRoman(number):
    # Computing output size and initializing data slongRomanture 
    puissance = int(log10(number))
    if puissance > 3:
        n_lin = puissance / 3 + 1 * (puissance % 3 != 0) - 1
    else:
        n_lin = 0
    longRoman = [['' for j in xrange(0, puissance + 1)] for i in xrange(0, n_lin + 1)]

    # Computing under the thousand
    remainder = number % 1000     # part to compute
    numby = number - remainder    # non-treated part

    longRoman[n_lin][0] = arabic2roman(remainder)

    # Computing powers above
    for i in xrange(3, puissance + 1):
        remainder = int(numby % 10 ** (i + 1))
        numby -= remainder
        if remainder > 0:
            figure = remainder / 10 ** (3 * ((i) / 3))
            longRoman[n_lin][i] = arabic2roman(figure)
        else:
            longRoman[n_lin][i] = ''

    for i in xrange(0, puissance + 1):
        for j in xrange(0, i / 3):
            m = n_lin - 1 - j
            longRoman[m][i] = '_' * len(longRoman[n_lin][i])
        for j in xrange(0, n_lin - i / 3):
            longRoman[j][i] = ' ' * len(longRoman[n_lin][i])

    # treating Ms
    for i in xrange(3, puissance + 1):
        for j in xrange(0, len(longRoman[n_lin][i])):
                if longRoman[n_lin][i][j] == 'I':
                    chain = longRoman[n_lin][i]
                    longRoman[n_lin][i] = chain[:j] + 'M' + chain[j + 1:]
                    chain = longRoman[n_lin - i / 3][i]
                    longRoman[n_lin - i / 3][i] = chain[:j] + ' ' + chain[j + 1:]
    return longRoman


def printLongRoman(longRoman):
    n_lin = len(longRoman)
    puissance = len(longRoman[0]) - 1

    for i in xrange(0, n_lin):
        res = ''
        for j in xrange(puissance, -1, -1):
            res += longRoman[i][j]
        print res


def concatenateLongRomans(longRoman1, operator, longRoman2):
    n_lin1 = len(longRoman1)
    puissance1 = len(longRoman1[0]) - 1
    n_lin2 = len(longRoman2)
    puissance2 = len(longRoman2[0]) - 1

    oplen = len(operator)

    puissance3 = puissance1 + (puissance2 + 1) + oplen
    n_lin3 = max(n_lin1, n_lin2)
    longRoman3 = [[' ' for j in xrange(0, puissance3 + 1)] for i in xrange(0, n_lin3)]

    for i in xrange(1, n_lin2 + 1):
        for j in xrange(0, puissance2 + 1):
            longRoman3[n_lin3 - i][j] = longRoman2[n_lin2 - i][j]

    for j in xrange(0, oplen):
        longRoman3[n_lin3 - 1][puissance2 + 1 + j] = operator[j]

    for i in xrange(1, n_lin1 + 1):
        for j in xrange(0, puissance1 + 1):
            longRoman3[n_lin3 - i][puissance2 + oplen + 1 + j] = longRoman1[n_lin1 - i][j]

    return longRoman3