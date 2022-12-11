def read_input():
    ops = []
    try:
        while True:
            line = input().split()
            if len(line) == 2:
                line = [line[0], int(line[1])]
            ops.append(line)
    except EOFError:
        pass
    return ops

def main():
    ops = read_input()
    cycle = 0
    tot_signal = [0]
    signal = 1
    crt = []
    def check_signal ():
        if len(crt) == 0 or len(crt[-1]) == 40:
            crt.append([])
        is_lit = signal < (cycle + 1) % 40 <= signal + 3
        crt[-1].append('#' if is_lit else '.')
        if (cycle - 20) % 40 == 0:
            tot_signal[0] += signal * cycle

    for op in ops:
        if op[0] == 'noop':
            cycle += 1
            check_signal()
        elif op[0] == 'addx':
            cycle += 1
            # print('middle of', op)
            check_signal()
            cycle += 1
            # print('end of', op)
            check_signal()
            signal += op[1]
            # print(cycle, op[1], signal)
        else:
            assert False
    print('part_1:', tot_signal[0])
    for i, row in enumerate(crt):
        PREFIX = 'part_2:'
        print(PREFIX if i == 0 else ' ' * len(PREFIX),
            ''.join(row))

main()
