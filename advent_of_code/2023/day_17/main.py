from enum import Enum
from collections import namedtuple, defaultdict
import heapq

CellInfo = namedtuple("CellInfo", ["r", "c", "direction", "steps_same_dir"])


class Direction(Enum):
    UP = "up"
    RIGHT = "right"
    DOWN = "down"
    LEFT = "left"


opposite_directions = {
    Direction.UP: Direction.DOWN,
    Direction.DOWN: Direction.UP,
    Direction.LEFT: Direction.RIGHT,
    Direction.RIGHT: Direction.LEFT,
}
direction_deltas = {
    Direction.UP: (-1, 0),
    Direction.RIGHT: (0, 1),
    Direction.DOWN: (1, 0),
    Direction.LEFT: (0, -1),
}


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def is_valid_transition_basic(cell_info_from: CellInfo, cell_info_to: CellInfo):
    if cell_info_to.direction == opposite_directions[cell_info_from.direction]:
        return False

    if cell_info_to.steps_same_dir >= 4:
        return False

    return True


def is_valid_transition_ultra(cell_info_from: CellInfo, cell_info_to: CellInfo):
    if cell_info_from.steps_same_dir == 0:
        # from the starting position, accept any valid direction
        return True

    if cell_info_to.direction == opposite_directions[cell_info_from.direction]:
        return False

    if cell_info_to.steps_same_dir >= 11:
        return False

    if (
        cell_info_from.steps_same_dir < 4
        and cell_info_from.direction != cell_info_to.direction
    ):
        return False

    return True


def dijkstra(grid, is_valid_transition):
    acc = 0  # used to fix issues with heapq on duplicate distances

    def get_acc():
        nonlocal acc
        acc += 1
        return acc

    cell = CellInfo(0, 0, Direction.RIGHT, 0)
    distances = {cell: 0}
    ff = [(0, get_acc(), cell)]

    while len(ff) > 0:
        distance, _, cell = heapq.heappop(ff)
        if distance != distances[cell]:
            assert distance > distances[cell]
            continue

        r, c, direction, steps_same_dir = cell

        for new_direction in Direction:
            dr, dc = direction_deltas[new_direction]
            new_r, new_c = r + dr, c + dc
            new_steps_same_dir = 1 if direction != new_direction else steps_same_dir + 1
            new_cell = CellInfo(new_r, new_c, new_direction, new_steps_same_dir)

            if not in_range(grid, new_r, new_c):
                continue

            new_distance = distance + grid[new_r][new_c]
            if new_distance >= distances.get(new_cell, new_distance + 1):
                continue

            if not is_valid_transition(cell, new_cell):
                continue

            distances[new_cell] = new_distance
            heapq.heappush(ff, (new_distance, get_acc(), new_cell))

    return distances


def get_cell_distances(grid, distances):
    cell_distances = [[2**32 for _ in range(len(grid[0]))] for _ in range(len(grid))]
    for (r, c, *_), distance in distances.items():
        cell_distances[r][c] = min(distance, cell_distances[r][c])

    return cell_distances


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield [int(x) for x in line]


def part_1(grid):
    distances = dijkstra(grid, is_valid_transition_basic)
    cell_distances = get_cell_distances(grid, distances)
    return cell_distances[-1][-1]


def part_2(grid):
    distances = dijkstra(grid, is_valid_transition_ultra)

    # discard unstable configurations
    distances = {
        cell: distance
        for cell, distance in distances.items()
        if cell.steps_same_dir >= 4
    }

    cell_distances = get_cell_distances(grid, distances)
    return cell_distances[-1][-1]


def main():
    grid = list(read_lines())
    print("part_1:", part_1(grid))
    print("part_2:", part_2(grid))


if __name__ == "__main__":
    main()
