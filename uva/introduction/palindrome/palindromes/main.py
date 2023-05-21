MIRRORED_CHARACTERS = {
    'A': 'A', 'M': 'M', 'Y': 'Y',
    'Z': '5', 'O': 'O', '1': '1',
    '2': 'S', 'E': '3', '3': 'E',
    'S': '2', '5': 'Z', 'H': 'H',
    'T': 'T', 'I': 'I', 'U': 'U',
    'J': 'L', 'V': 'V', '8': '8',
    'W': 'W', 'L': 'J', 'X': 'X',
}


def is_palindrome (word):
    return ''.join(reversed(word)) == word


def mirror (word):
    if any(char not in MIRRORED_CHARACTERS for char in word):
        return None
    return ''.join(reversed([MIRRORED_CHARACTERS[char] for char in word]))


def is_mirrored (word):
    return mirror(word) == word


def main ():
    words = []
    while True:
        try:
            words.append(input().strip())
        except EOFError:
            break

    for word in words:
        palindrome = is_palindrome(word)
        mirrored = is_mirrored(word)

        if palindrome and mirrored:
            print(f'{word} -- is a mirrored palindrome.')
        elif palindrome:
            print(f'{word} -- is a regular palindrome.')
        elif mirrored:
            print(f'{word} -- is a mirrored string.')
        else:
            print(f'{word} -- is not a palindrome.')
        print()


if __name__ == '__main__':
    main()
