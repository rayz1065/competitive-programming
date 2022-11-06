from random import randint

n = 9000
m = 100

print(n, m)
for i in range(n):
    print(''.join(str(randint(0, 1)) for _ in range(m)))
