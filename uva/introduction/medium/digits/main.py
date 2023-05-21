while True:
    line = input().strip()
    if line == 'END':
        break

    i = 0
    line_prev = line
    while True:
        line = str(len(line))
        if line == line_prev:
            break
        line_prev = line
        i += 1
    print(i + 1)
