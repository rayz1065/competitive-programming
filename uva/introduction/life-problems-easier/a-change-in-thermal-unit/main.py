def f_to_temperature (temperature_f):
    return (temperature_f - 32) * 5 / 9


def temperature_to_f (temperature):
    return temperature * 9 / 5 + 32


def main ():
    t = int(input().strip())
    for tc in range(t):
        temperature, increase_f = (int(x) for x in input().strip().split())
        temperature_f = temperature_to_f(temperature)
        temperature_f += increase_f
        temperature = f_to_temperature(temperature_f)
        print(f'Case {tc + 1}: {temperature:.2f}')


if __name__ == '__main__':
    main()
