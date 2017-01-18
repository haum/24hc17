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

def get_number_alea():
    if u[6] < v[6]:
        number_alea = randint(u[6],v[6])
    else:
        number_alea = randint(v[6],u[6])
    return number_alea


the_number_alea = get_number_alea()
for a in u:
    #stdout.write(str(a)+" ")
    if a == get_number_alea:
        stdout.write("error")
        the_number_alea = get_number_alea()

u_num_alea = the_number_alea
u.insert(randint(1,49), str(the_number_alea))

the_number_alea = get_number_alea()
for b in v:
    #stdout.write(str(a)+" ")
    if b == get_number_alea:
        stdout.write("error")
        the_number_alea = get_number_alea()

v_num_alea = the_number_alea
v.insert(randint(1,49), str(the_number_alea))



z = u+v
shuffle(z)

stdout.write("Enigma: \n")
for c in z:
    stdout.write(str(c)+" ")
    if argument_test == 1:
        enigma.write(str(c)+" ")
stdout.write("\nAnswer: \nu: "+str(u_num_alea)+";v: "+str(v_num_alea)+"\n")
if argument_test == 1:
    answer.write("u: "+str(u_num_alea)+";v: "+str(v_num_alea)+"\n")
    answer.close()
    enigma.close()
