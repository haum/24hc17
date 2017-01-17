from random import randint
from RomanProblems import *
import sys

def main():
    number1 = randint(10 ** 8, 10 ** 14)
    number2 = randint(10 ** 6, number1)
    longRoman1 = computeLongRoman(number1)
    longRoman2 = computeLongRoman(number2)

    operation = randint(0, 5)
    if operation == 0:
        operator = '+'
        number3 = number1 + number2
    elif operation == 1:
        operator = '-'
        number3 = number1 - number2
    elif operation == 2:
        operator = '*'
        number3 = number1 * number2
    elif operation == 3:
        operator = '//'
        number3 = number1 / number2
    else:
        operator = '%'
        number3 = number1 % number2

    longRoman3 = concatenateLongRomans(longRoman1, operator, longRoman2)
    longRoman4 = computeLongRoman(number3)

    print number1, operator, number2, '=', number3

    printLongRoman(longRoman3)
    printLongRoman(longRoman4)

    sys.stdout = open('enigma', 'w')
    printLongRoman(longRoman3)
    sys.stdout.close()
    sys.stdout = open('answer', 'w')
    printLongRoman(longRoman4)
    sys.stdout.close()


main()