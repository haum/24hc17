#Usage exemple: python gen.py code24hc17 2
#The file output is answer2 and enigma2

from sys import stdout
from random import randint
from sys import argv
import os

generate_file = argv
argument_test = 0

try:
    generate_file = argv[1]
    number_of_file = argv[2]
    if (os.path.isdir(str(generate_file))):
        argument_test = 1
        answer_path_file = str(generate_file)+"/answer"+str(number_of_file)
        enigma_path_file = str(generate_file)+"/enigma"+str(number_of_file)
    else:
        stdout.write("The folder doesn't exist !\n")

except IndexError:
    stdout.write("If you want to generate the files, you have to add the path.\n")
    stdout.write("Example: python gen.py code24hc17/enigme\n")

if (argument_test == 1):
    answer = open(answer_path_file, 'w')
    enigma = open(enigma_path_file, 'w')

U0 = randint(-100,100)
U1 = randint(-100,100)

r = U1-U0
if (argument_test == 1):
    answer.write(str(r)+"\n")
if (argument_test == 1):
    answer.close()

UN = U0
UN1 = UN+r
stdout.write(str(r)+"\n")
stdout.write(str(UN1)+" ")
if (argument_test == 1):
    enigma.write(str(UN1)+" ")

UN = UN1
# On comment obligatoirement à partir de 1 ! Car U0 est déjà calculer au dessus
for i in range(1,randint(2,20)):
    UN1 = UN+r
    stdout.write(str(UN1)+" ")
    if (argument_test == 1):
        enigma.write(str(UN1)+" ")
    UN = UN1

stdout.write("\n")
if (argument_test == 1):
    enigma.write("\n")
    enigma.close()
