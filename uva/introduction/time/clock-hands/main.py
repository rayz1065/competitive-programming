def calculate_angle (time):
    hours, minutes = (int(x) for x in time.split(':'))

    hour_angle = (360 // 12) * (hours + minutes / 60)
    minutes_angle = (360 // 60) * minutes

    angle = abs(hour_angle - minutes_angle)
    angle = min(angle, 360 - angle)
    return angle


def main ():
    while True:
        time = input().strip()
        if time == '0:00':
            break
        print(f'{calculate_angle(time):.3f}')


if __name__ == '__main__':
    main()
