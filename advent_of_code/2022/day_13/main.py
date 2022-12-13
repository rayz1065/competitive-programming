import json
from functools import cmp_to_key, reduce

def read_input ():
    pairs = []
    try:
        while True:
            line1 = json.loads(input())
            line2 = json.loads(input())
            pairs.append((line1, line2))
            assert input() == ''
    except EOFError:
        pass
    return pairs

def comp (left, right):
    # returns -1 for left < right, 0 for left = right, 1 for left > right
    if isinstance(left, int) and isinstance(right, int):
        if left < right:
            return -1
        if left == right:
            return 0
        return 1
    if isinstance(left, int):
        return comp([left], right)
    if isinstance(right, int):
        return comp(left, [right])
    for l, r in zip(left, right):
        if comp(l, r) == -1:
            return -1
        if comp(l, r) == 1:
            return 1
    if len(left) < len(right):
        return -1
    if len(left) > len(right):
        return 1
    return 0 # same

def main ():
    pairs = read_input()
    total = 0
    for i, pair in enumerate(pairs):
        left, right = pair
        if comp(left, right) != 1:
            total += i + 1
    print('part_1:', total)
    SEPARATORS = [ [[2]], [[6]] ]
    all_elements = list(SEPARATORS)
    for left, right in pairs:
        all_elements.append(left)
        all_elements.append(right)
    all_elements.sort(key=cmp_to_key(comp))
    separator_indeces = [None] * len(SEPARATORS)
    for i, elem in enumerate(all_elements):
        for sep_id, sep in enumerate(SEPARATORS):
            if comp(elem, sep) == 0:
                separator_indeces[sep_id] = i
    def prod (tot, curr):
        return tot * (curr + 1)
    print('part_2:', reduce(prod, separator_indeces, 1))

main()
