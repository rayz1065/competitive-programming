MONTHS = [
    None, 'January', 'February', 'March', 'April', 'May', 'June',
    'July', 'August', 'September', 'October', 'November', 'December',
]
MONTH_DAYS = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
YEAR_DAYS = sum(MONTH_DAYS)


def is_leap (year):
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)


def get_year_days (year):
    return YEAR_DAYS + is_leap(year)


FH_YEARS_DAYS = sum(get_year_days(i) for i in range(400))


def get_month_days (year, month):
    if is_leap(year) and month == 2:
        return MONTH_DAYS[month] + 1
    return MONTH_DAYS[month]


def date_increment (year, month, date):
    date += 1
    if date <= get_month_days(year, month):
        return year, month, date

    month, date = month + 1, 1
    if month <= 12:
        return year, month, date

    year, month = year + 1, 1
    return year, month, date


def normalize_date (date_str):
    year, month, date = date_str.split('-')
    month = MONTHS.index(month)
    return tuple(int(x) for x in (year, month, date))


def main ():
    t = int(input().strip())
    for tc in range(t):
        date_str = input().strip()
        days_ahead = int(input().strip())
        year, month, date = normalize_date(date_str)

        while days_ahead >= FH_YEARS_DAYS:
            # skip ahead by 400 years
            days_ahead -= FH_YEARS_DAYS
            year += 400

        while days_ahead > 0 and month != 1:
            # avoid off-by-one caused by being after February
            days_ahead -= 1
            year, month, date = date_increment(year, month, date)

        while days_ahead >= get_year_days(year):
            # skip ahead by a year
            days_ahead -= get_year_days(year)
            year += 1

        for _ in range(days_ahead):
            year, month, date = date_increment(year, month, date)

        print(f'Case {tc + 1}: {year}-{MONTHS[month]}-{str(date).rjust(2, "0")}')


if __name__ == '__main__':
    main()
