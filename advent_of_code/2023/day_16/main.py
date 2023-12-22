from enum import Enum


class Direction(Enum):
    UP = "up"
    RIGHT = "right"
    DOWN = "down"
    LEFT = "left"

    def get_deltas(self):
        deltas = {
            Direction.UP: (-1, 0),
            Direction.RIGHT: (0, 1),
            Direction.DOWN: (1, 0),
            Direction.LEFT: (0, -1),
        }

        return deltas[self]

    def split(self, cell):
        dr, dc = self.get_deltas()

        splitters = {
            "|": (Direction.UP, Direction.DOWN),
            "-": (Direction.LEFT, Direction.RIGHT),
        }

        if self in splitters[cell]:
            # traveling parallel to the splitter
            return [self]

        # return perpendicular directions
        return list(splitters[cell])

    def reflect(self, cell):
        # map the input direction to the output direction
        mirrors = {
            "/": {
                Direction.UP: Direction.RIGHT,
                Direction.RIGHT: Direction.UP,
                Direction.LEFT: Direction.DOWN,
                Direction.DOWN: Direction.LEFT,
            },
            "\\": {
                Direction.UP: Direction.LEFT,
                Direction.LEFT: Direction.UP,
                Direction.DOWN: Direction.RIGHT,
                Direction.RIGHT: Direction.DOWN,
            },
        }

        return mirrors[cell][self]

    def travel(self, cell):
        if cell in ("/", "\\"):
            return [self.reflect(cell)]

        if cell in ("|", "-"):
            return self.split(cell)

        return [self]


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield line


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def trace_ray(grid, start_cell):
    visited = set([start_cell])
    ff = [start_cell]

    while len(ff) > 0:
        r, c, direction = ff.pop()
        dr, dc = direction.get_deltas()

        for new_direction in direction.travel(grid[r][c]):
            dr, dc = new_direction.get_deltas()
            new_r, new_c = r + dr, c + dc
            new_key = (new_r, new_c, new_direction)
            if not in_range(grid, new_r, new_c) or new_key in visited:
                continue

            visited.add(new_key)
            ff.append((new_key))

    return visited


def print_energized(grid, energized):
    for row in range(len(grid)):
        print(
            "".join("#" if (row, col) in energized else "." for col in range(len(grid)))
        )


def get_energized(grid, start_cell):
    visited = trace_ray(grid, start_cell=start_cell)
    energized = set((r, c) for r, c, _ in visited)

    return energized


def part_1(grid):
    return len(get_energized(grid, start_cell=(0, 0, Direction.RIGHT)))


def part_2(grid):
    res = []
    rows, cols = len(grid), len(grid[0])

    # start from any row, going left or right
    for r in range(rows):
        res.append(len(get_energized(grid, start_cell=(r, cols - 1, Direction.LEFT))))
        res.append(len(get_energized(grid, start_cell=(r, 0, Direction.RIGHT))))

    # start from any column, going up or down
    for c in range(cols):
        res.append(len(get_energized(grid, start_cell=(rows - 1, c, Direction.UP))))
        res.append(len(get_energized(grid, start_cell=(0, c, Direction.DOWN))))

    return max(res)


def main():
    grid = list(read_lines())
    print("part_1:", part_1(grid))
    print("part_2:", part_2(grid))


if __name__ == "__main__":
    main()
