def read_input():
    n = int(input())
    return [tuple(int(x) for x in input().split())
                         for i in range(n)]

def solve():
    neigh = {}
    stars_in_x = {}
    s = 0
    for x, y in stars:
        neigh.setdefault(y, -1)
        neigh[y] += 1
        stars_in_x.setdefault(x, [])
        stars_in_x[x].append(y)
    for x, ys in stars_in_x.items():
        total_neigh = sum(neigh[y] for y in ys)
        for edge_y in ys:
            s += total_neigh - neigh[edge_y]
    return s

stars = read_input()

if __name__ == '__main__':
    print(solve())
