from random import randint
n = 49

print(n)
for i in range(n):
    print(' '.join(str(randint(0, 10000)) for _ in range(n)))
