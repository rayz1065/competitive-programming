PART_1_DAYS = 80
PART_2_DAYS = 256
MAX_AGE = 8
RESET_FISH_AGE = 6

def read_in():
    line = input()
    return [int(x) for x in line.split(',')]

def empty_state():
    return [0 for _ in range(MAX_AGE + 1)]

def generate_ages(fishes):
    state = empty_state()
    for fish in fishes:
        state[fish]+= 1
    return state

def simulate_state(state):
    new_state = empty_state()
    new_state[RESET_FISH_AGE] = state[0]
    for age in range(MAX_AGE + 1):
        new_age = (age - 1 + (MAX_AGE + 1)) % (MAX_AGE + 1)
        new_state[new_age]+= state[age]
    return new_state

def part_1(state):
    for _ in range(PART_1_DAYS):
        state = simulate_state(state)
    return sum(state)

def part_2(state):
    for _ in range(PART_2_DAYS):
        state = simulate_state(state)
    return sum(state)

def main():
    problem = read_in()
    initial_state = generate_ages(problem)
    print("part_1:", part_1(initial_state))
    print("part_2:", part_2(initial_state))

if __name__ == '__main__':
    main()
