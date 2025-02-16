PRUNE_MOD = 16777216

def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(int(line))
    return res

def mix(a, b):
    return a ^ b

def prune(a):
    return a % PRUNE_MOD

def advance_rng(a):
    a = prune(mix(a * 64, a))
    a = prune(mix(a // 32, a))
    a = prune(mix(a * 2048, a))
    return a

def get_changes(seed):
    deltas = {}
    changes = []
    for _ in range(2000):
        next_seed = advance_rng(seed)
        next_price = next_seed % 10
        changes.append(next_price - (seed % 10))
        if len(changes) > 4:
            changes = changes[1:]
        key = tuple(changes)
        if len(key) == 4 and key not in deltas:
            deltas[key] = next_price
        seed = next_seed
    return deltas

def part_1(seeds):
    res = 0
    for seed in seeds:
        for _ in range(2000):
            seed = advance_rng(seed)
        res += seed
    return res

def part_2(seeds):
    price_deltas = {}
    for seed in seeds:
        for changes, value in get_changes(seed).items():
            price_deltas.setdefault(changes, 0)
            price_deltas[changes] += value
    return max(price_deltas.values())

def main():
    seeds = read_input()
    print("part1", part_1(seeds))
    print("part2", part_2(seeds))


if __name__ == '__main__':
    main()
