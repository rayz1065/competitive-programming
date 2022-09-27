import itertools

def inputData():
    data = []
    try:
        while True:
            line = input()
            data.append(int(line))
    except EOFError:
        pass
    return data

def pairwise(iterable):
    one, two = itertools.tee(iterable, 2)
    next(two)
    return zip(one, two)

def part1(adapters: list):
    diffs = dict()
    for a, b in pairwise(adapters):
        diffs[b - a] = diffs.get(b - a, 0) + 1
    return diffs[1] * diffs[3]

def solvePart2(i: int, adapters: list, memo: dict):
    if i == len(adapters) - 1:
        return 1
    if memo.get(i) != None:
        return memo[i]
    j = i + 1
    s = 0
    while j < len(adapters) and adapters[i] + 3 >= adapters[j]:
        s+= solvePart2(j, adapters, memo)
        j+= 1

    memo[i] = s
    return s

def part2(adapters: list):
    return solvePart2(0, adapters, dict())

def main():
    adapters = inputData()
    adapters.append(0)
    adapters.sort()
    adapters.append(adapters[-1] + 3)

    print("1)", part1(adapters))
    print("2)", part2(adapters))

if __name__ == "__main__":
    main()