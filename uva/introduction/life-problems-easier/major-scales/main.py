NOTES = [
    'C', 'C#', 'D', 'D#', 'E', 'F',
    'F#', 'G', 'G#', 'A', 'A#', 'B',
]
MAJOR_SCALE = [2, 2, 1, 2, 2, 2, 1]


def note_to_number (note):
    return NOTES.index(note)


def get_scale (note):
    for delta in MAJOR_SCALE:
        yield note
        note = (note + delta) % len(NOTES)


def get_possible_scales (notes):
    notes = set(notes)
    for base, note in enumerate(NOTES):
        scale_notes = set(get_scale(base))
        if len(notes - scale_notes) == 0:
            yield note


def main ():
    while True:
        line = input().strip()
        if line == 'END':
            break

        notes = [note_to_number(x) for x in line.split()]
        print(' '.join(get_possible_scales(notes)))


if __name__ == '__main__':
    main()
