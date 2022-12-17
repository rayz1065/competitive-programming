import re

def read_input ():
    sensors = []
    try:
        while True:
            line = input()
            res = re.match(r'Sensor at x=(-?\d+), y=(-?\d+): '
                    r'closest beacon is at x=(-?\d+), y=(-?\d+)', line)
            assert res is not None
            sensors.append(tuple(int(x) for x in res.groups()))
    except EOFError:
        pass
    return sensors

def sensor_interval (sensor, searched_y):
    x, y, bx, by = sensor
    radius = abs(bx - x) + abs(by - y)
    x_range = radius - abs(searched_y - y)
    if x_range < 0:
        return None
    return (x - x_range, x + x_range)

def calc_in_range (sensors, searched_y, min_x, max_x, find_skip=False):
    # this probably doesn't always work
    intervals = filter(None, (sensor_interval(sens, searched_y) for sens in sensors))
    x = min_x
    s = 0
    for from_x, to_x in sorted(intervals):
        from_x = max(from_x, min_x)
        to_x = min(to_x, max_x)
        if x < from_x:
            if find_skip:
                return x + 1
            x = from_x
        s += max(0, to_x - x)
        x = max(x, to_x)
    return s

def part_1 (sensors, searched_y):
    # does not account for already present beacons
    return calc_in_range(sensors, searched_y, -2**30, 2**30)

def part_2 (sensors, max_coord):
    for y in range(0, max_coord + 1):
        if calc_in_range(sensors, y, 0, max_coord) != max_coord:
            break
    x = calc_in_range(sensors, y, 0, max_coord, True)
    return x * max_coord + y

def main ():
    sensors = read_input()
    print('part_1:', part_1(sensors, 2000000))
    print('part_2:', part_2(sensors, 4*10**6))

if __name__ == '__main__':
    main()
