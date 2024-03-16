def find_good_sticks(frequencies):
    found = []
    for stick in sorted(frequencies, key=lambda x: -x):
        while frequencies[stick] >= 2:
            frequencies[stick] -= 2
            found.append(stick)

            if len(found) == 2:
                return found

    return [0, 0]


def main():
    input()
    sticks = [int(x) for x in input().strip().split()]
    frequencies = {}
    for stick in sticks:
        frequencies.setdefault(stick, 0)
        frequencies[stick] += 1

    good_sticks = find_good_sticks(frequencies)

    print(good_sticks[0] * good_sticks[1])


if __name__ == "__main__":
    main()
