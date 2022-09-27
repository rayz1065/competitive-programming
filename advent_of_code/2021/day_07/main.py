def read_in():
    line = input()
    return [int(x) for x in line.split(',')]

def calc_fuel(positions, x, fuel_cb):
    return sum(fuel_cb(position, x) for position in positions)

def solve(positions, fuel_cb):
    x_min = min(positions)
    x_max = max(positions)
    min_dist = min(calc_fuel(positions, x, fuel_cb) for x in range(x_min, x_max + 1))
    for x in range(x_min, x_max):
        print(x, calc_fuel(positions, x, fuel_cb), sep='\t')
    return min_dist

def fuel_cb_1(position, x):
    return abs(x - position)

def part_1(positions):
    return solve(positions, fuel_cb_1)

def fuel_cb_2(position, x):
    return abs(x - position) * (abs(x - position) + 1) // 2

def part_2(positions):
    return solve(positions, fuel_cb_2)

def main():
    problem = read_in()
    print("part_1:", part_1(problem))
    print("part_2:", part_2(problem))

if __name__ == '__main__':
    main()
