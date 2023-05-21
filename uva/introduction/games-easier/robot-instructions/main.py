t = int(input().strip())
for _ in range(t):
    n = int(input().strip())
    instructions = [input().strip() for _ in range(n)]
    x = 0
    for i, instruction in enumerate(instructions):
        if instruction.startswith('SAME AS '):
            idx = int(instruction.split('SAME AS ')[1])
            instructions[i] = instructions[idx - 1]
    for instruction in instructions:
        if instruction == 'LEFT':
            x -= 1
        else:
            assert instruction == 'RIGHT'
            x += 1

    print(x)
