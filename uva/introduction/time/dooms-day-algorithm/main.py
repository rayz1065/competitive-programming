MONTH_DAYS = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
YEAR_DAYS = sum(MONTH_DAYS)
WEEK_DAYS = [None, 'Monday', 'Tuesday', 'Wednesday',
             'Thursday', 'Friday', 'Saturday', 'Sunday']
YEAR = 2011
FIRST_DAY_OF_YEAR = 6


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


def get_calendar (year, first_day):
    calendar = [[None for _ in range(get_month_days(year, month) + 1)]
                for month, _ in enumerate(MONTH_DAYS)]

    month, date = 1, 1
    day = first_day
    for _ in range(get_year_days(year)):
        calendar[month][date] = day
        year, month, date = date_increment(year, month, date)
        day = day % 7 + 1

    return calendar


def main ():
    t = int(input().strip())
    calendar = get_calendar(YEAR, FIRST_DAY_OF_YEAR)
    for _ in range(t):
        month, date = (int(x) for x in input().strip().split())
        day = calendar[month][date]
        print(WEEK_DAYS[day])


if __name__ == '__main__':
    main()
