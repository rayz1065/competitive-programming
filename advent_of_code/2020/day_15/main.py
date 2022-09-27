def inputData():
    line = input()
    numbers = line.split(',')
    return [int(x) for x in numbers]

def findNumInSeq(numbers, idxToFind):
    lastSeen = dict()
    numbersSaid = 0
    lastSaid = None

    for n in numbers:
        if lastSaid != None:
            numbersSaid+= 1
            lastSeen[lastSaid] = numbersSaid
        lastSaid = n

    while numbersSaid < idxToFind - 1:
        lsls = lastSeen.get(lastSaid, None)
        if lsls == None:
            n = 0
        else:
            n = numbersSaid + 1 - lsls
        numbersSaid+= 1
        lastSeen[lastSaid] = numbersSaid
        lastSaid = n
    return lastSaid

def part1(numbers):
    return findNumInSeq(numbers, 2020)

def part2(numbers):
    return findNumInSeq(numbers, 30000000)

def main():
    numbers = inputData()
    print("1)", part1(numbers))
    print("2)", part2(numbers))

if __name__ == "__main__":
    main()