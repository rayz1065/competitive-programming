from itertools import tee

def pairwise(it):
    a, b = tee(it)
    next(b)
    return zip(a, b)

def read_input():
    n = int(input())
    return (tuple(int(x) for x in input().split())
                         for _ in range(n))

columns = read_input()

def solve():
    for ab1, ab2 in pairwise(columns):
        if ab1[0] > ab2[1] or ab1[1] < ab2[0]:
            return "NO"
    return "YES"

if __name__ == '__main__':
    print(solve())
