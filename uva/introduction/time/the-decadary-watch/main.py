DAILY_CSECONDS = 100 * 60 * 60 * 24
DAILY_DECI_SECONDS = 100 * 100 * 100 * 10

def in_to_cseconds (x):
    hours = int(x[:2])
    minutes = int(x[2:4])
    cseconds = int(x[4:])
    return ((hours * 60) + minutes) * 6000 + cseconds


def main ():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        cseconds = in_to_cseconds(line)
        deci_seconds = int(cseconds * DAILY_DECI_SECONDS / DAILY_CSECONDS)
        print(str(deci_seconds).rjust(7, '0'))


if __name__ == '__main__':
    main()
