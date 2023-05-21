MAX_TIME = 5 * 3600

def parse_numbers (line):
    return [int(x) for x in line.split() if len(x) > 0]


def parse_input ():
    numbers = []
    while True:
        try:
            line = parse_numbers(input())
        except EOFError:
            break
        if len(line) == 3 and all(x == 0 for x in line):
            # after this line input may be garbled
            break
        numbers.extend(x for x in line)
    cases = [[]]
    for number in numbers:
        if number == 0:
            cases.append([])
        else:
            cases[-1].append(number)
    return [x for x in cases if len(x) > 0]


def is_green (cycle, t):
    # green in time [0, cycle - 5)
    time_since_start = t % (2 * cycle)
    return 0 <= time_since_start < cycle - 5


def is_sync (cycles, t):
    return all(is_green(cycle, t) for cycle in cycles)


def solve (cycles):
    for start_t in range(MAX_TIME + 1):
        if not is_sync(cycles, start_t):
            break
    for t in range(start_t + 1, MAX_TIME + 1):
        if is_sync(cycles, t):
            return t
    return None


def time_to_clock (t):
    seconds = t % 60
    minutes = (t % 3600) // 60
    hours = t // 3600
    return ':'.join(str(x).rjust(2, '0') for x in (hours, minutes, seconds))


def main ():
    cases = parse_input()
    for values in cases:
        sync_time = solve(values)
        if sync_time is None:
            print('Signals fail to synchronise in 5 hours')
        else:
            print(time_to_clock(sync_time))


if __name__ == '__main__':
    main()
