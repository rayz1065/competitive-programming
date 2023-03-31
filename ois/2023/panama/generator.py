from random import randint

n = 100000
q = 100000
print(n, q)
print(' '.join(str(randint(0, 10**3)) for _ in range(n)))
for _ in range(q):
    q = randint(1, 2)
    if q == 1:
        a = randint(1, n)
        b = randint(0, 1000)
        print(q, a, b)
    else:
        a = randint(1, n)
        b = randint(1, n)
        if b < a:
            a, b = b, a
        print(q, a, b)
