def read_input():
    n, m, l = (int(x) for x in input().split())
    cars = [int(x) for x in input().split()]
    spots = []
    for car in cars:
        spots.append((car - m, +1))
        spots.append((car + m + 1, -1))
    spots.append((0, 0))
    spots.append((l, 0))
    return l, sorted(spots)

l, spots = read_input()

def solve():
    s = len(spots)
    curr = 0
    i = 0
    while i < len(spots):
        x = spots[i][0]
        while i < len(spots) and spots[i][0] == x:
            curr += spots[i][1]
            i += 1
        # print("at", x, curr)
        if 0 <= x <= l:
            s = min(s, curr)
    return s

if __name__ == '__main__':
    print(solve())
