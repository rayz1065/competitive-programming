import re

myBag = 'shiny gold'



def inputData():
    differentColours = set()
    rules = []

    try:
        while True:
            line = input()
            matches = re.fullmatch(r'(.+) bags contain (.+)\.', line)
            assert(matches != None)
            colour, contentsStr = matches.groups()
            contents = []
            if contentsStr != 'no other bags':
                for content in contentsStr.split(', '):
                    contentMatch = re.fullmatch(r'(\d+) (.+) bags?', content)
                    assert(contentMatch != None)
                    contentAmount, contentColour = contentMatch.groups()
                    contentAmount = int(contentAmount)
                    contents.append((contentAmount, contentColour))
            rules.append((colour, contents))
            if colour not in differentColours:
                differentColours.add(colour)
            for content in contents:
                _, contentColour = content
                if contentColour not in differentColours:
                    differentColours.add(contentColour)

    except EOFError:
        pass
    print(len(differentColours))

    return (differentColours, rules)

def createGraph(rules):
    graph = dict()
    for rule in rules:
        branches = []
        root, contents = rule
        for content in contents:
            branches.append(content)
        graph[root] = branches
    return graph

def canReachMyBag(graph, node):
    if node == myBag:
        return True
    for _, colour in graph[node]:
        if canReachMyBag(graph, colour):
            return True
    return False

def part1(graph, differentColours):
    s = 0
    for colour in differentColours:
        if canReachMyBag(graph, colour) and colour != myBag:
            s+= 1
    return s

def calcInside(graph, node):
    inside = 0
    for am, colour in graph[node]:
        nested = calcInside(graph, colour)
        inside+= (1 + nested) * am
    return inside

def part2(graph):
    return calcInside(graph, myBag)

def main():
    differentColours, rules = inputData()
    graph = createGraph(rules)
    # print(rules)
    print("1)", part1(graph, differentColours))
    print("2)", part2(graph))

if __name__ == "__main__":
    main()