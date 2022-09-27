from math import copysign
import re

MAP_SIZE = 1000

def sgn(x):
    return int(copysign(1, x))

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return f"{self.x},{self.y}"

class Segment:
    def __init__(self, p1, p2):
        self.p1: Point = p1
        self.p2: Point = p2

    def __str__(self):
        return f"{self.p1} -> {self.p2}"

    def is_vertical(self):
        return self.p1.x == self.p2.x

    def is_horizzontal(self):
        return self.p1.y == self.p2.y

    def is_diagonal(self):
        return not self.is_orthogonal()

    def is_orthogonal(self):
        return self.is_vertical() or self.is_horizzontal()

    def points(self):
        dx = sgn(self.p2.x - self.p1.x)
        dy = sgn(self.p2.y - self.p1.y)
        if self.is_vertical():
            return ((self.p1.x, y) for y in range(self.p1.y, self.p2.y + dy, dy))
        if self.is_horizzontal():
            return ((x, self.p1.y) for x in range(self.p1.x, self.p2.x + dx, dx))
        if self.is_diagonal():
            return zip(range(self.p1.x, self.p2.x + dx, dx), range(self.p1.y, self.p2.y + dy, dy))
        assert False

def read_in():
    problem = []
    try:
        line_re = re.compile(r'^(\d+),(\d+) -> (\d+),(\d+)$')
        while True:
            line = input()
            match = line_re.match(line)
            assert match is not None
            p1 = Point(int(match[1]), int(match[2]))
            p2 = Point(int(match[3]), int(match[4]))
            problem.append(Segment(p1, p2))
    except EOFError:
        pass
    return problem

def calc_score(overlaps):
    return sum(x > 1 for x in overlaps.values())

def calc_overlaps(segments, overlaps = None):
    if overlaps is None:
        overlaps = {}
    for segment in segments:
        for x, y in segment.points():
            overlaps[x, y] = overlaps.get((x, y), 0) + 1
    return overlaps

def part_1(problem):
    overlaps = calc_overlaps(x for x in problem if x.is_orthogonal())
    return calc_score(overlaps)

def part_2(problem):
    overlaps = calc_overlaps(problem)
    return calc_score(overlaps)

def combined_parts(problem):
    # slightly faster
    orth = (x for x in problem if x.is_orthogonal())
    diag = (x for x in problem if x.is_diagonal())
    overlaps = calc_overlaps(orth)
    sol_1 = calc_score(overlaps)
    overlaps = calc_overlaps(diag, overlaps)
    sol_2 = calc_score(overlaps)
    return sol_1, sol_2

def main():
    problem = read_in()
    # sol_1, sol_2 = part_1(problem), part_2(problem)
    sol_1, sol_2 = combined_parts(problem)
    print("part_1:", sol_1)
    print("part_2:", sol_2)


if __name__ == '__main__':
    main()
