def normalize (word):
    return ''.join(sorted(word))

def main ():
    t = int(input())
    for tc in range(t):
        input()
        n = int(input().strip())
        dictionary = [input().strip() for _ in range(n)]
        anagrams_map = {}
        for word in dictionary:
            anagrams_map.setdefault(normalize(word), [])
            anagrams_map[normalize(word)].append(word)

        while True:
            word = input().strip()
            if word == 'END':
                break

            print(f'Anagrams for: {word}')
            if normalize(word) not in anagrams_map:
                print(f'No anagrams for: {word}')
                continue

            for i, b in enumerate(anagrams_map[normalize(word)]):
                i = str(i + 1).rjust(3)
                print(f'{i}) {b}')
        if tc + 1 < t:
            print()

if __name__ == '__main__':
    main()
