def make_gray(value, power):
    if power < 0:
        return

    make_gray(value, power - 1)
    value[power] = 1 - value[power]
    print("".join(str(x) for x in value))
    make_gray(value, power - 1)


def main():
    n = int(input().strip())
    value = [0] * n
    print("".join(str(x) for x in value))
    make_gray(value, n - 1)


if __name__ == "__main__":
    main()
