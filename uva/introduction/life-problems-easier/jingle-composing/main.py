NOTES = 'WHQESTX'
MEASURE_LENGTH = 64
NOTE_DURATION = {
    note: MEASURE_LENGTH // (2 ** i)
    for i, note in enumerate(NOTES)
}


def measure_length (measure):
    return sum(NOTE_DURATION[x] for x in measure)


def main ():
    while True:
        line = input().strip()
        if line == '*':
            break

        measures = line.strip('/').split('/')
        print(sum(measure_length(x) == MEASURE_LENGTH for x in measures))


if __name__ == '__main__':
    main()
