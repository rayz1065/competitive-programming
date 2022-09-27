from itertools import tee

def inputData():
    data = []

    try:
        while True:
            line = input()
            data.append(line)
    except EOFError:
        pass

    return data

def findPos(posString):
    minRow, maxRow = 0, 127
    minCol, maxCol = 0, 7

    for c in posString:
        if c == 'F':
            maxRow = (minRow + maxRow)//2
        if c == 'B':
            minRow = (minRow + maxRow)//2 + 1
        if c == 'L':
            maxCol = (minCol + maxCol)//2
        if c == 'R':
            minCol = (minCol + maxCol)//2 + 1
    
    assert(minCol == maxCol and minRow == maxRow)
    return (minRow, maxCol)

def calcSeatId(row, col):
    return row*8 + col

def part1(posStrings):
    s = 0
    for posStr in posStrings:
        row, col = findPos(posStr)
        s = max(s, calcSeatId(row, col))
    return s

def pairwise(iterable):
    "s -> (s0,s1), (s1,s2), (s2, s3), ..."
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)

def part2(posStrings):
    occupiedSeats = []
    for posStr in posStrings:
        row, col = findPos(posStr)
        seatId = calcSeatId(row, col)
        occupiedSeats.append(seatId)
    occupiedSeats.sort()
    for a, b in pairwise(occupiedSeats):
        if b != a + 1:
            return a + 1
    return None

def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()