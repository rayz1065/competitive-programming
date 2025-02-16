def solve(alphabet):
    chunks = []
    for letter in alphabet:
        if chunks and chunks[-1][-1] == letter:
            chunks[-1].append(letter)
        else:
            chunks.append([letter])

    found = set()
    res = []
    for letters in chunks:
        letter = letters[-1]
        alien_letters = []

        if len(letters) > 3:
            return -1

        if len(letters) % 2 == 1:
            alien_letters.append(letter)
        if len(letters) >= 2:
            alien_letters.append(f"{letter}{letter}")

        if found.intersection(alien_letters):
            return -1

        found.update(alien_letters)
        res.extend(alien_letters)

    return " ".join(res)


def main():
    n = int(input().strip())
    for _ in range(n):
        alphabet = input().strip()
        print(solve(alphabet))


if __name__ == "__main__":
    main()
