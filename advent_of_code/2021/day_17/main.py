import re

MAX_Y_SPEED = 200

class Problem:
    def __init__(self, x_min, x_max, y_min, y_max):
        self.x_min = x_min
        self.x_max = x_max
        self.y_min = y_min
        self.y_max = y_max

    def __str__(self):
        return f"target area: x={self.x_min}..{self.x_max}, y={self.y_min}..{self.y_max}"

    def in_target(self, x, y):
        return self.x_min <= x <= self.x_max and \
               self.y_min <= y <= self.y_max

def read_in():
    line = input()
    match = re.match(r'^target area: x=(-?\d+)\.\.(-?\d+), y=(-?\d+)\.\.(-?\d+)$', line)
    assert match is not None
    x_min, x_max, y_min, y_max = (int(x) for x in match.groups())
    return Problem(x_min, x_max, y_min, y_max)

def eval_drag(x_speed):
    if x_speed > 0:
        return x_speed - 1
    if x_speed < 0:
        return x_speed + 1
    return 0

def simulate(problem: Problem, x_speed, y_speed):
    x, y = 0, 0
    while x < problem.x_max:
        x+= x_speed
        y+= y_speed
        x_speed = eval_drag(x_speed)
        y_speed-= 1 # apply gravity
        yield x, y

        if x_speed == 0:
            # drag slowed the probe to a stop in the x direction
            if y_speed < 0 and y < problem.y_min:
                # the probe is never going back up and is already too low down
                break

def find_max_y(problem: Problem, x_speed):
    y_max = 0
    for y_speed in range(0, MAX_Y_SPEED):
        sp_y_max = 0
        for x, y in simulate(problem, x_speed, y_speed):
            sp_y_max = max(sp_y_max, y)
            if problem.in_target(x, y):
                y_max = max(y_max, sp_y_max)
    return y_max

def calculate_possible_x_speeds(problem: Problem):
    possible_x_speeds = []
    for x_speed in range(problem.x_max + 1):
        steps = [(step + 1, x) for step, (x, y)
                    in enumerate(simulate(problem, x_speed, 0))
                    if problem.x_min <= x <= problem.x_max]
        if len(steps):
            possible_x_speeds.append(x_speed)
    return possible_x_speeds

def part_1(problem: Problem):
    possible_x_speeds = calculate_possible_x_speeds(problem)
    max_y = 0
    for x_speed in possible_x_speeds:
        max_y = max(max_y, find_max_y(problem, x_speed))
    return max_y

def part_2(problem: Problem):
    possible_x_speeds = calculate_possible_x_speeds(problem)
    speeds = []
    for x_speed in possible_x_speeds:
        for y_speed in range(problem.y_min, MAX_Y_SPEED):
            points = simulate(problem, x_speed, y_speed)
            if any((problem.in_target(x, y) for x, y in points)):
                speeds.append((x_speed, y_speed))
    return len(speeds)

def main():
    problem = read_in()
    print(problem)
    print("part_1:", part_1(problem))
    print("part_2:", part_2(problem))

if __name__ == '__main__':
    main()
