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
V0 = randint(-100,100)
V1 = randint(-100,100)

list_u = list()
list_v = list()
#stdout.write(str(list_V[0]))

r = U1-U0
v = V1-V0
if (argument_test == 1):
    answer.write("r: "+str(r)+" ")
    answer.write("v: "+str(v)+"\n")
if (argument_test == 1):
    answer.close()

UN = U0
UN1 = UN+r
stdout.write("r: "+str(r)+"\n")
#if (argument_test == 1):
#    enigma.write(str(UN1)+" ")

VN = V0
VN1 = VN+v
stdout.write("v: "+str(v)+"\n")

list_u.insert(0, UN1)
stdout.write("Suite u: "+str(list_u[0])+" ")
UN = UN1
# On comment obligatoirement à partir de 1 ! Car U0 est déjà calculer au dessus
for i in range(1,4):
    UN1 = UN+r
    list_u.insert(i, UN1)
    stdout.write(str(list_u[i])+" ")
    #if (argument_test == 1):
    #    enigma.write(str(UN1)+" ")
    UN = UN1

stdout.write("\n")

list_v.insert(0, VN1)
stdout.write("Suite v: "+str(list_v[0])+" ")
VN = VN1
for z in range(1,4):
    VN1 = VN+v
    list_v.insert(z, VN1)
    stdout.write(str(list_v[z])+" ")
    VN = VN1

stdout.write("\n")

stdout.write("Mix: ")

for p in range(0,4):
    if (p % 2 == 0):
        stdout.write(str(list_v[p])+" ")
        if (argument_test == 1):
            enigma.write(str(list_v[p])+" ")
    else:
        stdout.write(str(list_u[p])+" ")
        if (argument_test == 1):
            enigma.write(str(list_u[p])+" ")

if (argument_test == 1):
    enigma.write("\n")
    enigma.close()
stdout.write("\n")
