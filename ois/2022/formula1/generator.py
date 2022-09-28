from random import randint

n = 2000
q = 50000

print(n)
for i in range(n):
    print(randint(0, 10**6), randint(0, 10**6), randint(0, 10**6))

print(q)
for i in range(q):
    print(randint(1, n), randint(1, 10**6))
