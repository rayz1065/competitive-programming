from random import randint, shuffle
n = 100000
m = n - 1
k = 100
max_w = 100000
print(n, m, k)
print(' '.join(str(randint(0, max(0, i - 1))) for i in range(0, n)))
nodes_with_fruit = list(range(1, n))
shuffle(nodes_with_fruit)
for v in nodes_with_fruit[:m]:
    d, w = randint(1, k), randint(1, max_w)
    print(v, d, w)