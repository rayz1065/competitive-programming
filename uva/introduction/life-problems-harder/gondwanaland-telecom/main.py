import re

CHARGING_STEPS = {
    'A': [0.10, 0.06, 0.02],
    'B': [0.25, 0.15, 0.05],
    'C': [0.53, 0.33, 0.13],
    'D': [0.87, 0.47, 0.17],
    'E': [1.44, 0.80, 0.30],
}
DAY_START = 8 * 60
EVENING_START = 18 * 60
NIGHT_START = 22 * 60
DAY_DURATION = 24 * 60
TIMES_MAPPING = [
    *([2] * DAY_START),
    *([0] * (EVENING_START - DAY_START)),
    *([1] * (NIGHT_START - EVENING_START)),
    *([2] * (DAY_DURATION - NIGHT_START)),
]


def compute_charge_times (start, end):
    # splits time into [day, evening, night]
    # if needed, can be made faster with more complex logic
    splits = [0, 0, 0]
    if start >= end:
        end += len(TIMES_MAPPING)

    for i in range(start, end):
        splits[TIMES_MAPPING[i % len(TIMES_MAPPING)]] += 1

    return splits


def read_input ():
    while True:
        line = input().strip()
        if line == '#':
            break
        yield line


def time_to_number (time):
    hours, minutes = (int(x) for x in time.split(' '))
    return hours * 60 + minutes


def main ():
    for line in read_input():
        match = re.match(r'([A-E]) ([\d-]+) (\d{2} \d{2}) (\d{2} \d{2})', line)
        step, number, start, end = match.groups()
        start, end = (time_to_number(x) for x in (start, end))
        splits = compute_charge_times(start, end)
        total_cost = sum(x * rate for x, rate in zip(splits, CHARGING_STEPS[step]))

        print(f'{str(number).rjust(10)}'
              f'{str(splits[0]).rjust(6)}'
              f'{str(splits[1]).rjust(6)}'
              f'{str(splits[2]).rjust(6)}'
              f'{step.rjust(3)}'
              + (f'{total_cost:.2f}').rjust(8))


if __name__ == '__main__':
    main()
