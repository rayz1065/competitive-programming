from collections import namedtuple
import re

class Point(namedtuple('Point', ['x', 'y'])):
    def __str__(self):
        return f'{self.x},{self.y}'

class Fold:
    def __init__(self, axys, coord):
        self.axys = axys
        self.coord = coord

    def __str__(self):
        return f'fold along {self.axys}={self.coord}'

    def apply(self, point: Point):
        '''returns a new point reflected along this fold up and to the left only'''
        new_x, new_y = point.x, point.y
        if self.axys == 'x' and point.x > self.coord:
            new_x = 2 * self.coord - point.x
        elif self.axys == 'y' and point.y > self.coord:
            new_y = 2 * self.coord - point.y
        return Point(new_x, new_y)

class SheetFolder:
    def __init__(self, points, folds):
        self.points = points
        self.folds = folds
        self.missing_folds = iter(self.folds)
        self.completed_folds = []

    def __str__(self):
        points = '\n'.join(str(p) for p in self.points)
        folds = '\n'.join(str(f) for f in self.folds)
        return f'{points}\n\n{folds}'

    def __next__(self):
        # stop iteration may be raised
        fold = next(self.missing_folds)
        new_points = []
        for point in self.points:
            # mirror the point along the fold
            new_points.append(fold.apply(point))
            # print(point, '->', fold.apply(point), sep='\t')
        self.points = list(set(new_points))
        self.completed_folds.append(fold)
        return self.points

    def __iter__(self):
        return self

def pretty_points(points):
    x_min = min(p.x for p in points)
    x_max = max(p.x for p in points)
    y_min = min(p.y for p in points)
    y_max = max(p.y for p in points)

    points = set(points)
    pretty_point = { False: '.', True: '#' }
    lines = []
    for y in range(y_min, y_max + 1):
        line = []
        for x in range(x_min, x_max + 1):
            line.append(pretty_point[Point(x, y) in points])
        lines.append(''.join(line))
    return '\n'.join(lines)

def read_in():
    points = []
    folds = []
    while True:
        line = input()
        if line == '':
            break
        x, y = (int(x) for x in line.split(','))
        points.append(Point(x, y))

    try:
        fold_re = re.compile(r'^fold along (x|y)=(\d+)$')
        while True:
            line = input()
            match = fold_re.match(line)
            assert match is not None
            axys = match[1]
            coord = int(match[2])
            folds.append(Fold(axys, coord))
    except EOFError:
        pass
    return SheetFolder(points, folds)

def part_1(folder):
    points = next(folder)
    return len(points)

def part_2(folder):
    for _ in folder:
        pass
    return folder.points

def main():
    folder = read_in()
    print("part_1:", part_1(folder))
    code_points = part_2(folder)
    print("part_2:", pretty_points(code_points), sep='\n')

if __name__ == '__main__':
    main()
