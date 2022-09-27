import re

def inputData():
    data = []

    try:
        while True:
            matches = re.match(r'(\d+)-(\d+) (\w): (\w+)', input())
            groups = matches.groups()
            data.append((int(groups[0]), int(groups[1]), groups[2], groups[3]))
    except EOFError:
        pass

    return data

def part1(data):
    s = 0
    for d in data:
        mn, mx, ch, pw = d
        s+= mn <= pw.count(ch) <= mx
    return s

def part2(data):
    s = 0
    for d in data:
        p1, p2, ch, pw = d
        s+= (pw[p1 - 1] == ch) ^ (pw[p2 - 1] == ch)
    return s

def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()