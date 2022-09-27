SC_MOVEMENTS = {
    '>': (0, 1),
    'v': (1, 0)
}

class TrenchMap:
    def __init__(self, trench_map):
        self.trench_map = trench_map
        self.n = len(self.trench_map)
        self.m = len(self.trench_map[0])
        self.moved = None

    def cells(self):
        for i in range(self.n):
            for j in range(self.m):
                yield i, j, self.trench_map[i][j]

    def is_empty_chr(self, cell):
        return cell == '.'

    def is_empty(self, i, j):
        return self.is_empty_chr(self.trench_map[i][j])

    def ahead_chr(self, i, j, cell):
        delta_i, delta_j = SC_MOVEMENTS[cell]
        return (i + delta_i)%self.n, (j + delta_j)%self.m

    def ahead(self, i, j):
        assert not self.is_empty(i, j)
        delta_i, delta_j = SC_MOVEMENTS[self.trench_map[i][j]]
        return (i + delta_i)%self.n, (j + delta_j)%self.m

    def move_east(self):
        moving = []
        for i, j, _ in self.cells():
            if self.trench_map[i][j] == '>':
                new_i, new_j = self.ahead(i, j)
                if self.is_empty(new_i, new_j):
                    moving.append((i, j))
        for i, j in moving:
            new_i, new_j = self.ahead(i, j)
            self.swap(i, j, new_i, new_j)
        return len(moving)

    def move_south(self):
        moving = []
        for i, j, _ in self.cells():
            if self.trench_map[i][j] == 'v':
                new_i, new_j = self.ahead(i, j)
                if self.is_empty(new_i, new_j):
                    moving.append((i, j))
        for i, j in moving:
            new_i, new_j = self.ahead(i, j)
            self.swap(i, j, new_i, new_j)
        return len(moving)

    def swap(self, i, j, other_i, other_j):
        tmp = self.trench_map[other_i][other_j]
        self.trench_map[other_i][other_j] = self.trench_map[i][j]
        self.trench_map[i][j] = tmp

    def simulate(self):
        trench = self.copy()
        res = trench.move_east()
        res+= trench.move_south()
        trench.moved = res
        return trench

    def copy(self):
        return TrenchMap([self.trench_map[i].copy() for i in range(self.n)])

    def __str__(self):
        return '\n'.join(''.join(row) for row in self.trench_map)

def read_in():
    problem = []
    try:
        while True:
            line = input()
            problem.append(list(line))
    except EOFError:
        pass
    return TrenchMap(problem)

def main():
    trench_map = read_in()
    i = 0
    while trench_map.moved is None or trench_map.moved > 0:
        i+= 1
        trench_map = trench_map.simulate()
    print(i, trench_map)

if __name__ == '__main__':
    main()
