import re
import numpy
from typing import List
import itertools
from math import sqrt
import sys

class TileBorder:
    tileId: int
    borderOrientation: int
    border: list

    matchingTileId: int
    matchingBorderOrientation: int
    extraRotation: int
    flipped: bool

    isMatchFlipped: bool

    def __init__(self, tileId, border, borderOrientation):
        self.tileId = tileId
        self.borderOrientation = borderOrientation
        self.border = border
        self.matchingTileId = None
        self.matchingBorderOrientation = None
        self.extraRotation = 0
        self.flipped = False
        self.isMatchFlipped = False

    def __str__(self):
        return 'Border {} ({}) of tile {}, matching {} with orientation {}: {}'.format(
            self.borderOrientation,
            self.getActualOrientation(),
            self.tileId,
            self.matchingTileId,
            self.matchingBorderOrientation,
            ''.join(self.border)
        )

    def checkBorder(self, border):
        if self.border == border.border or all(a == b for a, b in zip(self.border, reversed(border.border))):
            if self.border == border.border:
                self.isMatchFlipped = True
                border.isMatchFlipped = True
            self.matchingTileId = border.tileId
            self.matchingBorderOrientation = border.borderOrientation
            border.matchingTileId = self.tileId
            border.matchingBorderOrientation = self.borderOrientation
            return True
        return False

    def getActualOrientation(self):
        return (self.borderOrientation + self.extraRotation + self.flipped*2)%4

    def isMatched(self):
        return self.matchingTileId != None


class Tile:
    tileId: int
    tileMatrix: numpy.ndarray
    dimension: int
    matchingTiles: list

    borders: List[TileBorder]
    flipped: bool

    def __init__(self, tileId: int, tileList: list):
        tile = [[x for x in line] for line in tileList]
        self.tileMatrix = numpy.array(tile)
        self.tileId = tileId
        self.dimension = len(tileList)
        self.matchingTiles = []
        self.matchingBorders = []
        self.flipped = False

        topBorder = [x for x in self.tileMatrix[0]]
        bottomBorder = [x for x in self.tileMatrix[self.dimension - 1]]
        leftBorder = [x[0] for x in self.tileMatrix]
        rightBorder = [x[self.dimension - 1] for x in self.tileMatrix]
        borders = [topBorder, rightBorder, list(reversed(bottomBorder)), list(reversed(leftBorder))]

        self.borders = [TileBorder(tileId, border, orientation) for orientation, border in enumerate(borders)]
        self.removeBorders()
    
    def __str__(self):
        return 'Tile ' + str(self.tileId) + '(' + str(self.flipped) + '):\n' + '\n'.join(' '.join(x) for x in self.tileMatrix)
    
    def removeBorders(self):
        self.tileMatrix = numpy.array([line[1:self.dimension - 1] for line in self.tileMatrix[1:self.dimension - 1]])

    def rotate90(self):
        self.tileMatrix = numpy.rot90(self.tileMatrix)
        for border in self.borders:
            border.extraRotation = (border.extraRotation + 3)%4

    def flip(self):
        self.tileMatrix = numpy.fliplr(self.tileMatrix)
        self.flipped = not self.flipped
        for border in self.borders:
            if border.getActualOrientation()%2 == 1:
                border.flipped = not border.flipped


    def getOrientations(self):
        foundOrientations = {}
        for border in self.borders:
            if border.isMatched():
                foundOrientations[border.getActualOrientation()] = True
        return foundOrientations

def inputData():
    data = []

    try:
        while True:
            tileLine = input()
            tileParsed = re.fullmatch(r'Tile (\d+):', tileLine)
            assert(tileParsed != None)
            tileId = int(tileParsed.groups()[0])

            tileMatrix = []
            while (line := input()) != '':
                tileMatrix.append(line)
            data.append(Tile(tileId, tileMatrix))
    except EOFError:
        pass

    return data

def doTilesMatch(borders1, borders2):
    matchingBorders = []
    for border1 in borders1:
        for border2 in borders2:
            if border1.checkBorder(border2):
                matchingBorders.append((border1, border2))
    return matchingBorders

def part1(tiles: List[Tile]):
    for tile1, tile2 in itertools.combinations(tiles, 2):
        t1Borders = tile1.borders
        t2Borders = tile2.borders
        matching = doTilesMatch(t1Borders, t2Borders)
        if len(matching) > 0:
            tile1.matchingTiles.append(tile2)
            tile2.matchingTiles.append(tile1)
    m2 = [tile for tile in tiles if len(tile.matchingTiles) == 2]
    s = 1
    for tile in m2:
        s*= tile.tileId
    return s

def part2(tiles):
    puzzleWidth = int(sqrt(len(tiles)))
    puzzle: List[List[Tile]] = [[None for i in range(puzzleWidth)] for i in range(puzzleWidth)]
    cornerTiles = [tile for tile in tiles if len(tile.matchingTiles) == 2]
    unusedTiles = {}
    for tile in tiles:
        unusedTiles[tile.tileId] = tile
    
    for r in range(0, puzzleWidth):
        if r == 0:
            cornerTile = cornerTiles[0]
            while set(cornerTile.getOrientations()) != set([1, 2]):
                cornerTile.rotate90()
            
            puzzle[r][0] = cornerTile
            unusedTiles.pop(cornerTile.tileId)
            print('first tile is', cornerTile, sep="\n", end="\n\n")
        else:
            print('finding first tile of row')
            lastTile = puzzle[r - 1][0]
            bottomBorder = next(filter(lambda border: border.getActualOrientation() == 2, lastTile.borders))
            matchedTile = unusedTiles[bottomBorder.matchingTileId]
            matchedBorder = next(filter(lambda border: border.borderOrientation == bottomBorder.matchingBorderOrientation, matchedTile.borders))

            if bottomBorder.isMatchFlipped == (lastTile.flipped == matchedTile.flipped):
                matchedTile.flip()
            while matchedBorder.getActualOrientation() != 0:
                matchedTile.rotate90()
            puzzle[r][0] = matchedTile
            unusedTiles.pop(matchedTile.tileId)
            print('first tile or row {} is'.format(r), matchedTile, matchedBorder, sep='\n', end='\n\n')
        for c in range(1, puzzleWidth):
            print('finding tile ({}, {})'.format(r, c))
            lastTile = puzzle[r][c - 1]
            rightBorder = next(filter(lambda border: border.getActualOrientation() == 1, lastTile.borders))
            matchedTile = unusedTiles[rightBorder.matchingTileId]
            matchedBorder = next(filter(lambda border: border.borderOrientation == rightBorder.matchingBorderOrientation, matchedTile.borders))

            if rightBorder.isMatchFlipped == (lastTile.flipped == matchedTile.flipped):
                print('need to flip:', lastTile, matchedTile, rightBorder.isMatchFlipped, rightBorder.flipped, sep='\n')
                matchedTile.flip()
            while matchedBorder.getActualOrientation() != 3:
                matchedTile.rotate90()
            puzzle[r][c] = matchedTile
            unusedTiles.pop(matchedTile.tileId)
            print("({}, {})".format(r, c), matchedTile, sep='\n', end='\n\n')

    puzzleText = ''
    for _r in range(puzzleWidth):
        for rsmall in range(8):
            for tile in puzzle[_r]:
                puzzleText+= ''.join(tile.tileMatrix[rsmall]) + ''
            puzzleText+= '\n'
    print(puzzleText, file=sys.stderr)
    return 2209

def printMonster(scarySeaMonster):
    monsterStr = '\n'.join([''.join(line) for line in scarySeaMonster])
    lineLen = 8*12 - len(scarySeaMonster[0]) + 1
    monsterStr = monsterStr.replace('\n', '[.#A\\n]{' + str(lineLen) + '}').replace(' ', '.')

def main():
    tiles = inputData()
    print("1)", part1(tiles))
    print("2)", part2(tiles))
    scarySeaMonster = numpy.array([[c for c in line] for line in "                  # \n#    ##    ##    ###\n #  #  #  #  #  #   ".split('\n')])

if __name__ == "__main__":
    main()