import itertools

sumLen = 25

def inputData():
    data = []
    try:
        while True:
            line = input()
            data.append(int(line))
    except EOFError:
        pass
    
    return data

def canSumUpTo(values: list, toSum: int):
    for a, b in itertools.combinations(values, r=2):
        if a != b and a + b == toSum:
            return True
    return False

def part1(data: list):
    currSum = []
    for i in range(sumLen):
        currSum.append(data[i])
    
    for i in range(sumLen, len(data)):
        if not canSumUpTo(currSum, data[i]):
            return data[i]
        currSum.append(data[i])
        currSum.remove(currSum[0])

def sumBetween(prefixSum: list, a: int, b: int):
    if a == 0:
        return prefixSum[b - 1]
    return prefixSum[b - 1] - prefixSum[a - 1]

def part2(data: list, invalid: int):
    prefixSum = list(itertools.accumulate(data))
    for a in range(0, len(data) - 2):
        for b in range(a + 2, len(data)):
            if sumBetween(prefixSum, a, b) == invalid:
                return (min(data[a:b]), max(data[a:b]))

def main():
    data = inputData()
    invalid = part1(data)
    print("1)", invalid)
    minS, maxS = part2(data, invalid)
    print("2)", minS + maxS)

if __name__ == "__main__":
    main()