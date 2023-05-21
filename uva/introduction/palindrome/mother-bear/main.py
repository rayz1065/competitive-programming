import re

NOT_EATEN = "You won't be eaten!"
EATEN = "Uh oh.."


def is_palindrome (word):
    return ''.join(reversed(word)) == word


def main ():
    sentences = []
    while True:
        line = input().strip()
        if line == 'DONE':
            break
        sentences.append(line)

    for sentence in sentences:
        sentence = re.sub('[^a-z]', '', sentence.lower())
        print(NOT_EATEN if is_palindrome(sentence) else EATEN)


if __name__ == '__main__':
    main()
