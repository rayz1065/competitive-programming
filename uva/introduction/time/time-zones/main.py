import re

TIMEZONES = {
    'UTC': +0,      'GMT': +0,      'BST': +1,      'IST': +1,      
    'WET': +0,      'WEST': +1,     'CET': +1,      'CEST': +2,     
    'EET': +2,      'EEST': +3,     'MSK': +3,      'MSD': +4,      
    'AST': -4,      'ADT': -3,      'NST': -3.5,    'NDT': -2.5,    
    'EST': -5,      'EDT': -4,      'CST': -6,      'CDT': -5,      
    'MST': -7,      'MDT': -6,      'PST': -8,      'PDT': -7,      
    'HST': -10,     'AKST': -9,     'AKDT': -8,     'AEST': +10,    
    'AEDT': +11,    'ACST': +9.5,   'ACDT': +10.5,  'AWST': +8,     
}

def normalize_time (time):
    if time == 'midnight':
        return 0
    if time == 'noon':
        return 12 * 60

    time_info = time.split()
    hour, minute = (int(x) for x in time_info[0].split(':'))
    hour %= 12

    if time_info[1] == 'p.m.':
        hour += 12

    return hour * 60 + minute


def to_am_pm (time):
    hour = (time // 60) % 24
    minute = time % 60
    if (hour, minute) == (0, 0):
        return 'midnight'
    if (hour, minute) == (12, 0):
        return 'noon'

    hour_r = hour % 12
    if hour_r == 0:
        hour_r = 12

    return f'{hour_r}:{str(minute).rjust(2, "0")} {"a" if hour < 12 else "p"}.m.'


def convert_tz (time, tz_from, tz_to):
    time -= int(TIMEZONES[tz_from] * 60)
    time += int(TIMEZONES[tz_to] * 60)
    time = (time + 24 * 60) % (24 * 60)
    return time


def main ():
    t = int(input().strip())
    for _ in range(t):
        line = input().strip()
        res = re.match(r'^(noon|midnight|\d+:\d+ (?:a|p)\.m\.) (\w{3,4}) (\w{3,4})$', line)
        time, tz_from, tz_to = res.groups()

        time = normalize_time(time)
        time = convert_tz(time, tz_from, tz_to)
        print(to_am_pm(time))


if __name__ == '__main__':
    main()
