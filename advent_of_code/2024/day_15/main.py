DIRECTIONS = {"v": (1, 0), "^": (-1, 0), "<": (0, -1), ">": (0, 1)}


def read_input():
    grid = []
    robot = None
    while True:
        line = input().strip()
        if line == "":
            break

        line = list(line)
        if "@" in line:
            robot_column = line.index("@")
            robot = len(grid), robot_column
            line[robot_column] = "."

        grid.append(line)

    instructions = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        instructions.extend(list(line))

    return grid, robot, instructions


def find_wall_or_space(grid, r, c, dr, dc):
    while grid[r][c] not in ".#":
        r += dr
        c += dc
    return r, c


def simulate_1(grid, robot, instruction):
    dr, dc = DIRECTIONS[instruction]
    r, c = robot
    new_r, new_c = r + dr, c + dc
    if grid[new_r][new_c] == "#":
        return grid, robot
    if grid[new_r][new_c] == ".":
        return grid, (new_r, new_c)

    empty_r, empty_c = find_wall_or_space(grid, new_r, new_c, dr, dc)
    if grid[empty_r][empty_c] == "#":
        return grid, robot

    grid = [row[:] for row in grid]
    robot = new_r, new_c
    grid[empty_r][empty_c] = grid[new_r][new_c]
    grid[new_r][new_c] = "."

    return grid, robot


def print_grid(grid, robot, boxes=None):
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if (r, c) == robot:
                print("@", end="")
            elif boxes and (r, c) in boxes:
                print("[", end="")
            elif boxes and (r, c - 1) in boxes:
                print("]", end="")
            else:
                print(cell, end="")
        print()
    print()


def get_grid_score_1(grid):
    res = 0
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if cell == "O":
                res += r * 100 + c
    return res


def get_grid_score_2(boxes):
    res = 0
    for r, c in boxes:
        res += r * 100 + c
    return res


def get_box_location(boxes, r, c):
    if (r, c) in boxes:
        return (r, c)
    if (r, c - 1) in boxes:
        return (r, c - 1)
    return None


def simulate_2(grid, robot, boxes, instruction):
    dr, dc = DIRECTIONS[instruction]
    r, c = robot
    new_r, new_c = r + dr, c + dc

    if grid[new_r][new_c] == "#":
        return robot, boxes

    box_location = get_box_location(boxes, new_r, new_c)

    if grid[new_r][new_c] == "." and box_location is None:
        return (new_r, new_c), boxes

    pushed_boxes = set([box_location])
    ff = [box_location]

    while ff:
        box_r, box_c = ff.pop()
        new_box_r = box_r + dr
        new_box_c = box_c + dc

        if grid[new_box_r][new_box_c] == "#" or grid[new_box_r][new_box_c + 1] == "#":
            return robot, boxes

        box_location_1 = get_box_location(boxes, new_box_r, new_box_c)
        box_location_2 = get_box_location(boxes, new_box_r, new_box_c + 1)

        if box_location_1 is not None and box_location_1 not in pushed_boxes:
            ff.append(box_location_1)
            pushed_boxes.add(box_location_1)
        if box_location_2 is not None and box_location_2 not in pushed_boxes:
            ff.append(box_location_2)
            pushed_boxes.add(box_location_2)

    boxes = boxes.difference(pushed_boxes)
    boxes.update((box_r + dr, box_c + dc) for box_r, box_c in pushed_boxes)

    return (new_r, new_c), boxes


def part_1(grid, robot, instructions):
    for instruction in instructions:
        grid, robot = simulate_1(grid, robot, instruction)
    return get_grid_score_1(grid)


def part_2(grid, robot, instructions):
    boxes = set()
    grid = list(row[:] for row in grid)
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if cell == "O":
                boxes.add((r, c * 2))
                grid[r][c] = "."
    grid = [[x for x in row for _ in range(2)] for row in grid]
    robot = (robot[0], robot[1] * 2)

    for instruction in instructions:
        robot, boxes = simulate_2(grid, robot, boxes, instruction)

    return get_grid_score_2(boxes)


def main():
    grid, robot, instructions = read_input()
    print("part1:", part_1(grid, robot, instructions))
    print("part2:", part_2(grid, robot, instructions))


if __name__ == "__main__":
    main()
