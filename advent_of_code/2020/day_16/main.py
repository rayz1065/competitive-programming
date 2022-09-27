import re
interestingFields = 'departure'

def inputData():
    nearbyTickets = []
    yourTicket = None
    rules = dict()

    while len(line:=input()) > 0:
        matches = re.fullmatch(r'(.+): (\d+)-(\d+) or (\d+)-(\d+)', line)
        assert(matches != None)
        fieldName, f, t, f2, t2 = matches.groups()
        f, t, f2, t2 = int(f), int(t), int(f2), int(t2)
        rules[fieldName] = [(f, t), (f2, t2)]
    assert(input() == 'your ticket:')
    yourTicket = [int(x) for x in input().split(',')]
    assert(input() == '')
    assert(input() == 'nearby tickets:')

    try:
        while True:
            nearbyTickets.append([int(x) for x in input().split(',')])
    except EOFError:
        pass

    return (nearbyTickets, yourTicket, rules)

def checkTicketField(rules, ticketField):
    for rule in rules.values():
        for f, t in rule:
            if f <= ticketField <= t:
                return True
    return False

def checkTicket(rules, ticket):
    c = []
    for field in ticket:
        if not checkTicketField(rules, field):
            c.append(field)
    return c

def checkFieldAgainstRule(rule: list, field):
    for f, t in rule:
        if f <= field <= t:
            return True
    return False

def checkFieldsAgainstRule(rule, fields):
    for field in fields:
        if not checkFieldAgainstRule(rule, field):
            return False
    return True

def findCorrectRules(i: int, validRulesForField: list, mappedRules: dict):
    if i == len(validRulesForField):
        return mappedRules
    fieldIdx, validRules = validRulesForField[i]
    for validRule in validRules:
        if mappedRules.get(validRule, None) == None:
            mappedRules[validRule] = fieldIdx
            s = findCorrectRules(i + 1, validRulesForField, mappedRules)
            if s != None:
                return s
            mappedRules[validRule] = None
    return None


def part1(rules, nearbyTickets):
    c = []
    for ticket in nearbyTickets:
        c.extend(checkTicket(rules, ticket))
    return sum(c)

def part2(rules, nearbyTickets, yourTicket):
    validTickets = [x for x in nearbyTickets if len(checkTicket(rules, x)) == 0]

    validTickets.append(yourTicket)

    validRulesForField = []
    for i in range(len(yourTicket)):
        validRules = []
        fields = [x[i] for x in validTickets]
        for fieldName, rule in rules.items():
            if checkFieldsAgainstRule(rule, fields):
                # print('rule', fieldName, 'is valid for fields', i)
                validRules.append(fieldName)
        validRulesForField.append(validRules)

    validRulesSorted = [(i, x) for i, x in enumerate(validRulesForField)]
    validRulesSorted.sort(key = lambda ix: len(ix[1]))
    
    prod = 1
    mappedRules: dict = findCorrectRules(0, validRulesSorted, dict())
    for fieldName, fieldIdx in mappedRules.items():
        if fieldName.startswith(interestingFields):
            print(yourTicket[fieldIdx])
            prod*= yourTicket[fieldIdx]
    return prod
    

def main():
    nearbyTickets, yourTicket, rules = inputData()
    print("1)", part1(rules, nearbyTickets))
    print("2)", part2(rules, nearbyTickets, yourTicket))

if __name__ == "__main__":
    main()