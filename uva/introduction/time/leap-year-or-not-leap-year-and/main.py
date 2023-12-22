def is_leap (year):
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)


def is_huluculu (year):
    return year % 15 == 0


def is_bulukulu (year):
    return year % 55 == 0 and is_leap(year)


def is_ordinary (year):
    return all(not is_x(year) for is_x in (is_leap, is_huluculu, is_bulukulu))


CHARACTERISTICS = {
    'leap': is_leap,
    'huluculu festival': is_huluculu,
    'bulukulu festival': is_bulukulu,
    'an ordinary': is_ordinary,
}


def main ():
    tc = 0
    while True:
        try:
            year = int(input().strip())
        except EOFError:
            break

        result = [f'This is {name} year.'
                  for name, is_x in CHARACTERISTICS.items()
                  if is_x(year)]

        tc += 1
        if tc > 1:
            print()
        print('\n'.join(result))


if __name__ == '__main__':
    main()
