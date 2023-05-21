BEAT_DURATION = 480
BEAT_DIVISIONS = 8
DIVISION_DURATION = BEAT_DURATION // BEAT_DIVISIONS
BEATS_COUNT = 4

def find_closest (measure, beat, tick):
    remainder = tick % DIVISION_DURATION
    if remainder < DIVISION_DURATION // 2:
        tick -= remainder
    else:
        tick += DIVISION_DURATION - remainder

    if tick == BEAT_DURATION:
        beat, tick = beat + 1, 0
    if beat == BEATS_COUNT + 1:
        measure, beat = measure + 1, 1

    return measure, beat, tick


def quantize (performance):
    to_skip = [False] * len(performance)
    current_notes = { note: None for _, note, *_ in performance }
    for i, (code, note, *timestamp) in enumerate(performance):
        timestamp = find_closest(*timestamp)
        performance[i] = (code, note, *timestamp)

        if code == 1:
            current_notes[note] = i
            continue

        start_idx = current_notes[note]
        if start_idx is None:
            continue
        current_notes[note] = None

        start_timestamp = performance[start_idx][2:]
        if start_timestamp == timestamp:
            # start and end coincide
            to_skip[start_idx] = True
            to_skip[i] = True

    # remove empty notes
    performance = [x for i, x in enumerate(performance) if not to_skip[i]]
    return performance


def main ():
    while True:
        n = int(input().strip())
        if n == -1:
            break

        performance = [tuple(int(x) for x in input().strip().split())
                        for _ in range(n)]
        performance = quantize(performance)

        print(len(performance))
        for code, note, measure, beat, tick in performance:
            print(code, note, measure, beat, tick)

    print(-1)


if __name__ == '__main__':
    main()
