from math import ceil


def is_valid(a_scores, b_scores):
    a_victories = 0
    b_victories = 0
    for i, (a_score, b_score) in enumerate(zip(a_scores, b_scores)):
        if min(a_score, b_score) >= 11:
            return False

        if a_score == 11:
            a_victories += 1
        elif b_score == 11:
            b_victories += 1
        else:
            return False

        if b_victories >= 3:
            return False
        if a_victories >= 3 and i + 1 < len(a_scores):
            return False

    return True


def solve(a, b):
    if a < 33 or a > 55 or b > 55:
        return [[-1, -1]]

    res = []
    for rounds_count in range(3, 6):
        b_scores = [0] * rounds_count
        a_scores = [0] * rounds_count

        # assign winning rounds
        a_scores[-1] = 11
        a_scores[-2] = 11
        a_scores[-3] = 11

        for round_idx in range(rounds_count - 3):
            b_scores[round_idx] = 11

        # assign losing rounds
        for round_idx in range(rounds_count - 3):
            remaining_score = a - sum(a_scores)
            remaining_rounds = rounds_count - 3 - round_idx
            mean_score = remaining_score / remaining_rounds
            a_scores[round_idx] = ceil(mean_score)

        for round_idx in range(3):
            remaining_score = b - sum(b_scores)
            remaining_rounds = 3 - round_idx
            mean_score = remaining_score / remaining_rounds
            b_scores[-round_idx - 1] = ceil(mean_score)

        if sum(a_scores) != a or sum(b_scores) != b:
            continue
        if min(*a_scores, *b_scores) < 0:
            continue

        if is_valid(a_scores, b_scores):
            for a_score, b_score in zip(a_scores, b_scores):
                res.append([a_score, b_score])
            return res

    return [[-1, -1]]


def print_sol(res):
    for a, b in res:
        print(a, b)


def main():
    t = int(input())
    for _ in range(t):
        a, b = (int(x) for x in input().strip().split())
        res = solve(a, b)
        print_sol(res)


if __name__ == "__main__":
    main()
