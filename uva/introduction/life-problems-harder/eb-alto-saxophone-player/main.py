NOTES = {
    'a': '0110000000', 'A': '1110000000',
    'b': '0100000000', 'B': '1100000000',
    'c': '0111001111', 'C': '0010000000',
    'd': '0111001110', 'D': '1111001110',
    'e': '0111001100', 'E': '1111001100',
    'f': '0111001000', 'F': '1111001000',
    'g': '0111000000', 'G': '1111000000',
}
NOTES = { note: [x == '1' for x in values] for note, values in NOTES.items() }


def count_presses (song):
    presses = [0] * 10
    currently_pressed = [0] * 10

    for note in song:
        for finger, is_pressed in enumerate(NOTES[note]):
            presses[finger] += (is_pressed and not currently_pressed[finger])
        currently_pressed = NOTES[note]

    return presses


def main ():
    t = int(input().strip())
    for _ in range(t):
        song = input().strip()
        presses = count_presses(song)

        print(' '.join(str(x) for x in presses))


if __name__ == '__main__':
    main()
