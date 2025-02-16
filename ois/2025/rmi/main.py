def get_min_position(my_score, scores_a, scores_b):
    i = 0
    j = len(scores_a) - 1
    res = 0

    while j >= 0:
        if scores_a[i] + scores_b[j] <= my_score:
            res += 1
            i += 1
        j -= 1

    return len(scores_a) - res


def get_max_position(my_score, scores_a, scores_b):
    i = 0
    j = len(scores_a) - 1
    res = 0

    while i < len(scores_a):
        if scores_a[i] + scores_b[j] > my_score:
            res += 1
            j -= 1
        i += 1

    return res


def main():
    a, b, _ = (int(x) for x in input().strip().split())
    scores_a = sorted(int(x) for x in input().strip().split())
    scores_b = sorted(int(x) for x in input().strip().split())
    my_score = a + b

    print(
        get_min_position(my_score, scores_a, scores_b) + 1,
        get_max_position(my_score, scores_a, scores_b) + 1,
    )


if __name__ == "__main__":
    main()
