import re

MONTHS = [
    None, 'January', 'February', 'March', 'April', 'May', 'June',
    'July', 'August', 'September', 'October', 'November', 'December',
]

def is_leap (year):
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)


LEAP_YEARS_IN_FH_YEARS = sum(is_leap(year) for year in range(400))


def normalize_date (date_str):
    res = re.match(r'^(\w+) (\d+), (\d+)$', date_str)
    month, date, year = res.groups()
    month = MONTHS.index(month)
    return tuple(int(x) for x in (year, month, date))


def count_leap_years (year_a, year_b):
    '''year_a inclusive, year_b exclusive'''
    fh_intervals = max(0, year_b - year_a) // 400
    year_a += fh_intervals * 400
    res = LEAP_YEARS_IN_FH_YEARS * fh_intervals \
          + sum(is_leap(year) for year in range(year_a, year_b))

    return res


def compute_leap_between (date_a, date_b):
    y_a, m_a, d_a = date_a
    y_b, m_b, d_b = date_b
    res = count_leap_years(y_a + 1, y_b)
    if is_leap(y_a) and (m_a, d_a) <= (2, 29) and (y_a, 2, 29) <= date_b:
        res += 1
    if y_a != y_b and is_leap(y_b) and (m_b, d_b) >= (2, 29):
        res += 1

    return res


def main ():
    t = int(input().strip())
    for tc in range(t):
        date_a, date_b = (normalize_date(x) for x in (input(), input()))
        print(f'Case {tc + 1}: {compute_leap_between(date_a, date_b)}')


if __name__ == '__main__':
    main()
