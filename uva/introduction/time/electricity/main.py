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


def solve (measures):
    measures_map = {
        (y, m, d): p
        for d, m, y, p in measures
    }

    correct_measures = []
    for day, month, year, measure in measures:
        year, month, day = date_increment(year, month, day)
        if (year, month, day) in measures_map:
            next_measure = measures_map[year, month, day]
            correct_measures.append(next_measure - measure)

    return len(correct_measures), sum(correct_measures)


def main ():
    while True:
        n_measures = int(input())
        if n_measures == 0:
            break

        measures = [
            tuple(int(x) for x in input().strip().split())
            for _ in range(n_measures)
        ]

        n_days, total_consumption = solve(measures)
        print(n_days, total_consumption)


if __name__ == '__main__':
    main()
