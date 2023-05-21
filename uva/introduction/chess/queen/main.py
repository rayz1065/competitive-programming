MOV = [
    (-1, 0), (1, 0), (0, 1), (0, -1),
    (-1, -1), (-1, 1), (1, -1), (1, 1)
]

def in_range (r, c):
    return 1 <= r <= 8 and 1 <= c <= 8

def compute_ray (pos, direction, max_dist=8):
    x, y = pos
    dx, dy = direction
    for dist in range(1, max_dist + 1):
        new_x, new_y = x + dx * dist, y + dy * dist
        if not in_range(new_x, new_y):
            break
        yield new_x, new_y

def reachable (pos):
    res = []
    for direction in MOV:
        res.extend(compute_ray(pos, direction))
    return res

while True:
    x, y, to_x, to_y = (int(x) for x in input().strip().split())
    if x == 0:
        break

    if (x, y) == (to_x, to_y):
        print(0)
    elif (to_x, to_y) in reachable((x, y)):
        print(1)
    else:
        print(2)
