import numpy

def inputData():
    grid = []
    nRows, nCols = 0, 0
    try:
        while True:
            line = input()
            grid.append(line)
            nRows+= 1
            nCols = len(line)
    except EOFError:
        pass

    return (nRows, nCols, grid)

def getCellAt(grid, nRows, nCols, r, c):
    if r >= nRows:
        return '.'
    c = c%nCols
    # print(r,c, nRows, nCols)
    return grid[r][c]

def findTreesWithSlope(nRows, nCols, grid, rSlope, cSlope):
    treesFound = 0
    r, c = 0, 0
    while r < nRows:
        r, c = r + rSlope, c + cSlope
        treesFound+= getCellAt(grid, nRows, nCols, r, c) == '#'
    return treesFound

def part1(nRows, nCols, grid):
    treesFound = 0
    r, c = 0, 0
    while r < nRows:
        r, c = r + 1, c + 3
        treesFound+= getCellAt(grid, nRows, nCols, r, c) == '#'
    return treesFound

def part2(nRows, nCols, grid):
    slopes = [(1, 1), (1, 3), (1, 5), (1, 7), (2, 1)]
    s = 1
    for slope in slopes:
        rSlope, cSlope = slope
        s*= findTreesWithSlope(nRows, nCols, grid, rSlope, cSlope)
    return s

def main():
    nRows, nCols, grid = inputData()
    print("1)", part1(nRows, nCols, grid))
    print("2)", part2(nRows, nCols, grid))

if __name__ == "__main__":
    main()