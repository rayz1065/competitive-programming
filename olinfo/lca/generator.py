from random import randint, choice

num_range = 10**9
n, q, t = 1000, 2000, 2
print(n, q, t)

for i in range(1, n):
    a = i
    b = randint(0, i - 1)
    print(a, b, randint(-num_range, num_range))

for i in range(q):
    a, b = randint(0, n - 1), randint(0, n - 1)
    if a == b:
        a = (a + 1) % n
    print(a, b)
