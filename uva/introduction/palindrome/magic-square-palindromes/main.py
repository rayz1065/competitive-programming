import re
import math


def is_palindrome (word):
    return ''.join(reversed(word)) == word


def is_magic_square (word):
    if not is_palindrome(word):
        return False

    side_len = math.isqrt(len(word))
    if side_len ** 2 != len(word):
        return False

    read_down = ''.join(word[r * side_len + c]
                        for c in range(side_len)
                        for r in range(side_len))
    if read_down != word:
        return False
    # note: if read_down is the same as the word, it already is a palindrome
    # no need to check if reading from the other side yields the same result

    return True


def clean_sentence (sentence):
    return re.sub('[^a-z]', '', sentence.lower())


def main ():
    t = int(input().strip())
    sentences = [clean_sentence(input()) for _ in range(t)]

    for tc, sentence in enumerate(sentences):
        print(f'Case #{tc + 1}:')
        if is_magic_square(sentence):
            print(math.isqrt(len(sentence)))
        else:
            print('No magic :(')

if __name__ == '__main__':
    main()
