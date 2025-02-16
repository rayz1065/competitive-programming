def main():
    coords1 = tuple(int(x) for x in input().strip().split())
    coords2 = tuple(int(x) for x in input().strip().split())
    print(sum(abs(x - y) for x, y in zip(coords1, coords2)))


if __name__ == "__main__":
    main()
