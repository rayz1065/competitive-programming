from random import randint, choice

n = 10000
m = 10000
wages = [randint(50, 1000) for _ in range(n)]
parent = [0] * n

for i in range(1, n):
    parent[i] = randint(0, i - 1)

print(n, m)
print(wages[0])
for i in range(1, n):
    print(wages[i], parent[i] + 1)
parents = list(set(parent))

for i in range(m):
    if randint(0, 1) == 0:
        # change wages
        print('p', choice(parents) + 1, randint(-1000, 1000))
    else:
        # query
        print('q', randint(0, n - 1) + 1)
