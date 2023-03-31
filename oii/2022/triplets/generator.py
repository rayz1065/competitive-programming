from random import choice, randint

n = randint(100, 200)
found = [0]

print(n)
for i in range(1, n):
    print(choice(found), i)
    found.append(i)
