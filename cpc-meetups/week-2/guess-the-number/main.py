from sys import stdout


def main():
    a, b = 1, 1_000_000
    res = 0

    while a <= b:
        mid = (a + b) // 2
        print(mid)
        stdout.flush()
        hint = input().strip()
        if hint == "<":
            b = mid - 1
        else:
            a = mid + 1
            res = mid

    print(f"! {res}")


if __name__ == "__main__":
    main()
