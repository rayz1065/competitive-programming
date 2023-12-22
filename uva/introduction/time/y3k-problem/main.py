MONTH_DAYS = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
YEAR_DAYS = sum(MONTH_DAYS)


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


def main ():
    fh_years_days = sum(get_year_days(i) for i in range(400))

    while True:
        days_ahead, date, month, year = (int(x) for x in input().strip().split())
        if date == 0:
            break

        while days_ahead >= fh_years_days:
            # skip ahead by 400 years
            days_ahead -= fh_years_days
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

        print(date, month, year)


if __name__ == '__main__':
    main()
