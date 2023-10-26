from random import randint

def make_graph():
    edges = set()
    while len(edges) < m:
        a = len(edges) if len(edges) < n else randint(0, n - 1)
        b = randint(0, n - 1)
        if a == b:
            continue
        if a > b:
            a, b = b, a

        edges.add(( a, b ))

    return edges

n = 100000
m = 200000
q = 100000
print(n, m, q)

print(' '.join(f'{randint(0, 10**8)}' for _ in range(q)))

edges = make_graph()

for a, b in edges:
    print(a, b, randint(0, 10**8))
