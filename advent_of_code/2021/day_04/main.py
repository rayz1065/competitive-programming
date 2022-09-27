BINGO_SIZE = 5


def read_in():
    extracted_numbers = [int(x) for x in input().split(',')]
    boards = []

    try:
        while True:
            curr_board = []
            line = input()
            assert line == ''
            for i in range(BINGO_SIZE):
                line = input()
                line = line.strip(' ').replace('  ', ' ').split(' ')
                curr_board.append([int(x.strip(' ')) for x in line])
            boards.append(curr_board)
    except EOFError:
        pass
    return (extracted_numbers, boards)

def mark_number(board, extr_num):
    for i, row in enumerate(board):
        for j, num in enumerate(row):
            if num == extr_num:
                board[i][j] = -1

def all_marked(numbers):
    return all(num < 0 for num in numbers)

def is_winning(board):
    for row in board:
        if all_marked(row):
            return True
    for i in range(BINGO_SIZE):
        if all_marked(board[j][i] for j in range(BINGO_SIZE)):
            return True
    return False

def find_winning(boards):
    for board in boards:
        if is_winning(board):
            return board
    return None

def winning_exists(boards):
    return find_winning(boards) is not None

def sum_unmarked(board):
    return sum(num for row in board for num in row if num >= 0)

def extract_until(extracted_numbers, boards, fun):
    last_extracted_idx = 0
    while True:
        for board in boards:
            mark_number(board, extracted_numbers[last_extracted_idx])
        if fun(boards):
            break
        last_extracted_idx+= 1
    return last_extracted_idx

def part_1(extracted_numbers, boards):
    last_extracted_idx = extract_until(extracted_numbers, boards, winning_exists)
    winning_board = find_winning(boards)
    return sum_unmarked(winning_board) * extracted_numbers[last_extracted_idx]

def part_2(extracted_numbers, boards):
    last_extracted_idx = 0
    while True:
        for board in boards:
            mark_number(board, extracted_numbers[last_extracted_idx])
        boards = [board for board in boards if not is_winning(board)]
        if len(boards) == 1:
            break
        last_extracted_idx+= 1
    last_extracted_idx = extract_until(extracted_numbers, boards, winning_exists)
    losing_board = boards[0]
    return sum_unmarked(losing_board) * extracted_numbers[last_extracted_idx]

def main():
    extracted_numbers, boards = read_in()
    print("part_1:", part_1(extracted_numbers, boards))
    print("part_2:", part_2(extracted_numbers, boards))

if __name__ == '__main__':
    main()
