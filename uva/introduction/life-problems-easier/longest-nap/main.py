import re

DAY_START = 10 * 60
DAY_END = 18 * 60
DAY_DURATION = DAY_END - DAY_START


def clock_to_int (time):
    segments = tuple(int(x) for x in time.split(':'))
    return segments[0] * 60 + segments[1]


def int_to_clock (time):
    segments = [
        time // 60,
        time % 60
    ]
    return ':'.join(str(x).rjust(2, '0') for x in segments)


def solve (times: list):
    occupied = [0] * DAY_DURATION
    for time in times:
        for i in range(time[0] - DAY_START, time[1] - DAY_START):
            occupied[i] += 1

    # find the longest window of zeros
    curr_start = 0
    best_duration, best_start = 0, None
    for i, is_occupied in enumerate(occupied):
        if is_occupied:
            curr_start = i + 1
            continue

        # recompute the best duration
        duration = i - curr_start + 1
        if duration > best_duration:
            best_duration = duration
            best_start = curr_start

    return best_duration, best_start + DAY_START


def main ():
    tc = 0
    while True:
        try:
            n = int(input().strip())
        except EOFError:
            break

        # extract clock from input
        times = [input().strip() for _ in range(n)]
        times = [
            tuple(re.match(r'^(\d{2}:\d{2}) (\d{2}:\d{2})', time).groups())
            for time in times
        ]
        times = [tuple(clock_to_int(x) for x in time)
                 for time in times]

        duration, start = solve(times)
        duration_h = duration // 60
        duration_m = duration % 60

        duration_segments = []
        if duration_h > 0:
            duration_segments.append(f'{duration_h} hours')
        duration_segments.append(f'{duration_m} minutes')

        tc += 1
        print(f'Day #{tc}: the longest nap starts at {int_to_clock(start)} '
              f'and will last for {" and ".join((duration_segments))}.')


if __name__ == '__main__':
    main()
