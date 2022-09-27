import re
from itertools import permutations, chain

SEVEN_SEGMENT_NUMBERS = [
    'abcefg',
    'cf',
    'acdeg',
    'acdfg',
    'bcdf',
    'abdfg',
    'abdefg',
    'acf',
    'abcdefg',
    'abcdfg',
]
SEGMENTS_COUNT = 9

lengths_map = [[] for _ in range(SEGMENTS_COUNT + 1)]
for i, i_str in enumerate(SEVEN_SEGMENT_NUMBERS):
    lengths_map[len(i_str)].append(i)
seven_segments_map = { i_str: i for i, i_str in enumerate(SEVEN_SEGMENT_NUMBERS) }
unique_lengths = { i: True for i, numbers in enumerate(lengths_map) if len(numbers) == 1 }
def ALL_SEGMENTS():
    return (chr(ord('a') + j)  for j in range(SEGMENTS_COUNT))

def read_in():
    problem = []
    try:
        line_re = re.compile(r'([a-g\s]+)\s\|\s([a-g\s]+)')
        while True:
            line = input()
            res = line_re.match(line)
            assert res is not None
            inputs = res[1].split(' ')
            outputs = res[2].split(' ')
            problem.append(Display(inputs, outputs))
    except EOFError:
        pass
    return problem

def calculate_leds_map(perm):
    return { chr(ord('a') + i): c for i, c in enumerate(perm) }

def remap_number(number, leds_map):
    return ''.join(sorted(leds_map[x] for x in number))

class Display:
    def __init__(self, inputs, outputs):
        self.inputs: list = inputs
        self.outputs: list = outputs
        self.led_could_map_to = {
            segment: set(ALL_SEGMENTS())
            for segment in ALL_SEGMENTS()
        }

    def __str__(self):
        inputs_str = ' '.join(self.inputs)
        outputs_str = ' '.join(self.outputs)
        return f"{inputs_str} | {outputs_str}"

    def count_outputs_unique_len(self):
        return sum(1 for x in self.outputs if len(x) in unique_lengths)

    def check_leds_map(self, leds_map):
        for number in chain(self.inputs, self.outputs):
            remapped_number = remap_number(number, leds_map)
            if remapped_number not in seven_segments_map:
                # this is not a valid number
                return False
        return True

    def find_leds_map(self):
        for perm in permutations('abcdefg'):
            leds_map = calculate_leds_map(perm)
            if self.check_leds_map(leds_map):
                return leds_map
        return None

    def calculate_output(self, leds_map):
        res = 0
        for number in self.outputs:
            remapped_number = remap_number(number, leds_map)
            number = seven_segments_map[remapped_number]
            res = res * 10 + number
        return res

    def solve(self):
        leds_map = self.find_leds_map()
        assert leds_map is not None
        return self.calculate_output(leds_map)

    def _solve_2(self, assignments):
        if len(assignments) == SEGMENTS_COUNT:
            if self.check_leds_map(assignments):
                return True
            return False

        best = None
        for segment in ALL_SEGMENTS():
            if segment in assignments:
                # segment is already assigned
                continue
            if best is None or \
                len(self.led_could_map_to[segment]) < len(self.led_could_map_to[best]):
                best = segment

        for assignment in self.led_could_map_to[best].difference(assignments.values()):
            assignments[best] = assignment
            sol = self._solve_2(assignments)
            if sol:
                # propagate the solution
                return sol
            assignments.pop(best)
        return False

    def solve_2(self):
        for number in chain(self.inputs, self.outputs):
            if len(number) in unique_lengths:
                # this number is of a unique length
                # this means that the segments that compose it must be in the unique number
                x = lengths_map[len(number)][0]
                remapped_number = SEVEN_SEGMENT_NUMBERS[x]
                for c in number:
                    self.led_could_map_to[c].intersection_update(remapped_number)

        leds_map = {}
        assert self._solve_2(leds_map)
        return self.calculate_output(leds_map)

def part_1(problem):
    return sum(x.count_outputs_unique_len() for x in problem)

def part_2(problem):
    # solutions = [x.solve() for x in problem]
    solutions = [x.solve_2() for x in problem]
    return sum(solutions)

def main():
    problem = read_in()
    print("part_1:", part_1(problem))
    print("part_2:", part_2(problem))

if __name__ == '__main__':
    main()
