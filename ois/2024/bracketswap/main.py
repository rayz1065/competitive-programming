def main():
    input()
    line = input().strip()

    unbalanced = []
    opening = []
    open_count = 0

    for i, parenthesis in enumerate(line):
        if parenthesis == '(':
            open_count += 1
            opening.append(i)
        elif parenthesis == ')' and open_count > 0:
            open_count -= 1
        else:
            unbalanced.append(i)
            open_count += 1

    print(len(unbalanced))
    for i, j in zip(unbalanced, reversed(opening)):
        print(i, j)


if __name__ == "__main__":
    main()
