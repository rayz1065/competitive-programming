from random import randint, choice

n_nodes = randint(1, 10000)
q_queries = randint(10, 100)
operations = [0, 1, 2]
value_max = 100
numbers = [randint(-value_max, value_max) for i in range(n_nodes)]

print(n_nodes, q_queries)
print(' '.join(str(x) for x in numbers))
versions_count = 1

for i in range(q_queries):
    op = choice(operations)
    l = randint(0, n_nodes - 2)
    r = randint(l + 1, n_nodes - 1)
    if op == 0:
        # change values in [l, r)
        print(op, l, r, randint(-value_max, value_max))
        versions_count += 1
    elif op == 1:
        # reset to v
        v = randint(0, versions_count - 1)
        print(op, l, r, v)
        versions_count += 1
    else:
        print(op, l, r)
