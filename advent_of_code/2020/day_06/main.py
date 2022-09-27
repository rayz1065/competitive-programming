def inputData():
    data = []
    currGroup = []

    try:
        while True:
            line = input()
            if len(line) == 0:
                data.append(currGroup)
                currGroup = []
            else:
                currGroup.append(line)
    except EOFError:
        pass

    data.append(currGroup)
    return data

def countForGroupAnyone(groupAnswers):
    found = dict()
    for personAnswers in groupAnswers:
        for answer in personAnswers:
            if answer not in found:
                found[answer] = True
    return len(found)


def countForGroupEveryone(groupAnswers):
    count = dict()
    for personAnswers in groupAnswers:
        for answer in personAnswers:
            count[answer] = count.get(answer, 0) + 1

    members = len(groupAnswers)
    counts = count.values()
    everyone = list(filter(lambda x: x == members, counts))
    return len(everyone)

def part1(data):
    s = 0
    for group in data:
        s+= countForGroupAnyone(group)
    return s

def part2(data):
    s = 0
    for group in data:
        s+= countForGroupEveryone(group)
    return s

def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()