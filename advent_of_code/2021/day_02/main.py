directions = {
    'forward': (0, 1),
    'up': (-1, 0),
    'down': (1, 0),
}

def read_in():
    res = []
    try:
        while True:
            line = input().split(' ')
            dire, am = line[0], int(line[1])
            res.append((dire, am))
    except EOFError:
        pass
    return res

def move_1(movements):
    depth, x = 0, 0
    for dire, am in movements:
        delta_depth, delta_x = directions[dire]
        depth+= delta_depth * am
        x+= delta_x * am
    return depth, x

def part_1(problem):
    depth, x = move_1(problem)
    return depth * x

def move_2(movements):
    depth, x, aim = 0, 0, 0
    for dire, am in movements:
        delta_aim, delta_x = directions[dire]
        aim+= delta_aim * am
        x+= delta_x * am
        depth+= delta_x * am * aim
    return depth, x, aim

def part_2(problem):
    depth, x, _aim = move_2(problem)
    return depth * x

def main():
    problem = read_in()
    print("part_1:", part_1(problem))
    print("part_2:", part_2(problem))

if __name__ == '__main__':
    main()
