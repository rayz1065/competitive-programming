from math import ceil

def main ():
    n, k = (int(x) for x in input().strip().split())
    costs = sorted(int(x) for x in input().strip().split())
    target = n * k

    total_cost = sum(costs)
    diff = target - total_cost
    min_c = ceil(abs(diff) / n)

    if diff > 0:
        print(min_c)
        return

    for i, cost in enumerate(costs):
        if cost > min_c:
            break

        total_cost -= cost - 1
        diff = target - total_cost
        min_c = ceil(abs(diff) / (n - i - 1))

    print(min_c)


if __name__ == '__main__':
    main()
