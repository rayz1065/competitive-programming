import sys
from itertools import tee, chain
from math import factorial
from time import time_ns

start = time_ns() / 10 ** 9

def pairwise(it):
    a, b = tee(it)
    next(b)
    return zip(a, b)

n, k = (int(x) for x in input().split())
mid_start = 3 * k
mid_end = (n // k - 3) * k
mid_end_start = mid_end - k
mid_optimize = mid_start + 2 * k < mid_end
best_costs = [10**9]
best_sols = [[]]
cut_branches = { 'tot': 0 }
forced_next = {}
if mid_optimize:
    forced_next.update({
        mid_start + i: mid_end_start + i for i in range(k)
    })
    forced_next.update({
        mid_end_start + i: mid_start + i for i in range(k)
    })

def is_mid_start(pos):
    return mid_start <= pos <= mid_start + k - 1

def is_mid_end(pos):
    return mid_end - k <= pos <= mid_end - 1

# print(f"0 - [{mid_start}:{mid_start + k - 1}] - [{mid_end - k}:{mid_end - 1}] - {n - 1}")
# print(forced_next)

def cost_estimate(curr):
    # how long will it take to finish plowing?
    base = calculate_cost(curr)
    pos = curr[-1]
    leftmost = min(pos, min(missing))
    rightmost = max(pos, max(missing))

    dist_to_rightmost = rightmost - pos
    dist_to_leftmost = pos - leftmost
    # go from pos to leftmost, then from leftmost to rightmost
    estimate_1 = base + 2 * dist_to_leftmost + dist_to_rightmost
    # go from pos to rightmost, then from rightmost to leftmost
    estimate_2 = base + dist_to_leftmost + 2 * dist_to_rightmost
    return min(estimate_1, estimate_2)

def calculate_cost(curr):
    return sum(abs(a - b) for a, b in pairwise(curr))

def is_timeout():
    return (time_ns() / 10 ** 9) - start >= 9.

def print_curr_best():
    print(best_costs[-1])
    for i, x in enumerate(best_sols[-1]):
        print(x, end=' ')
        if x in forced_next and best_sols[-1][i - 1] != forced_next[x]:
            delta = -k if forced_next[x] < x else k
            a = x + delta
            while a != forced_next[x]:
                print(a, end=' ')
                a += delta
    # print(cut_branches)

def solve(curr):
    if is_timeout():
        print_curr_best()
        sys.exit(0)

    if len(missing) == 0:
        curr_cost = calculate_cost(curr)
        if curr_cost < best_costs[-1]:
            # print(curr, 'with cost', curr_cost)
            best_costs.append(curr_cost)
            best_sols.append(tuple(curr))
        return
    if cost_estimate(curr) >= best_costs[-1]:
        # not an improvement
        # approx number of saved calls
        # missing = n - len(curr)
        # cut_branches['tot'] += factorial(missing)
        return
    if curr[-1] in forced_next and curr[-2] not in forced_next:
        next_pos = forced_next[curr[-1]]
        assert next_pos in missing, curr
        curr.append(next_pos)
        missing.discard(next_pos)
        solve(curr)
        missing.add(next_pos)
        curr.pop()
        return

    # print(curr, missing)
    for i in missing:
        if abs(curr[-1] - i) >= k and (
            (i <= (mid_start + k) and curr[-1] <= (mid_start + k)) or
            (i >= (mid_end_start) and curr[-1] >= (mid_end_start)) or
            len(missing) <= 2):
            curr.append(i)
            missing.discard(i)
            solve(curr)
            missing.add(i)
            curr.pop()

if mid_optimize:
    missing = set(chain(range(1, mid_start + k), range(mid_end - k, n)))
else:
    missing = set(range(1, n))
solve([0])
print_curr_best()
