while True:
    curr, wanted = (int(x) for x in input().strip().split())
    if curr == -1:
        break
    res = min(
        abs(curr - wanted),
        abs(curr + 100 - wanted),
        abs(curr - 100 - wanted),
    )
    print(res)
