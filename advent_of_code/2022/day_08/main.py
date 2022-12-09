def read_input ():
    lines = []
    try:
        while True:
            line = input()
            lines.append([int(x) for x in line])
    except EOFError:
        pass
    return lines

MOV_R = [ -1, 0, 1, 0 ]
MOV_C = [ 0, 1, 0, -1 ]
lines = read_input()
n = len(lines)
m = len(lines[0])

def cells_by_mov (r, c, mov):
    r += MOV_R[mov]
    c += MOV_C[mov]
    while 0 <= r < n and 0 <= c < m:
        yield r, c
        r += MOV_R[mov]
        c += MOV_C[mov]

def scenic_dist (r, c):
    distances = [0, 0, 0, 0]
    prod = 1
    for mov in range(4):
        dist = 0
        for newr, newc in cells_by_mov(r, c, mov):
            dist += 1
            if lines[newr][newc] >= lines[r][c]:
                break
        prod *= dist
    return prod

def part_1 ():
    visible = [[False] * m for _ in range(n)]

    for i in range(n):
        min_h = -1
        for j in range(m):
            if lines[i][j] > min_h:
                visible[i][j] = True
                min_h = lines[i][j]
    for i in range(n):
        min_h = -1
        for j in reversed(range(m)):
            if lines[i][j] > min_h:
                visible[i][j] = True
                min_h = lines[i][j]
    for j in range(m):
        min_h = -1
        for i in range(n):
            if lines[i][j] > min_h:
                visible[i][j] = True
                min_h = lines[i][j]
    for j in range(m):
        min_h = -1
        for i in reversed(range(n)):
            if lines[i][j] > min_h:
                visible[i][j] = True
                min_h = lines[i][j]
    return sum(sum(x) for x in visible)

def part_2 ():
    s = 0
    for i in range(1, n - 1):
        for j in range(1, n - 1):
            s = max(s, scenic_dist(i, j))
    return s

def main():
    print('part_1', part_1())
    print('part_2', part_2())

if __name__ == '__main__':
    main()
