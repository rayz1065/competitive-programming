def check_trans (trans, prices):
    tot = 0
    for am in trans:
        if am < 0:
            tot -= prices[-am - 1]
        else:
            tot += am
        if tot < 0:
            return False
    return True

t = int(input())
for _ in range(t):
    n, q = (int(x) for x in input().split())
    prices = list(int(x) for x in input().split())
    trans = (int(x) for x in input().split())
    print("OK" if check_trans(trans, prices) else "HACKER")
