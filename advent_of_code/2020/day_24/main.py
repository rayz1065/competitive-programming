import re
possibleDirections = {
    'e': (2, 0),
    'se': (1, -1),
    'sw': (-1, -1),
    'w': (-2, 0),
    'nw': (-1, 1),
    'ne': (1, 1),
}

def inputData():
    data = []
    lineRe = re.compile(r'(' + '|'.join(possibleDirections) + ')')
    try:
        while True:
            line = input()
            matches = lineRe.findall(line)
            data.append(matches)
    except EOFError:
        pass
    return data

def getPos(line):
    east, north = 0, 0
    for dire in line:
        dEast, dNorth = possibleDirections[dire]
        east, north = east + dEast, north + dNorth
    return (east, north)

def findStarting(lines):
    found = {}
    for line in lines:
        found[getPos(line)] = found.get(getPos(line), 0) + 1
    return [x for x, y in found.items() if y%2 == 1]

def part1(lines):
    return len(findStarting(lines))

def markNeighbours(position, count):
    east, north = position
    for dE, dN in possibleDirections.values():
        newPos = (east + dE, north + dN)
        count[newPos] = count.get(newPos, 0) + 1
    count[position] = count.get(position, 0) + 100

def step(positions):
    count = {}
    for position in positions:
        markNeighbours(position, count)
    return [position for position, am in count.items() if 101 <= am <= 102 or am == 2]

def part2(lines):
    positions = findStarting(lines)
    for _day in range(100):
        positions = step(positions)
        # print('Day {}: {}'.format(_day + 1, len(positions)))
    return len(positions)

def main():
    lines = inputData()
    print("1)", part1(lines))
    print("2)", part2(lines))

if __name__ == "__main__":
    main()