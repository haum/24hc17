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
#v = list(v0+i*rv for i in range(50))

#z = u+v
#shuffle(z)

false_value_rand = randint(0,49)
a = 0
for o in u:
    a += 1
    if (a == false_value_rand):
        if (a == 0):
            false_value_rand = -1
        false_value = o+false_value_rand
        stdout.write(str(false_value)+" ")
        if argument_test == 1:
            enigma.write(str(false_value)+" ")
    else:
        stdout.write(str(o)+" ")
    if (argument_test == 1):
        enigma.write(str(o)+" ")

if (argument_test == 1):
    enigma.write("\n")
stdout.write("\nIntru: "+str(false_value)+"\n")

if (argument_test == 1):
    answer.write(str(false_value)+"\n")
    answer.close()
    enigma.close()
