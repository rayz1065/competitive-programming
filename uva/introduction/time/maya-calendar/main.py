import re

YEAR_MONTHS = [ # Haab
    'pop', 'no', 'zip', 'zotz', 'tzec', 'xul', 'yoxkin', 'mol', 'chen',
    'yax', 'zac', 'ceh', 'mac', 'kankin', 'muan', 'pax', 'koyab', 'cumhu',
    'uayet',
]
MONTH_LENGTHS = [ *[20] * 18, 5 ]
YEAR_LENGTH = sum(MONTH_LENGTHS)

HOLLY_DAY_NAMES = [ # Tzolkin
    'imix', 'ik', 'akbal', 'kan', 'chicchan', 'cimi', 'manik', 'lamat', 'muluk',
    'ok', 'chuen', 'eb', 'ben', 'ix', 'mem', 'cib', 'caban', 'eznab', 'canac', 'ahau',
]
HOLLY_PERIODS = 13
HOLLY_YEAR_LENGTH = HOLLY_PERIODS * len(HOLLY_DAY_NAMES)
HOLLY_CALENDAR = [
    ((i % HOLLY_PERIODS) + 1, HOLLY_DAY_NAMES[i % len(HOLLY_DAY_NAMES)])
    for i in range(HOLLY_YEAR_LENGTH)
]


def days_since_year_start (month, day):
    month_idx = YEAR_MONTHS.index(month)
    return sum(MONTH_LENGTHS[:month_idx]) + day


def main ():
    t = int(input().strip())
    print(t)

    for _ in range(t):
        date = input().strip()
        res = re.match(r'^(\d+)\.\s*(\w+)\s+(\d+)$', date)
        day, month, year = res.groups()
        day = int(day)
        year = int(year)

        day_idx = year * YEAR_LENGTH + days_since_year_start(month, day)

        holly_year = day_idx // HOLLY_YEAR_LENGTH
        holly_day = day_idx % HOLLY_YEAR_LENGTH
        holly_period, holly_day_name = HOLLY_CALENDAR[holly_day]

        print(holly_period, holly_day_name, holly_year)


if __name__ == '__main__':
    main()

