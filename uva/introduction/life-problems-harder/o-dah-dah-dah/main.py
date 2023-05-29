MORSE = {
    'A': '.-  ', 'J': '.---', 'S': '...  ', '1': '.----', '.': '.-.-.-', ':': '---...',
    'B': '-...', 'K': '-.- ', 'T': '-    ', '2': '..---', ',': '--..--', ';': '-.-.-.',
    'C': '-.-.', 'L': '.-..', 'U': '..-  ', '3': '...--', '?': '..--..', '=': '-...- ',
    'D': '-.. ', 'M': '--  ', 'V': '...- ', '4': '....-', "'": '.----.', '+': '.-.-. ',
    'E': '.   ', 'N': '-.  ', 'W': '.--  ', '5': '.....', '!': '-.-.--', '-': '-....-',
    'F': '..-.', 'O': '--- ', 'X': '-..- ', '6': '-....', '/': '-..-. ', '_': '..--.-',
    'G': '--. ', 'P': '.--.', 'Y': '-.-- ', '7': '--...', '(': '-.--. ', '"': '.-..-.',
    'H': '....', 'Q': '--.-', 'Z': '--.. ', '8': '---..', ')': '-.--.-', '@': '.--.-.',
    'I': '..  ', 'R': '.-. ', '0': '-----', '9': '----.', '&': '.-... ', }

MORSE = { k: v.rstrip() for k, v in MORSE.items() }
MORSE_LETTER = { v: k for k, v in MORSE.items() }


def morse_to_word (morse):
    return ''.join(MORSE_LETTER[x] for x in morse.split(' '))


def main ():
    t = int(input().strip())
    for tc in range(t):
        message = input().strip()
        words = message.split('  ')

        print(f'Message #{tc + 1}')
        print(' '.join(morse_to_word(word) for word in words))
        if tc + 1 < t:
            print()


if __name__ == '__main__':
    main()
