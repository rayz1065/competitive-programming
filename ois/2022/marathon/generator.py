from random import randint, choice, shuffle
n = 2500
q = 50

print(n, q)
nodes = list(range(1, n))
branches = []

for i in range(1, n):
    x = i + 1
    y = randint(0, i - 1) + 1
    branches.append((x, y))
    print(x, y)
for _ in range(q):
    action = randint(1, 2)
    if action == 1:
        x, y = choice(branches)
        print(action, x, y)
    else:
        shuffle(nodes)
        x, y = nodes[:2]
        print(action, x, y)
