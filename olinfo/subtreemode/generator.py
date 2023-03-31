from random import randint

n = 1000000
color_count = n
print(n)
print(' '.join(str(randint(0, node - 1)) for node in range(1, n)))
print(' '.join(str(randint(0, color_count - 1)) for node in range(n)))
