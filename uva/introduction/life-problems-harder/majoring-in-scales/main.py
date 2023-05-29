NOTES = [
    'A', 'A#', 'B', 'C', 'C#', 'D',
    'D#', 'E', 'F', 'F#', 'G', 'G#'
]
MAJOR_SCALE = [2, 2, 1, 2, 2, 2, 1]
DISTANCES = [None, 'SECOND', 'THIRD', 'FOURTH', 'FIFTH', 'SIXTH', 'SEVENTH', 'OCTAVE']
NOTE_MODIFIERS = { 'b': -1, '#': +1 }


def get_note_idx (note):
    base_note = NOTES.index(note[0])
    if len(note) == 1:
        return base_note
    return base_note + NOTE_MODIFIERS[note[1]]


def get_note_names (note_idx, used_sign=None):
    names = []
    if len(NOTES[note_idx]) == 1:
        names.append(NOTES[note_idx])
    if len(NOTES[(note_idx + 1) % len(NOTES)]) == 1 and used_sign != '#':
        names.append(f'{NOTES[(note_idx + 1) % len(NOTES)]}b')
    if len(NOTES[note_idx - 1]) == 1 and used_sign != 'b':
        names.append(f'{NOTES[note_idx - 1]}#')
    return names


def generate_notes (note_indexes, first_note, used_sign):
    '''creates the scales using the passed sign'''
    result = [None] * len(note_indexes)
    freqs = { x: 0 for x in 'ABCDEFG' }
    result[0] = first_note
    freqs[first_note[0]] += 1

    for i, note_idx in enumerate(note_indexes):
        names = get_note_names(note_idx, used_sign=used_sign)
        if i == 0 or len(names) > 1:
            continue
        # there is only one option for this note
        result[i] = names[0]
        freqs[names[0][0]] += 1

    if max(freqs.values()) > 1:
        # note appears twice
        return None

    for i, note_idx in enumerate(note_indexes):
        if result[i] is not None:
            continue
        # fills in the remaining names using unused notes
        names = [x for x in get_note_names(note_idx, used_sign=used_sign)
                 if freqs[x[0]] == 0]
        assert len(names) == 1
        result[i] = names[0]
        freqs[names[0][0]] += 1

    return result


def get_scale (note):
    req_sign = None if len(note) == 1 else note[1]
    note_idx = get_note_idx(note)
    note_indexes = []
    for delta in MAJOR_SCALE:
        note_indexes.append(note_idx)
        note_idx = (note_idx + delta) % len(NOTES)

    if req_sign is not None:
        notes = generate_notes(note_indexes, note, used_sign=req_sign)
        return notes

    if (res := generate_notes(note_indexes, note, used_sign='#')) is not None:
        return res

    return generate_notes(note_indexes, note, used_sign='b')


def print_all_scales ():
    all_notes = set(x for i, _ in enumerate(NOTES) for x in get_note_names(i))
    for note in all_notes:
        scale = get_scale(note)
        print(note, scale)


def main ():
    while True:
        try:
            scale = input().strip()
            notes = input().strip().split(';')
        except EOFError:
            break

        scale_notes = list(get_scale(scale))
        print(f'Key of {scale}')
        for note in notes:
            base_note, direction, amount = note.split()
            if base_note not in scale_notes:
                print(f'{base_note}: invalid note for this key')
                continue

            distance = DISTANCES.index(amount)
            if direction == 'DOWN':
                distance *= -1

            new_idx = (scale_notes.index(base_note) + distance) % len(scale_notes)
            print(f'{base_note}: {direction} {amount} > {scale_notes[new_idx]}')

        print()


if __name__ == '__main__':
    main()
