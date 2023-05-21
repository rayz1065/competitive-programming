import itertools

def letter_key (letter):
    key = ord(letter.lower()) * 2
    if letter == letter.lower():
        key += 1
    return key


def letter_key_to_letter (key):
    lower = key % 2 == 1
    letter = chr(key // 2)
    if not lower:
        letter = letter.upper()
    return letter


def tuple_to_word (tup):
    return ''.join(letter_key_to_letter(x) for x in tup)


n = int(input().strip())
words = [input().strip() for _ in range(n)]

for word in words:
    word_keys = tuple(sorted(letter_key(x) for x in sorted(word)))
    permutations = [tuple_to_word(x) for x in itertools.permutations(word_keys)]
    for permutation in permutations:
        print(''.join(permutation))
