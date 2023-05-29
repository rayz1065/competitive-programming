KEYS = ['abc', 'def', 'ghi', 'jkl', 'mno', 'pqrs', 'tuv', 'wxyz', ' ']
KEY_PRESSES = {
    character: i + 1
    for key in KEYS
    for i, character in enumerate(key)
}


def count_clicks (line):
    return sum(KEY_PRESSES[x] for x in line)


def main ():
    t = int(input().strip())

    for tc in range(t):
        line = input()
        print(f'Case #{tc + 1}: {count_clicks(line)}')


if __name__ == '__main__':
    main()
