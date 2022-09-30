def read_input():
    return tuple(int(x) for x in input().split())

n, m, e = read_input()

s = max(e % i for i in range(m, n + 1))
print(s)
