while True:
    line = input().strip()
    if line[0] == '0':
        break
    height, length = (int(x) for x in line.split())
    final_heights = [int(x) for x in input().strip().split()]

    s = 0
    curr_height = height
    for height in final_heights:
        if height < curr_height:
            s += curr_height - height
        curr_height = height
    print(s)
