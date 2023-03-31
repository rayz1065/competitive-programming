from random import randint

n = randint(10, 20)
m = randint(n, 2 * n)
print(n, m)
for i in range(n):
    print(i, i)
for i in range(m - n):
    a = randint(0, n - 1)
    b = randint(0, n - 1)
    if a == b:
        b += 1
    print(a, b)
