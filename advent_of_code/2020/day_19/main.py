import re

def inputData():
    rules = {}
    lines = []
    while (line:= input()) != '':
        match = re.fullmatch(r'(\d+):\s([\s\d\|]+|\"\w\")', line)
        assert(match != None)
        ruleNum, rule = match.groups()
        rules[int(ruleNum)] = rule
    try:
        while True:
            line = input()
            lines.append(line)
    except EOFError:
        pass
    return (rules, lines)

def getRuleRegex(rules, parsedRules, ruleNum):
    if parsedRules.get(ruleNum, None) != None:
        return parsedRules[ruleNum]

    rule: str = rules[ruleNum]
    if rule[0] == '"':
        parsedRules[ruleNum] = rule[1]
        return parsedRules[ruleNum]
    
    rulePiecies = rule.split(' | ')
    pRulePiecies = []
    for rulePiece in rulePiecies:
        joinedRules = [int(x) for x in rulePiece.split(' ')]
        pJoinedRules = []
        for rule in joinedRules:
            if rule != ruleNum:
                pJoinedRules.append(getRuleRegex(rules, parsedRules, rule))
            else:
                pJoinedRules.append('+')


        if len(pJoinedRules) > 1 and pJoinedRules[1] == '+':
            if len(pJoinedRules) == 2:
                pRule = '(' + pJoinedRules[0] + ')+'
            else:
                pTmpSplit = []
                for repetitions in range(1, 5): # doesn't repeat more than 4 times
                    pTmpSplit.append(pJoinedRules[0]*repetitions + pJoinedRules[2]*repetitions)
                pRule = '(' + '|'.join(pTmpSplit) + ')'
        else:
            pRule = ''.join(pJoinedRules)
        pRulePiecies.append(''.join(pRule))
    
    mergedRule = '|'.join(pRulePiecies)
    if len(rulePiecies) > 1:
        mergedRule = '(' + mergedRule + ')'
    parsedRules[ruleNum] = mergedRule
    return parsedRules[ruleNum]

def part1(rules, lines):
    parsedRules = {}
    ruleZeroRegex = re.compile(getRuleRegex(rules, parsedRules, 0))

    correctlyParsed = []
    for line in lines:
        match = ruleZeroRegex.fullmatch(line)
        if match != None:
            correctlyParsed.append(line)
    return len(correctlyParsed)

def part2(rules, lines):
    rules[8] = '42 | 42 8'
    rules[11] = '42 31 | 42 11 31'
    parsedRules = {}
    ruleZeroRegex = re.compile(getRuleRegex(rules, parsedRules, 0))
    correctlyParsed = []
    for line in lines:
        matches = ruleZeroRegex.fullmatch(line)
        if matches != None:
            correctlyParsed.append(line)
    return len(correctlyParsed)

def main():
    rules, lines = inputData()
    print("1)", part1(rules, lines))
    print("2)", part2(rules, lines))

if __name__ == "__main__":
    main()