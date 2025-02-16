OPCODE_NAMES = ["adv", "bxl", "bst", "jnz", "bxc", "out", "bdv", "cdv"]
PROGRAM_OUTPUTS = None


def read_input():
    registers = [int(input().split(": ")[1]) for _ in range(3)]
    input()
    program = [int(x) for x in input().split(": ")[1].split(",")]
    return registers, program


def get_combo(value, registers):
    if 0 <= value <= 3:
        return value
    if 4 <= value <= 7:
        return registers[value - 4]
    raise ValueError(f"Invalid combo {value}")


def execute_op(opcode, value, registers):
    opcode = OPCODE_NAMES[opcode]
    registers = list(registers)
    ip = None
    output = None

    if opcode == "adv":
        num = registers[0]
        den = 2 ** get_combo(value, registers)
        registers[0] = num // den
    elif opcode == "bxl":
        registers[1] = registers[1] ^ value
    elif opcode == "bst":
        registers[1] = get_combo(value, registers) % 8
    elif opcode == "jnz":
        if registers[0] != 0:
            ip = value
    elif opcode == "bxc":
        registers[1] = registers[1] ^ registers[2]
    elif opcode == "out":
        output = get_combo(value, registers) % 8
    elif opcode == "bdv":
        num = registers[0]
        den = 2 ** get_combo(value, registers)
        registers[1] = num // den
    elif opcode == "cdv":
        num = registers[0]
        den = 2 ** get_combo(value, registers)
        registers[2] = num // den

    return tuple(registers), ip, output


def execute_program(registers, program):
    ip = 0
    res = []
    while 0 <= ip < len(program) - 1:
        opcode = program[ip]
        value = program[ip + 1]
        registers, new_ip, new_output = execute_op(opcode, value, registers)
        if new_output is not None:
            res.append(new_output)
        if new_ip is not None:
            ip = new_ip
        else:
            ip += 2
    return res


def pretty_print_program(program):
    for i in range(len(program) // 2):
        print(f"{i*2}: {OPCODE_NAMES[program[i * 2]]} {program[i * 2 + 1]}")


def solve_2(program, i, curr):
    if i < 0:
        return curr

    target = program[i]

    global PROGRAM_OUTPUTS
    valid_values = [
        x for x in PROGRAM_OUTPUTS[target] if 0 <= x - (curr * 8) % 1024 < 8
    ]

    res = None

    for value in valid_values:
        new_curr = curr * 8 + value % 8
        new_res = solve_2(program, i - 1, new_curr)
        if new_res is not None and (res is None or new_res < res):
            res = new_res

    return res


def part_1(registers, program):
    return ",".join(map(str, execute_program(registers, program)))


def part_2(program):
    global PROGRAM_OUTPUTS
    PROGRAM_OUTPUTS = [[] for _ in range(8)]
    for i in range(2**10):
        output = execute_program((i, 0, 0), program)
        output2 = execute_program((i + 2**10, 0, 0), program)
        assert output[0] == output2[0]
        PROGRAM_OUTPUTS[output[0]].append(i)

    res = solve_2(program, len(program) - 1, 0)
    assert execute_program((res, 0, 0), program) == program

    return res


def main():
    registers, program = read_input()
    print("part1:", part_1(registers, program))
    print("part2:", part_2(program))


if __name__ == "__main__":
    main()
