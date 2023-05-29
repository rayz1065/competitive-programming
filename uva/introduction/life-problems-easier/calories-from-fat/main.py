CALORIES_BY_INGREDIENT = [9, 4, 4, 4, 7]


def get_calories (food):
    computed_percentage = 100
    calories = [0] * len(food)
    for i, quantity in enumerate(food):
        value = int(quantity[:-1])
        if quantity.endswith('g'):
            calories[i] = CALORIES_BY_INGREDIENT[i] * value
        elif quantity.endswith('C'):
            calories[i] = value
        else:
            computed_percentage -= value

    total_calories = sum(calories) * 100 / computed_percentage
    for i, quantity in enumerate(food):
        if quantity.endswith('%'):
            value = int(quantity[:-1])
            calories[i] = total_calories * value / 100

    return calories


def solve (foods):
    fat_calories = 0
    total_calories = 0
    for food in foods:
        calories = get_calories(food)
        fat_calories += calories[0]
        total_calories += sum(calories)

    return fat_calories / total_calories


def read_input ():
    while True:
        line = input().strip()
        if line == '-':
            break

        foods = []
        while line != '-':
            foods.append(line)
            line = input().strip()

        foods = [x.split() for x in foods]
        yield foods


def main ():
    for foods in read_input():
        res = round(solve(foods) * 100)
        print(f'{res}%')


if __name__ == '__main__':
    main()
