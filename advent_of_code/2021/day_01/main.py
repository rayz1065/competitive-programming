import itertools

def read_in():
    res = []
    try:
        while True:
            res.append(int(input()))
    except EOFError:
        pass
    return res

def pairwise(iterable):
    a, b = itertools.tee(iterable)
    next(b, None)
    return zip(a, b)

def part_1(measurements):
    return sum(b > a for a, b in pairwise(measurements))

def part_2(measurements):
    avg_measurements = []
    s = 0
    for i, measure in enumerate(measurements):
        s+= measure
        if i < 2:
            continue
        avg_measurements.append(s)
        s-= measurements[i - 2]
    return part_1(avg_measurements)

def main():
    measurements = read_in()
    print("part_1:", part_1(measurements))
    print("part_2:", part_2(measurements))

if __name__ == '__main__':
    main()
