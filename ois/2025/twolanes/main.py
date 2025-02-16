def main():
    n = int(input().strip())
    lanes = [input(), input()]
    print(next((i for i, lights in enumerate(zip(*lanes)) if "G" not in lights), n))


if __name__ == "__main__":
    main()
