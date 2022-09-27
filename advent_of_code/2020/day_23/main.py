import itertools

def inputData():
    num = int(input())
    return num

class ListCupNode:
    num: int
    nxt = None

    def __init__(self, num):
        self.num = num
    
    def __iter__(self):
        return ListCup(self)

    def __str__(self):
        return str(self.num)

    def setNext(self, nxt):
        self.nxt = nxt

class ListCup:
    currentCup: ListCupNode
    
    def __init__(self, cup):
        self.currentCup = cup
    
    def __iter__(self):
        return self
    
    def __next__(self):
        num = self.currentCup.num
        self.currentCup = self.currentCup.nxt
        return num

    def removeNext(self, am):
        removedCups = []
        itCup = self.currentCup
        for _ in range(am):
            itCup = itCup.nxt
            removedCups.append(itCup)
        self.currentCup.setNext(itCup.nxt)
        return removedCups

def isInList(lst, value):
    try:
        _ = lst.index(value)
        return True
    except ValueError:
        pass
    return False

def cupAdd(n, curr, am):
    return ((curr - 1) + am + n)%n + 1

def nextStep(cups):
    selectedCup = cups[0]
    pickedCups = cups[1:4]
    remainingCups = [cups[0]]
    remainingCups.extend(cups[4:len(cups)])

    destinationCup = cupAdd(len(cups), selectedCup, - 1)
    while not isInList(remainingCups, destinationCup):
        destinationCup = cupAdd(len(cups), destinationCup, - 1)
    destinationIdx = remainingCups.index(destinationCup)
    remainingCups[destinationIdx + 1: destinationIdx + 1] = pickedCups
    
    remainingCups.pop(0)
    remainingCups.append(selectedCup)
    return remainingCups


def part1(cups):
    cups = list(int(x) for x in str(cups))
    for _ in range(100):
        cups = nextStep(cups)
    idx1 = cups.index(1)
    res = cups[idx1 + 1:len(cups)]
    res.extend(cups[0:idx1])
    return ''.join(str(x) for x in res)

def part2(cupsStr):
    cupNums = list(int(x) for x in str(cupsStr))
    cups = [ListCupNode(x) for x in itertools.chain(cupNums, range(len(cupNums) + 1, 1000000 + 1))]
    
    for i in range(len(cups)):
        cups[i].setNext(cups[(i + 1)%len(cups)])
    
    cupsIter = ListCup(cups[0])
    cups.sort(key = lambda x: x.num)

    for _ in range(10000000):
        if _%10000 == 0:
            print(_, end='\r')
        removedCups = cupsIter.removeNext(3)
        currentCup = next(cupsIter)
        destinationCupNum = cupAdd(len(cups), currentCup, - 1)
        while isInList(removedCups, cups[destinationCupNum - 1]):
            destinationCupNum = cupAdd(len(cups), destinationCupNum, - 1)

        destinationCup = cups[destinationCupNum - 1]
        assert(destinationCup.num == destinationCupNum)
        removedCups[len(removedCups) - 1].nxt = destinationCup.nxt
        destinationCup.nxt = removedCups[0]
    print()
    return cups[0].nxt.num * cups[0].nxt.nxt.num
    

def main():
    cups = inputData()
    print("1)", part1(cups))
    print("2)", part2(cups))

if __name__ == "__main__":
    main()