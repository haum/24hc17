from random import randint, choice

a=randint(2**17, 2**30)
b=randint(2**17, 2**30)
a*=choice((-1,1))
b*=choice((-1,1))

print(a, '*', b)
print(a*b)
