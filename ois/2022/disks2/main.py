n_days, t_repair = (int(x) for x in input().split())
contests = list(tuple(int(x) for x in input().split())
                             for _ in range(n_days))

def solve ():
    for i in range(0, n_days - 1):
        contest_a, contest_b = contests[i], contests[i + 1]
        distance = (contest_b[0] + 24) - contest_a[1]
        if distance >= t_repair:
            return i
    return -1

print(solve())
