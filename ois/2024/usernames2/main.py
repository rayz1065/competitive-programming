def main():
    username = input().strip()
    n = int(input().strip())

    used_suffixes = set()
    for _ in range(n):
        other = input().strip()
        if not other.startswith(username):
            continue

        suffix = other[len(username) :]
        if suffix == "":
            suffix = "0"
        elif suffix.startswith("0"):
            continue

        try:
            suffix = int(suffix)
        except ValueError:
            continue

        used_suffixes.add(suffix)

    suffix = next(i for i in range(len(used_suffixes) + 1) if i not in used_suffixes)
    suffix = str(suffix).lstrip("0")
    print(f"{username}{suffix}")


if __name__ == "__main__":
    main()
