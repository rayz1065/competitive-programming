from math import ceil, floor

def my_round (x):
    return ceil(x) if (x % 1) >= 0.5 else floor(x)


def time_to_clock (time):
    hour = (time // 60) % 12
    if hour == 0:
        hour = 12
    minute = time % 60
    return ':'.join(str(x).rjust(2, '0') for x in (hour, minute))


def main ():
    daily_seconds = 24 * 60 ** 2

    while True:
        try:
            loss_a, loss_b = (int(x) for x in input().strip().split())
        except EOFError:
            break

        # seconds after which they sync
        sync_time = daily_seconds * daily_seconds // 2 / abs(loss_b - loss_a)

        # seconds that a moves in a second
        speed_a = 1. - loss_a / daily_seconds

        # time according to a
        a_time = my_round((speed_a * sync_time % daily_seconds) / 60)

        print(sync_time, " ", speed_a, "\n")
        print((speed_a * sync_time) / 60, "\n")
        print(loss_a, loss_b, time_to_clock(a_time))


if __name__ == '__main__':
    main()
