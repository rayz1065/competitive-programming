import time

def inputData():
    data = ['']
    try:
        while True:
            line = input()
            line = '.' + line + '.'
            data.append(line)
    except EOFError:
        pass

    nCols = len(data[1])
    data[0] = '.'*nCols
    data.append('.'*nCols)

    return data

def inRange(seatMap, r, c):
    return r >= 0 and c >= 0 and r < len(seatMap) and c < len(seatMap[0])

def printMap(seatMap):
    print('\033[' + str(len(seatMap)) + 'A' )
    for x in seatMap:
        print(x)
    print()

def isFreeSeat(seatMap, r, c):
    return seatMap[r][c] == 'L'

def isOccupiedSeat(seatMap, r, c):
    return seatMap[r][c] == '#'

def countOccAdj(seatMap, r, c):
    s = 0
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i != 0 or j != 0:
                s+= isOccupiedSeat(seatMap, r + i, c + j)
    return s

def countOccVisib(seatMap, r, c):
    s = 0
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i != 0 or j != 0:
                _r, _c, r, c = r, c, r + i, c + j
                while inRange(seatMap, r, c) and seatMap[r][c] == '.':
                    r+= i
                    c+= j
                if inRange(seatMap, r, c) and isOccupiedSeat(seatMap, r, c):
                    s+= 1
                r, c = _r, _c
    return s

def nextStep(seatMap: list):
    newMap = []
    nRows = len(seatMap)
    nCols = len(seatMap[0])
    for r in range(nRows):
        newLine = ''
        for c in range(nCols):
            if r == 0 or c == 0 or r == nRows - 1 or c == nCols - 1:
                newLine+= '.'
            elif isFreeSeat(seatMap, r, c) and countOccAdj(seatMap, r, c) == 0:
                newLine+= '#'
            elif isOccupiedSeat(seatMap, r, c) and countOccAdj(seatMap, r, c) >= 4:
                newLine+= 'L'
            else:
                newLine+= seatMap[r][c]
        newMap.append(newLine)

    return newMap

def nextStep2(seatMap: list):
    newMap = []
    nRows = len(seatMap)
    nCols = len(seatMap[0])
    for r in range(nRows):
        newLine = ''
        for c in range(nCols):
            if r == 0 or c == 0 or r == nRows - 1 or c == nCols - 1:
                newLine+= '.'
            elif isFreeSeat(seatMap, r, c) and countOccVisib(seatMap, r, c) == 0:
                newLine+= '#'
            elif isOccupiedSeat(seatMap, r, c) and countOccVisib(seatMap, r, c) >= 5:
                newLine+= 'L'
            else:
                newLine+= seatMap[r][c]
        newMap.append(newLine)

    return newMap

def cmpMaps(map1: list, map2: list):
    for r, r2 in zip(map1, map2):
        if r != r2:
            return False
    return True

def countOccupied(seatMap: list):
    s = 0
    for row in seatMap:
        for c in row:
            s+= (c == '#')
    return s

def part1(seatMap: list):
    lastMap = seatMap
    while True:
        seatMap = nextStep(seatMap)
        if cmpMaps(lastMap, seatMap):
            break
        lastMap = seatMap
    return countOccupied(lastMap)

def part2(seatMap: list):
    lastMap = seatMap
    while True:
        seatMap = nextStep2(seatMap)
        if cmpMaps(lastMap, seatMap):
            break
        printMap(seatMap)
        lastMap = seatMap
    return countOccupied(lastMap)
            


def main():
    data = inputData()
    # print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()