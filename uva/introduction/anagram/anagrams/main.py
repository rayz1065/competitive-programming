def normalize (word):
    return ''.join(sorted(word.replace(' ', '')))


def ordered_pairs (items):
    items = sorted(items)
    for i, a in enumerate(items):
        for j, b in enumerate(items):
            if i >= j:
                continue
            yield a, b


t = int(input().strip())
input() # empty line

for tc in range(t):
    words = []
    while True:
        try:
            line = input()
        except EOFError:
            break
        if line == '':
            break
        words.append(line)

    # the order of the output is very specific...
    for a, b in ordered_pairs(words):
        if normalize(a) == normalize(b):
            print(a, '=', b)

    if tc + 1 < t:
        print()
