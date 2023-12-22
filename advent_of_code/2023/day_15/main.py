import re
from collections import namedtuple

Lense = namedtuple("Lense", ["label", "focal"])


def my_hash(string):
    res = 0
    for c_ in string:
        res += ord(c_)
        res = res * 17
        res = res % 256

    return res


def part_1(sequence):
    return sum(my_hash(x) for x in sequence)


def print_hashmap(hashmap):
    for box, lenses in enumerate(hashmap):
        if len(lenses) > 0:
            print(box, lenses)


def box_focussing_power(box, lenses: list[Lense]):
    res = 0
    for lense_idx, (label, focal) in enumerate(lenses):
        res += (box + 1) * (lense_idx + 1) * focal

    return res


def part_2(sequence):
    hashmap = [[] for _ in range(256)]
    for operation in sequence:
        res = re.match(r"^(\w+)([=-])(\d*)$", operation)
        label, op, focal = res.groups()
        box = my_hash(label)

        idx = next(
            (idx for idx, value in enumerate(hashmap[box]) if value[0] == label), None
        )

        if operation.endswith("-"):
            if idx is not None:
                hashmap[box].pop(idx)
        else:
            focal = int(focal)
            lense = Lense(label, focal)
            if idx is not None:
                hashmap[box][idx] = lense
            else:
                hashmap[box].append(lense)

            # print_hashmap(hashmap)
            # print()

    return sum(box_focussing_power(box, lenses) for box, lenses in enumerate(hashmap))


def main():
    sequence = input().strip().split(",")
    print("part_1:", part_1(sequence))
    print("part_2:", part_2(sequence))


if __name__ == "__main__":
    main()
