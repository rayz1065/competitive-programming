SEP = '******'
INVALID_WORD = 'NOT A VALID WORD'
END_OF_INPUTS = 'XXXXXX'

def read_input ():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        if line == END_OF_INPUTS:
            break
        yield line


def normalize (word):
    return ''.join(sorted(word))


def make_anagrams_dict (words):
    res = {}
    for word in sorted(words):
        res.setdefault(normalize(word), [])
        res[normalize(word)].append(word)
    return res


def main ():
    dictionary = list(read_input())
    words = list(read_input())

    anagrams_dict = make_anagrams_dict(dictionary)
    for word in words:
        word = normalize(word)
        if word not in anagrams_dict:
            print(INVALID_WORD)
            print(SEP)
            continue

        for b in anagrams_dict[word]:
            print(b)
        print(SEP)


if __name__ == '__main__':
    main()
