def read_input ():
    all_calories = []
    curr_calories = []
    try:
        while True:
            line = input()
            if line == '':
                all_calories.append(curr_calories)
                curr_calories = []
            else:
                curr_calories.append(int(line))
    except EOFError:
        all_calories.append(curr_calories)
    return all_calories

def main ():
    all_calories = read_input()
    all_sums = [sum(x) for x in all_calories]
    print('part 1:', max(all_sums))
    all_sums.sort()
    print('part 2:', all_sums[-1] + all_sums[-2] + all_sums[-3])

if __name__ == '__main__':
    main()
