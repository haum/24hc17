from random import randint, shuffle
from sys import stdout
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

ru = randint(-100,100)
rv = randint(-100,100)
u0 = randint(-100,100)
v0 = randint(-100,100)


u = list(u0+i*ru for i in range(50))
v = list(v0+i*rv for i in range(50))

z = u+v
shuffle(z)

for o in z:
    stdout.write(str(o)+" ")
    if (argument_test == 1):
        enigma.write(str(o)+" ")

if (argument_test == 1):
    enigma.write("\n")
stdout.write("\nru: "+str(ru)+";rv: "+str(rv))
if (argument_test == 1):
    answer.write("ru: "+str(ru)+" "+";rv: "+str(rv)+"\n")
    answer.close()
    enigma.close()
