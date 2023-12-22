def calculate_angle (hours, minutes):
    hour_angle = (360 // 12) * (hours * 5 + (minutes // 12)) // 5
    minutes_angle = (360 // 60) * minutes

    angle = abs(hour_angle - minutes_angle)
    angle = min(angle, 360 - angle)
    return angle


def main ():
    VALID_ANGLES = set(calculate_angle(hours, minutes)
                       for hours in range(12)
                       for minutes in range(60))

    while True:
        try:
            angle = int(input().strip())
        except EOFError:
            break

        print('Y' if angle in VALID_ANGLES else 'N')


if __name__ == '__main__':
    main()
