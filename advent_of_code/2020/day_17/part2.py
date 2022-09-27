from collections import defaultdict

def getEmptyMap(val = False):
    return defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: val))))

def countCells(state: defaultdict):
    s = 0
    for xCube in state.values():
        for yPlane in xCube.values():
            for zLine in yPlane.values():
                for val in zLine.values():
                    if val:
                        s+= 1
    return s

def addOcc(_x, _y, _z, _w, occurencies: defaultdict):
    for x in range(_x - 1, _x + 2):
        for y in range(_y - 1, _y + 2):
            for z in range(_z - 1, _z + 2):
                for w in range(_w - 1, _w + 2):
                    if not (x == _x and y == _y and z == _z and w == _w):
                        occurencies[x][y][z][w]+= 1

def nextStep(state: defaultdict):
    occurencies = getEmptyMap(0)
    for x, xCube in state.items():
        for y, yPlane in xCube.items():
            for z, zLine in yPlane.items():
                for w, v in zLine.items():
                    if v:
                        addOcc(x, y, z, w, occurencies)
    newState = getEmptyMap()
    for x, xCube in occurencies.items():
        for y, yPlane in xCube.items():
            for z, zLine in yPlane.items():
                for w, occ in zLine.items():
                    if state[x][y][z][w] and (occ == 2 or occ == 3):
                        newState[x][y][z][w] = True
                    if not state[x][y][z][w] and occ == 3:
                        newState[x][y][z][w] = True
    return newState
    

def inputData():
    lines = []
    try:
        while True:
            line = input()
            lines.append(line)
    except EOFError:
        pass

    state = getEmptyMap()
    for x, line in enumerate(lines):
        for y, c in enumerate(line):
            if c == '#':
                state[x][y][0][0] = True
    return state

def part2(currState):
    for _ in range(6):
        print(_, countCells(currState))
        ns = nextStep(currState)
        currState = ns
    return countCells(currState)

def main():
    data = inputData()
    print("2)", part2(data))

if __name__ == "__main__":
    main()