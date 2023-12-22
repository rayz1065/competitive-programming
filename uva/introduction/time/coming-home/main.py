def solve(curr_time, busses):
    curr_h, curr_m = (int(x) for x in curr_time.split(':'))
    best_wait = None

    for start_time, transit_time in busses:
        start_h, start_m = (int(x) for x in start_time.split(':'))
        if start_time < curr_time:
            start_h += 24

        wait = (start_h - curr_h) * 60 + (start_m - curr_m) + transit_time
        if best_wait is None or wait < best_wait:
            best_wait = wait

    return best_wait


def main ():
    t = int(input().strip())
    for tc in range(t):
        k_busses, curr_time = input().strip().split()
        k_busses = int(k_busses)
        busses = [input().split() for _ in range(k_busses)]
        busses = [(x, int(y)) for x, y in busses]

        print(f'Case {tc + 1}: {solve(curr_time, busses)}')


if __name__ == '__main__':
    main()
