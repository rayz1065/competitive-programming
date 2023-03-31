from random import randint, choice

n = 100000
q = 100000

def era (maxp):
    is_prime = [True] * maxp
    is_prime[0] = False
    is_prime[1] = False
    for i in range(2, maxp):
        if not is_prime[i]:
            continue
        for j in range(i * i, maxp, i):
            is_prime[j] = False
    return is_prime

primes = [i for i, isp in enumerate(era(10 ** 2)) if isp]
values = [choice(primes) for _ in range(n)]
print(n)
print(' '.join(str(x) for x in values))
for i in range(1, n):
    v = randint(0, i - 1)
    print(i + 1, v + 1)
print(q)
for i in range(q):
    u, v = randint(0, n - 1), randint(0, n - 1)
    print(u + 1, v + 1)

