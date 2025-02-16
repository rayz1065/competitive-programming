def main():
    _, m = (int(x) for x in input().strip().split())
    chocolates = [int(x) for x in input().strip().split()]
    costs = [int(x) for x in input().strip().split()]
    viable = [x for x, c in zip(chocolates, costs) if x % 2 == 0 and c <= m]
    viable.append(0)
    print(max(viable))


if __name__ == "__main__":
    main()
