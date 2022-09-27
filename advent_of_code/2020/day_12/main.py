import re

directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
direMap = {'N': 0, 'E': 1, 'S': 2, 'W': 3}

def inputData():
    data = []

    try:
        while True:
            line = input()
            groups = re.fullmatch(r'(\w)(\d+)', line).groups()
            az, am = groups
            data.append((az, int(am)))
    except EOFError:
        pass

    return data

def part1(data: list):
    x, y, dire = 0, 0, 1
    for az, am in data:
        if az == 'L':
            dire = (dire + 4 - am//90)%4
        elif az == 'R':
            dire = (dire + am//90)%4
        elif az == 'F':
            xS, yS = directions[dire]
            x, y = x + xS*am, y + yS*am
        elif direMap.get(az, None) != None:
            tmpDire = direMap[az]
            xS, yS = directions[tmpDire]
            x, y = x + xS*am, y + yS*am
        else:
            raise Exception('Instruction not recognized')
    return abs(x) + abs(y)

def part2(data: list):
    x, y = 0, 0
    wayX, wayY = 10, 1
    for az, am in data:
        if az == 'L':
            am = 360 - am
            az = 'R'
        if az == 'R':
            if am == 90:
                wayX, wayY = wayY, -wayX
            elif am == 180:
                wayX, wayY = -wayX, -wayY
            elif am == 270:
                wayX, wayY = -wayY, wayX
        elif az == 'F':
            x, y = x + wayX*am, y + wayY*am
        elif direMap.get(az, None) != None:
            tmpDire = direMap[az]
            xS, yS = directions[tmpDire]
            wayX, wayY = wayX + xS*am, wayY + yS*am
        else:
            raise Exception('Instruction not recognized')
    return abs(x) + abs(y)

def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))


if __name__ == "__main__":
    main()