from random import choice,shuffle

# Create the path
letters = list(chr(ord('a') + i) for i in range(26)) + list(chr(ord('A') + i) for i in range(26))
path = list(set(choice(letters)+choice(letters)+choice(letters)+choice(letters) for i in range(50)))
shuffle(path)

pathfile = open("path_easy", "w")
for p in path:
    pathfile.write(p + '\n')
pathfile.close()

alea = (
    "The White Rabbit is gone to \"%s\"\n",
)

for i in range(len(path)-1):
    max_ph = min(int((i-50)/10)+1, len(alea))
    if i < 50: max_ph = 1
    f = open("node_%s"%path[i], "w")
    msg = choice(alea[0:max_ph])%path[i+1]
    print(msg)
    f.write(msg)
    f.close()

f = open("node_%s"%path[-1], "w")
f.write("Wait, I think the White Rabbit is gone to \"wonderland\"!\n")
f.close()
