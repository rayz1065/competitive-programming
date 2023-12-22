SCORES = [
    -1,
    25,
    18,
    15,
    12,
    10,
    8,
    6,
    4,
    2,
    1,
]


def main():
    t = int(input())
    for _ in range(t):
        assert input() == ""
        n = int(input())
        positions = [int(x) for x in input().strip().split()]

        best_score = 0
        driver_score = 0
        for position in positions:
            best_score += SCORES[2] if position == 1 else SCORES[1]
            driver_score += 0 if position >= len(SCORES) else SCORES[position]

        print("Champion" if driver_score >= best_score else "Practice harder")


if __name__ == "__main__":
    main()
