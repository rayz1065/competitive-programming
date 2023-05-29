import re

WEIGHT_MULTIPLIERS = [0.5, 0.05]


def main ():
    t = int(input().strip())
    for tc in range(t):
        line = input().strip()
        weight_data = re.match(r'^(?:(\d+)\s*.)\s*(?:(\d+)\s*.)?$', line).groups()

        weight = sum(float(x) * mul for x, mul in zip(weight_data, WEIGHT_MULTIPLIERS)
                     if x is not None)

        weight = str(round(weight, 5)).rstrip('0.')
        print(f'Case {tc + 1}: {weight}')


if __name__ == '__main__':
    main()
