DECRYPTION_KEY = 811589153

def read_input ():
    numbers = []
    try:
        i = 0
        while True:
            numbers.append((i, int(input())))
            i += 1
    except EOFError:
        pass
    return numbers


def find_idx (numbers, idx):
    return next(i for i, number in enumerate(numbers) if number[0] == idx)


def move (numbers, initial_pos):
    # moves idx to the new position
    n = len(numbers)
    move_by = numbers[initial_pos][1]
    while move_by > n or move_by < 0:
        move_by = move_by//n + move_by % n
    for j in range(move_by):
        a = (initial_pos + j) % n
        b = (initial_pos + j + 1) % n
        numbers[a], numbers[b] = numbers[b], numbers[a]

def mix_list (numbers):
    n = len(numbers)
    for idx in range(n):
        move(numbers, find_idx(numbers, idx))

def solve (numbers, mix_steps=1):
    numbers = list(numbers)
    n = len(numbers)
    for step in range(mix_steps):
        print('mixing...', f'{step + 1}/{mix_steps}')
        mix_list(numbers)
    pos_0 = next(i for i, number in enumerate(numbers) if number[1] == 0)
    return sum(numbers[(pos_0 + delta) % n][1] for delta in [1000, 2000, 3000])

def part_2 (numbers):
    numbers = [(i, num * DECRYPTION_KEY) for i, num in numbers]
    return solve(numbers, 10)

def main ():
    numbers = read_input()
    print('part_1:', solve(numbers))
    print('part_2:', part_2(numbers))

if __name__ == '__main__':
    main()
