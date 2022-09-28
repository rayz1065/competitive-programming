def read_input():
    _, r, t, l = (int(x) for x in input().split())
    xs = [int(x) for x in input().split()]
    xs.append(l)
    return r, t, xs

r_skippable, t_half_period, xs = read_input()

def dist_to_next(semaphore_idx):
    if semaphore_idx == len(xs) - 1:
        return 0
    return xs[semaphore_idx + 1] - xs[semaphore_idx]

def fastest_route(semaphore_idx, already_skipped, elapsed_time):
    '''Find the best route from this semaphore after t time has passed'''
    if semaphore_idx == len(xs) - 1:
        # already reached the end
        return 0
    dist = dist_to_next(semaphore_idx)
    if elapsed_time % (2 * t_half_period) >= t_half_period:
        # wait for green
        wait_for_green = 2 * t_half_period - elapsed_time % (2 * t_half_period)
        best = fastest_route(semaphore_idx + 1, already_skipped, elapsed_time + dist + wait_for_green) + dist + wait_for_green
        # don't wait for green
        if already_skipped < r_skippable:
            time_by_skipping = fastest_route(semaphore_idx + 1, already_skipped + 1, elapsed_time + dist) + dist
            best = min(best, time_by_skipping)
    else:
        # already green
        best = fastest_route(semaphore_idx + 1, already_skipped, elapsed_time + dist) + dist
    return best

def my_min(a, b):
    if a is None:
        return b
    return min(a, b)

def iterative_solve():
    memo = [[2 ** 40 for _ in range(r_skippable + 1)] for _ in range(2)]
    # reaching the first semaphore in xs[0] time
    memo[0][0] = xs[0]
    for i in range(len(xs) - 1):
        # print(memo)
        for k, _ in enumerate(memo[(i + 1) % 2]):
            memo[(i + 1) % 2][k] = 2 ** 40
        dist = dist_to_next(i)
        # we're at the semaphore at distance x
        for already_skipped in range(r_skippable + 1):
            # we've already skipped already_skipped semaphores
            elapsed_time = memo[i % 2][already_skipped]

            if elapsed_time % (2 * t_half_period) >= t_half_period:
                # wait for green
                wait_for_green = 2 * t_half_period - elapsed_time % (2 * t_half_period)
                time_by_waiting = elapsed_time + dist + wait_for_green
                memo[(i + 1) % 2][already_skipped] = my_min(memo[(i + 1) % 2][already_skipped], time_by_waiting)
                # don't wait for green
                if already_skipped < r_skippable:
                    time_by_skipping = elapsed_time + dist
                    memo[(i + 1) % 2][already_skipped + 1] = my_min(memo[(i + 1) % 2][already_skipped + 1], time_by_skipping)
            else:
                # already green
                time_by_waiting = elapsed_time + dist
                memo[(i + 1) % 2][already_skipped] = my_min(memo[(i + 1) % 2][already_skipped], time_by_waiting)
    # print(memo)
    return min(filter(None, memo[(len(xs) - 1) % 2]))

def solve():
    return iterative_solve()
    # return fastest_route(0, 0, xs[0]) + xs[0]

if __name__ == '__main__':
    print(solve())
