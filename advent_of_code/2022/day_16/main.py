import re

MAX_TIME = 30

def read_input ():
    valves = []
    try:
        while True:
            line = input()
            res = re.match(r'^Valve (\w+) has flow rate=(\d+); tunnels? leads? to valves? ([\w,\s]+)$', line)
            assert res is not None, line
            valve, rate, tunnels = res.groups()
            valves.append((valve, int(rate), tunnels.split(', ')))
    except EOFError:
        pass
    return valves

memo_1 = {}

def rec_part_1 (pos, active, time):
    base_val = sum(valves_rates[x] for x in active)
    s = base_val
    if time == MAX_TIME:
        return s
    if (pos, active, time) in memo_1:
        return memo_1[pos, active, time]
    if pos not in active and valves_rates[pos] > 0:
        new_active = tuple(sorted([*active, pos]))
        s = max(s, base_val + rec_part_1(pos, new_active, time + 1))
    for adj in valves_graph[pos]:
        s = max(s, base_val + rec_part_1(adj, active, time + 1))
    memo_1[pos, active, time] = s
    return s

def part_1 ():
    return rec_part_1('AA', (), 1)

valves = read_input()
valves_graph = { valve: reachable for valve, _, reachable in valves }
valves_rates = { valve: rate for valve, rate, _ in valves }

def rewrite_problem ():
    # assign ids
    ids = {}
    next_id = 0
    for valve, rate, _ in valves:
        if rate > 0 and valve not in ids:
            ids[valve] = next_id
            next_id += 1
    for valve, *_ in valves:
        if valve not in ids:
            ids[valve] = next_id
            next_id += 1
    num_branches = sum(len(adj) for _, _, adj in valves)
    rates = []
    for valve, vid in ids.items():
        rates.append(valves_rates[valve])
    print(len(valves), num_branches, ids['AA'])
    print(' '.join(str(x) for x in rates))
    for valve, _, adj in valves:
        for valve_2 in adj:
            print(ids[valve], ids[valve_2])

def main ():
    # print('part_1:', part_1())
    rewrite_problem()

if __name__ == '__main__':
    main()
