import re
from itertools import product, tee

def pairwise(iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)

class Cube:
    def __init__(self, action, x_range, y_range, z_range):
        assert action in ['on', 'off']
        self.action = action
        self.x_range = x_range
        self.y_range = y_range
        self.z_range = z_range

    def __str__(self):
        return f'{self.str_sign()} x={self.x_range[0]}..{self.x_range[1]},' \
                                 f'y={self.y_range[0]}..{self.y_range[1]},' \
                                 f'z={self.z_range[0]}..{self.z_range[1]}'

    def in_init_range(self):
        return -50 <= self.x_range[0] <= self.x_range[1] <= 50 and \
               -50 <= self.y_range[0] <= self.y_range[1] <= 50 and \
               -50 <= self.z_range[0] <= self.z_range[1] <= 50

    def __iter__(self):
        return product(range(self.x_range[0], self.x_range[1] + 1),
                       range(self.y_range[0], self.y_range[1] + 1),
                       range(self.z_range[0], self.z_range[1] + 1))

    def __hash__(self):
        return hash((self.action, self.x_range, self.y_range, self.z_range))

    def __eq__(self, other):
        return self.action == other.action and \
               self.x_range[0] == other.x_range[0] and self.x_range[1] == other.x_range[1] and \
               self.y_range[0] == other.y_range[0] and self.y_range[1] == other.y_range[1] and \
               self.z_range[0] == other.z_range[0] and self.z_range[1] == other.z_range[1]

    def overlap(self, other):
        x_range = (max(self.x_range[0], other.x_range[0]), min(self.x_range[1], other.x_range[1]))
        y_range = (max(self.y_range[0], other.y_range[0]), min(self.y_range[1], other.y_range[1]))
        z_range = (max(self.z_range[0], other.z_range[0]), min(self.z_range[1], other.z_range[1]))
        for coord in (x_range, y_range, z_range):
            if coord[0] > coord[1]:
                return None
        return Cube(self.action, x_range, y_range, z_range)

    def volume(self):
        return (self.x_range[1] - self.x_range[0] + 1) * \
               (self.y_range[1] - self.y_range[0] + 1) * \
               (self.z_range[1] - self.z_range[0] + 1)

    def sign(self):
        if self.action == 'off':
            return -1
        return +1

    def str_sign(self):
        sign = self.sign()
        return '+' if sign > 0 else '-'

    def value(self):
        return self.sign() * self.volume()

    def inverse(self):
        sign = 'off' if (self.action == 'on') else 'on'
        return Cube(sign, self.x_range, self.y_range, self.z_range)

    # def subtract(self, other):
    #     # partitions of ranges: [self.range[0], other.range[0], other.range[1], self.range[1]]
    #     overlap = self.overlap(other)
    #     if overlap is None:
    #         return
    #     x_part = pairwise([self.x_range[0], other.x_range[0], other.x_range[1], self.x_range[1]])
    #     y_part = pairwise([self.y_range[0], other.y_range[0], other.y_range[1], self.y_range[1]])
    #     z_part = pairwise([self.z_range[0], other.z_range[0], other.z_range[1], self.z_range[1]])
    #     for x_min, x_max in x_part:
    #         for y_min, y_max in y_part:
    #             for z_min, z_max in z_part:
    #                 pass

def read_in():
    problem = []
    try:
        switch_re = re.compile(r'(on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+)')
        while True:
            line = input()
            match = switch_re.match(line)
            assert match is not None
            action = match.groups()[0]
            xmin, xmax, ymin, ymax, zmin, zmax = (int(x) for x in match.groups()[1:])
            problem.append(Cube(action, (xmin, xmax), (ymin, ymax), (zmin, zmax)))
    except EOFError:
        pass
    return problem

def part_1(problem):
    reactor = set()
    cubes = (cube for cube in problem if cube.in_init_range())
    for cube in cubes:
        for x, y, z in iter(cube):
            if cube.action == 'on':
                reactor.add((x, y, z))
            elif (x, y, z) in reactor:
                reactor.remove((x, y, z))
    return len(reactor)

def part_2(problem):
    cubes = dict()
    for new_cube in problem:
        ext_cubes = dict()
        if new_cube.action == 'on':
            ext_cubes[new_cube] = 1

        # calculate the new cubes
        for cube, freq in cubes.items():
            assert freq == 1
            inv = cube.overlap(new_cube)
            if inv is None:
                continue
            overlap = inv.inverse()
            if inv in ext_cubes:
                if freq >= ext_cubes[inv]:
                    freq-= ext_cubes[inv]
                    ext_cubes.pop(inv)
                else:
                    ext_cubes[inv]-= freq
                    freq = 0
            if freq > 0:
                ext_cubes.setdefault(overlap, 0)
                ext_cubes[overlap]+= freq

        # add the new cubes
        for cube, freq in ext_cubes.items():
            cubes.setdefault(cube, 0)
            cubes[cube]+= freq
    return sum(x.value() * freq for x, freq in cubes.items())

def main():
    problem = read_in()
    print("part_1:", part_1(problem))
    print("part_2:", part_2(problem))

if __name__ == '__main__':
    main()
