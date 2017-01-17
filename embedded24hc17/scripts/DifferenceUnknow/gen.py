#Usage exemple: python gen.py code24hc17 2
#The file output is enigma2 and enigma2

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
        enigma_path_file = str(generate_file)+"/enigma"+str(number_of_file)
        answer_path_file = str(generate_file)+"/answer"+str(number_of_file)
    else:
        stdout.write("The folder doesn't exist !\n")

except IndexError:
    stdout.write("If you want to generate the files, you have to add the path.\n")
    stdout.write("Example: python gen.py code24hc17/enigme\n")

if (argument_test == 1):
    enigma = open(enigma_path_file, 'w')
    answer = open(answer_path_file, 'w')

U0 = randint(-100,100)
U1 = randint(-100,100)

list_u = list()

r = U1-U0
#if (argument_test == 1):
#    answer.write("r: "+str(r)+" ")
#    answer.write("v: "+str(v)+"\n")
#if (argument_test == 1):
#    answer.close()

UN = U0
UN1 = UN+r
#stdout.write("r: "+str(r)+"\n")
#if (argument_test == 1):
#    enigma.write(str(UN1)+" ")

list_u.insert(0, UN1)
#stdout.write("Suite u: "+str(list_u[0])+" ")
UN = UN1
# On comment obligatoirement à partir de 1 ! Car U0 est déjà calculer au dessus
for i in range(1,100):
    UN1 = UN+r
    list_u.insert(i, UN1)
    #stdout.write(str(list_u[i])+" ")
    #if (argument_test == 1):
    #    enigma.write(str(UN1)+" ")
    UN = UN1

stdout.write("Answer: ")
for p in range(0,100):
    stdout.write(str(list_u[p])+" ")

false_value_rand = randint(0,99)
stdout.write("\nEnigma: ")
for z in range(0,100):
    if (z == false_value_rand):
        if (z == 0):
            false_value_rand = -1
        false_value = list_u[z]+false_value_rand
        stdout.write(" "+str(false_value)+" ")
    else:
        stdout.write(str(list_u[z])+" ")


#if (argument_test == 1):
#    enigma.write("\n")
#    enigma.close()
stdout.write("\n")
