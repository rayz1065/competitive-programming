import re

UNKNOWN_AREA = 'Unknown'
LOCAL_CALL = 'Local'


def split_number (number, codes):
    if number[0] != '0':
        return LOCAL_CALL, number
    subscriber_max_len = 10
    if len(number) > 1 and number[1] != '0':
        subscriber_max_len = 7

    # can also loop over values of i which satisfy length condition
    for i in range(1, len(number)):
        code, subscriber = number[:i], number[i:]
        if code in codes and 4 <= len(subscriber) <= subscriber_max_len:
            return code, subscriber

    return UNKNOWN_AREA, ''


def read_logs ():
    parts = []
    while True:
        line = input().strip()
        if line == '#':
            break
        parts.extend((x for x in line.split() if len(x)))

    for i in range(len(parts) // 2):
        number, duration = parts[i * 2], int(parts[i * 2 + 1])
        yield number, duration


def get_codes ():
    # table of IID and STD codes, localities, prices
    codes = {
        UNKNOWN_AREA: (UNKNOWN_AREA, None),
        LOCAL_CALL: (LOCAL_CALL, 0.),
    }
    while True:
        line = input().strip()
        if line == '000000':
            break
        match = re.match(r'^(\d+)\s*([^\$]+)\$(\d+)$', line)
        code, locality, price = match.groups()
        codes[code] = (locality, int(price))

    return codes


def main ():
    codes = get_codes()

    for number, duration in read_logs():
        code, subscriber_number = split_number(number, codes)
        location, price = codes[code]

        price_per_minute = f'{price / 100:.2f}' if price is not None else ''
        total_price = price * duration / 100 if price is not None else -1.

        print(number.ljust(16),
              location.ljust(25),
              subscriber_number.rjust(10),
              str(duration).rjust(5),
              price_per_minute.rjust(6),
              f'{total_price:.2f}'.rjust(7),
              sep='')


if __name__ == '__main__':
    main()
