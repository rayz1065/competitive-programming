from random import randint

n = 1000
print(n)
print(' '.join(str(randint(0, 1000)) for _ in range(n)))