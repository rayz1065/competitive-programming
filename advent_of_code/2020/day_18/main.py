import re

def inputData():
    data = []

    try:
        while True:
            line = input()
            data.append(line)
    except EOFError:
        pass
    return data

def getOp(expr):
    if expr[0] == '(':
        return getPar(expr, 0)
    if '0' <= expr[0] <= '9':
        match = re.match(r'(\d+)', expr)
        assert(match != None)
        return match.groups()[0]
    assert(False)

def eval(expr):
    if expr[0] == '(' and findClosing(expr, 0) == len(expr):
        return eval(expr[1:len(expr) - 1])
    match = re.fullmatch(r'\d+', expr)
    if match != None:
        return int(expr)
    return solve1(expr)

def eval2(expr):
    if expr[0] == '(' and findClosing(expr, 0) == len(expr):
        return eval2(expr[1:len(expr) - 1])
    match = re.fullmatch(r'\d+', expr)
    if match != None:
        return int(expr)
    return solve2(expr)

def solve1(expr):
    i = 0
    lft = getOp(expr)
    i+= len(lft)
    lft = eval(lft)
    assert(i < len(expr))
    while i < len(expr):
        operand, i = expr[i], i + 1
        rgt = getOp(expr[i:])
        i+= len(rgt)
        rgt = eval(rgt)
        assert(operand == '+' or operand == '*')
        if operand == '+':
            lft = lft + rgt
        elif operand == '*':
            lft = lft * rgt
    return lft

def solve2(expr):
    i = 0
    lft = getOp(expr)
    i+= len(lft)
    opAndOperands = [eval2(lft)]
    while i < len(expr):
        operand, i = expr[i], i + 1
        rgt = getOp(expr[i:])
        opAndOperands.append(operand)
        opAndOperands.append(eval2(rgt))
        i+= len(rgt)
    
    toMul = []
    currAdd = 0
    for i, val in enumerate(opAndOperands):
        if i%2 == 0:
            currAdd+= opAndOperands[i]
        elif i%2 == 1 and val == '*':
            toMul.append(currAdd)
            currAdd = 0
        elif i%2 == 1 and val == '+':
            pass
        else:
            print(opAndOperands)
            assert(False)
    
    if currAdd > 0:
        toMul.append(currAdd)
    print(opAndOperands, '->', toMul)
    s = 1
    for x in toMul:
        s*= x
    return s

def findClosing(expr: str, i: int):
    assert(expr[i] == '(')
    openFound = 1
    while openFound > 0:
        i+= 1
        if expr[i] == '(':
            openFound+= 1
        elif expr[i] == ')':
            openFound-= 1
    end = i + 1
    return end

def getPar(expr: str, i: int):
    start = i
    openFound = 1
    while openFound > 0:
        i+= 1
        if expr[i] == '(':
            openFound+= 1
        elif expr[i] == ')':
            openFound-= 1
    end = i + 1
    return expr[start:end]

def part1(lines):
    return sum([solve1(line.replace(' ', '')) for line in lines])

def part2(lines):
    return sum([solve2(line.replace(' ', '')) for line in lines])

def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()