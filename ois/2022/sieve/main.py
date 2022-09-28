import time

start_time = time.time_ns() / 10 ** 9
n, m = (int(x) for x in input().split())
numbers = [int(x) for x in input().split()]
neighbors_memo = {}
neigh_ahead_memo = {}
best = n + 1

def is_marked (number, picked):
    return any(x % number == 0 or number % x == 0 for x in picked)

def found_sol (picked):
    return all(is_marked(x, picked) for x in numbers)

def no_brainer_1 (picked, i=0):
    curr_best = n + 1
    if len(picked) >= best or (time.time_ns() / 10 ** 9) - start_time > 0.5:
        return curr_best
    if i == len(numbers):
        if not found_sol(picked):
            # not a valid solution
            return curr_best
        # print(picked)
        globals()['best'] = len(picked)
        return len(picked)

    if not is_marked(numbers[i], picked):
        # try picking
        picked.append(numbers[i])
        curr_best = min(curr_best, no_brainer_1(picked, i + 1))
        picked.pop()

        if not must_pick(i):
            # try skipping
            curr_best = min(curr_best, no_brainer_1(picked, i + 1))
    else:
        # already marked, no point in picking it
        curr_best = min(curr_best, no_brainer_1(picked, i + 1))
    return curr_best

def must_pick (i):
    # check if the previous numbers have all been skipped
    number = numbers[i]
    return len(neigh_ahead(number)) == 0

def neighbors (number):
    if number not in neighbors_memo:
        picked = [number]
        marked = set(x for x in numbers if is_marked(x, picked)) - set(picked)
        neighbors_memo[number] = marked
    return neighbors_memo[number]

def neigh_ahead (number):
    if number not in neigh_ahead_memo:
        i = order[number]
        ahead = numbers[i + 1:]
        neigh_ahead_memo[number] = neighbors(number).intersection(ahead)
    return neigh_ahead_memo[number]

def print_info ():
    for number in numbers:
        marked = neighbors(number)
        print(f"For {number} picked are {sorted(marked)} for a total of {len(marked)}, "
              f"neigh ahead are {neigh_ahead(number)}")

# remove the ones without neighbors
start_picked = [x for x in numbers if len(neighbors(x)) == 0]
numbers = list(set(numbers).difference(start_picked))
# apply some heuristic
numbers = sorted(numbers, key=lambda x: -len(neighbors(x)))
order = { x: i for i, x in enumerate(numbers) }
# print_info()
no_brainer_1(start_picked)
print(best)
