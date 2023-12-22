MONTH_DAYS = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
YEAR_DAYS = sum(MONTH_DAYS)
SIGNS = {
    'Aquarius': ((1, 21), (2, 19)),
    'Pisces': ((2, 20), (3, 20)),
    'Aries': ((3, 21), (4, 20)),
    'Taurus': ((4, 21), (5, 21)),
    'Gemini': ((5, 22), (6, 21)),
    'Cancer': ((6, 22), (7, 22)),
    'Leo': ((7, 23), (8, 21)),
    'Virgo': ((8, 22), (9, 23)),
    'Libra': ((9, 24), (10, 23)),
    'Scorpio': ((10, 24), (11, 22)),
    'Sagittarius': ((11, 23), (12, 22)),
    # hack to deal with change of year
    'Capricorn': ((12, 23), (12, 31)),
    'capricorn': ((1, 1), (1, 20)),
}
DAYS_AHEAD = 40 * 7


def is_leap (year):
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)


def get_month_days (year, month):
    if is_leap(year) and month == 2:
        return MONTH_DAYS[month] + 1
    return MONTH_DAYS[month]


def get_year_days (year):
    return YEAR_DAYS + is_leap(year)


def date_increment (year, month, date):
    date += 1
    if date <= get_month_days(year, month):
        return year, month, date

    month, date = month + 1, 1
    if month <= 12:
        return year, month, date

    year, month = year + 1, 1
    return year, month, date


def normalize (in_date):
    return tuple(int(x) for x in (in_date[4:], in_date[0:2], in_date[2:4]))


def get_sign (month, date):
    for sign, (start, end) in SIGNS.items():
        if (month, date) >= start and (month, date) <= end:
            return sign
    assert False, f'No sign for {month}-{date}'


def main ():
    t = int(input().strip())
    for tc in range(t):
        year, month, date = normalize(input())
        for _ in range(DAYS_AHEAD):
            year, month, date = date_increment(year, month, date)

        sign = get_sign(month, date)

        month, date = (str(x).rjust(2, '0') for x in (month, date))
        month, date = date, month # format date as m/d/y
        print(f'{tc + 1} {date}/{month}/{year} {sign.lower()}')


if __name__ == '__main__':
    main()
