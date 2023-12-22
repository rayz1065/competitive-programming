import re
from collections import namedtuple

Coords = namedtuple("Coords", ["x", "y", "z"])
Brick = namedtuple("Brick", ["coords_a", "coords_b"])


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(r"(\d+),(\d+),(\d+)~(\d+),(\d+),(\d+)", line)
        x, y, z, xt, yt, zt = (int(x) for x in res.groups())
        yield Brick(Coords(x, y, z), Coords(xt, yt, zt))


def sign(x):
    return 0 if x == 0 else x // abs(x)


def brick_iter(brick: Brick):
    dx = sign(brick.coords_b.x - brick.coords_a.x)
    dy = sign(brick.coords_b.y - brick.coords_a.y)
    dz = sign(brick.coords_b.z - brick.coords_a.z)
    x, y, z = brick.coords_a

    yield Coords(x, y, z)
    while (x, y, z) != brick.coords_b:
        x, y, z = x + dx, y + dy, z + dz
        yield Coords(x, y, z)


def get_occupied_coords(bricks: list[Brick]):
    res = {}
    for i, brick in enumerate(bricks):
        for coords in brick_iter(brick):
            res[coords] = i

    return res


def get_resting_points(occupied: dict, brick: Brick):
    brick_id = occupied[brick.coords_a]

    res = set()
    for x, y, z in brick_iter(brick):
        brick_below = occupied.get(Coords(x, y, z - 1), None)
        if brick_below is not None and brick_below != brick_id:
            res.add(brick_below)

    return res


def make_fall(occupied: dict, brick: Brick):
    brick_id = occupied[brick.coords_a]

    while brick.coords_a.z > 1:
        # try lowering it
        if len(get_resting_points(occupied, brick)) > 0:
            # can no longer fall
            break

        for coords in brick_iter(brick):
            occupied.pop(coords)

        x, y, z = brick.coords_a
        tx, ty, tz = brick.coords_b
        brick = Brick(Coords(x, y, z - 1), Coords(tx, ty, tz - 1))

        for coords in brick_iter(brick):
            occupied[coords] = brick_id

    return brick


def print_plane(occupied: dict, coord_idx):
    xs = [x[coord_idx] for x in occupied]
    zs = [x.z for x in occupied]

    res = [["." for _ in range(max(xs) + 1)] for _ in range(max(zs) + 1)]
    for coords, brick_id in occupied.items():
        res[coords.z][coords[coord_idx]] = chr(brick_id + ord("A"))

    for row in reversed(res):
        print(" ".join(row))
    print()


def part_1(bricks: list[Brick]):
    occupied = get_occupied_coords(bricks)
    for brick_id, brick in sorted(enumerate(bricks), key=lambda x: x[1].coords_a.z):
        brick = make_fall(occupied, brick)
        bricks[brick_id] = brick

    can_be_disintegrated = [True] * len(bricks)
    for brick_id, brick in enumerate(bricks):
        resting_points = get_resting_points(occupied, brick)
        if len(resting_points) == 1:
            can_be_disintegrated[resting_points.pop()] = False

    return sum(can_be_disintegrated)


def part_2(bricks: list[Brick]):
    occupied = get_occupied_coords(bricks)
    for brick_id, brick in sorted(enumerate(bricks), key=lambda x: x[1].coords_a.z):
        brick = make_fall(occupied, brick)
        bricks[brick_id] = brick

    candidates = set()
    for brick_id, brick in enumerate(bricks):
        resting_points = get_resting_points(occupied, brick)
        if len(resting_points) == 1:
            candidates.add(resting_points.pop())

    res = 0
    for candidate in candidates:
        occupied_new = occupied.copy()
        bricks_new = bricks.copy()
        for coords in brick_iter(bricks[candidate]):
            occupied_new.pop(coords)

        for brick_id, brick in sorted(
            enumerate(bricks_new), key=lambda x: x[1].coords_a.z
        ):
            if brick_id == candidate:
                continue

            brick_after = make_fall(occupied_new, brick)

            if brick != brick_after:
                res += 1

            bricks_new[brick_id] = brick_after

    return res


def main():
    bricks = list(read_lines())
    print("part_1:", part_1(bricks))
    print("part_2:", part_2(bricks))


if __name__ == "__main__":
    main()
