def read_input():
    input()
    return [int(x) for x in input().split()]

cells = read_input()

def solve(dice):
    pos = 0
    s = 0
    while pos < len(cells):
        if cells[pos] == 0:
            s += 1
            pos += dice
        else:
            pos += cells[pos]
    return s

if __name__ == '__main__':
    for i in range(1, 7):
        print(solve(i), end=' ')
    print()
