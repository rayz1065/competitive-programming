from collections import defaultdict

def addOcc(coords: tuple, coordsDiff: list, occurencies: defaultdict):
    if len(coords) == len(coordsDiff):
        if len([x for x in coordsDiff if x != 0]) != 0:
            calcCoords = tuple(v + d for v, d in zip(coords, coordsDiff))
            occurencies[calcCoords]+= 1
        return
    for i in range(-1, 2):
        coordsDiff.append(i)
        addOcc(coords, coordsDiff, occurencies)
        coordsDiff.pop()

def getEmptyState():
    return defaultdict(lambda: 0)

def isInState(state: defaultdict, coords: tuple):
    return state[coords]

def nextStep(state: defaultdict):
    occurencies = defaultdict(lambda: 0)
    for coords in state.keys():
        addOcc(coords, [], occurencies)
    
    newState = getEmptyState()
    for coords, occ in occurencies.items():
        inState = isInState(state, coords)
        if inState and (occ == 2 or occ == 3):
            newState[coords] = True
        if not inState and occ == 3:
            newState[coords] = True
    return newState
    

def inputData():
    lines = []
    try:
        while True:
            line = input()
            lines.append(line)
    except EOFError:
        pass

    return lines

def iterateSteps(state: defaultdict, steps: int):
    for _ in range(6):
        state = nextStep(state)
    return state

def part1(lines: list):
    state = getEmptyState()
    for x, line in enumerate(lines):
        for y, c in enumerate(line):
            if c == '#':
                state[(x, y, 0)] = True
    return len(iterateSteps(state, 6))

def part2(lines: list):
    state = getEmptyState()
    for x, line in enumerate(lines):
        for y, c in enumerate(line):
            if c == '#':
                state[(x, y, 0, 0)] = True
    return len(iterateSteps(state, 6))


def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()