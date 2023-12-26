from math import ceil


def main():
    n, k = (int(x) for x in input().strip().split())
    costs = sorted((int(x) for x in input().strip().split()), key=lambda x: -x)
    target = n * k

    total_cost = sum(costs)
    diff = target - total_cost

    if diff == 0:
        print(0)
        return
    elif diff > 0:
        print(1)
        return

    for i, cost in enumerate(costs):
        # decrease cost to 1
        total_cost -= cost - 1
        diff = target - total_cost
        if diff >= 0:
            break

    print(i + 1)


if __name__ == "__main__":
    main()
