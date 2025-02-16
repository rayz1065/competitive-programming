import math


EPS = 1e-8


def get_angle(a, b, c):
    # returns angle at b
    if a[0] == c[0]:
        b1 = abs(a[1] - b[1])
        b2 = abs(c[1] - b[1])
        h = abs(a[0] - b[0])
    else:
        b1 = abs(a[0] - b[0])
        b2 = abs(c[0] - b[0])
        h = abs(a[1] - b[1])
    angle1 = math.atan(b1 / h)
    angle2 = math.atan(b2 / h)
    return angle1 + angle2


def is_right(a, b, c):
    # returns True if the angle at b is right
    vec1 = (b[0] - a[0], b[1] - a[1])
    vec2 = (b[0] - c[0], b[1] - c[1])
    dot = vec1[0] * vec2[0] + vec1[1] * vec2[1]
    return dot == 0


def main():
    corners = [tuple(int(x) for x in input().strip().split()) for _ in range(4)]
    n = int(input().strip())
    res = 0
    for _ in range(n):
        tulip = tuple(int(x) for x in input().strip().split())
        angles = [get_angle(corners[i], tulip, corners[i - 1]) for i in range(4)]
        good = sum(x > math.pi / 2 + EPS for x in angles)
        res += good == 2 and not any(
            is_right(corners[i], tulip, corners[i - 1]) for i in range(4)
        )

    print(res)


if __name__ == "__main__":
    main()
