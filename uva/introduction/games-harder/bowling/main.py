def main ():
    while True:
        line = input().strip()
        if line == 'Game Over':
            break
        rolls = line.split()

        values = rolls.copy()
        for i, value in enumerate(values):
            if value == 'X':
                values[i] = 10
            elif value == '/':
                # note: cannot be first
                values[i] = 10 - values[i - 1]
            else:
                values[i] = int(value)

        round_idx, already_tossed = 1, False
        total_score = 0
        for i, roll in enumerate(rolls):
            if round_idx > 10:
                break

            total_score += values[i]
            if roll == 'X':
                total_score += values[i + 1] + values[i + 2]
            elif roll == '/':
                total_score += values[i + 1]

            if roll == 'X' or already_tossed:
                round_idx += 1
                already_tossed = False
            else:
                already_tossed = True

        print(total_score)

if __name__ == '__main__':
    main()
