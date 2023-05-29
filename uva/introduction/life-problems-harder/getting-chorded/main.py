NOTES = [
    'A', 'A#', 'B', 'C', 'C#', 'D',
    'D#', 'E', 'F', 'F#', 'G', 'G#'
]
MINOR_DELTAS = [0, 3, 7]
MAJOR_DELTAS = [0, 4, 7]


def get_chord (note, deltas):
    note_idx = NOTES.index(note)
    return tuple(sorted(
        NOTES[(note_idx + delta) % len(NOTES)]
        for delta in deltas
    ))


MAJOR_CHORDS = {
    get_chord(note, MAJOR_DELTAS): note
    for note in NOTES
}
MINOR_CHORDS = {
    get_chord(note, MINOR_DELTAS): note
    for note in NOTES
}


def normalize (note):
    base_note = NOTES.index(note[0].upper())
    if len(note) == 1:
        return NOTES[base_note]

    assert note[1] in 'b#'

    if note[1] == 'b':
        return NOTES[base_note - 1]
    return NOTES[base_note + 1]


def main ():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        chord = tuple(sorted(normalize(x) for x in line.split()))

        chord_type = 'unrecognized'
        if chord in MAJOR_CHORDS:
            chord_type = f'a {MAJOR_CHORDS[chord]} Major chord'
        elif chord in MINOR_CHORDS:
            chord_type = f'a {MINOR_CHORDS[chord]} Minor chord'

        print(f'{line} is {chord_type}.')


if __name__ == '__main__':
    main()
