from itertools import product

def read_input ():
    points = []
    try:
        while True:
            coords = tuple(int(x) for x in input().split(','))
            points.append(coords)
    except EOFError:
        pass
    return points

adjacent_points = [
    (x, y, z)
    for x, y, z
    in product(range(-1, 2), range(-1, 2), range(-1, 2))
    if abs(x) + abs(y) + abs(z) == 1
]

def part_1 (points):
    points = set(points)
    s = 0
    for x, y, z in points:
        for dx, dy, dz in adjacent_points:
            if (x + dx, y + dy, z + dz) not in points:
                s += 1
    return s

def part_2 (points):
    points_map = { point: 'rock' for point in points }
    min_coord = min(0, min(min(point) for point in points)) - 1
    max_coord = max(max(point) for point in points) + 1
    assert (-1, -1, -1) not in points
    # dfs
    ff = [(-1, -1, -1)]
    points_map[ff[0]] = 'air'
    while len(ff) > 0:
        x, y, z = ff[-1]
        ff.pop()
        for dx, dy, dz in adjacent_points:
            if not (min_coord <= x + dx <= max_coord and min_coord <= y + dy <= max_coord and min_coord <= z + dz <= max_coord):
                # out of range
                continue
            new_point = (x + dx, y + dy, z + dz)
            if new_point not in points_map:
                points_map[new_point] = 'air'
                ff.append(new_point)
    coord_range = range(min_coord, max_coord)
    for point in product(coord_range, coord_range, coord_range):
        if point not in points_map:
            points_map[point] = 'inside'
    new_points = [point for point, p_type in points_map.items() if p_type != 'air']
    return part_1(new_points)

def main ():
    points = read_input()

    print('part_1:', part_1(points))
    print('part_2:', part_2(points))

if __name__ == '__main__':
    main()
