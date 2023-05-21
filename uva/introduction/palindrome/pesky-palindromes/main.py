def is_palindrome (word):
    return ''.join(reversed(word)) == word


def count_palindromes (word):
    s = 0
    marked = set()
    for i, _ in enumerate(word):
        for j in range(i + 1, len(word) + 1):
            if word[i:j] in marked:
                continue
            marked.add(word[i:j])
            if is_palindrome(word[i:j]):
                s += 1
    return s


def main ():
    words = []
    while True:
        try:
            words.append(input().strip())
        except EOFError:
            break

    for word in words:
        res = count_palindromes(word)
        print(f'The string \'{word}\' contains {res} palindromes.')


if __name__ == '__main__':
    main()
