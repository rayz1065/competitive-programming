def inputData():
    startTime = int(input())
    line = input()
    ids = []
    for val in line.split(','):
        if val == 'x':
            ids.append(val)
        else:
            ids.append(int(val))

    return (startTime, ids)


def part1(startTime, ids):
    currTime = startTime
    while True:
        for busId in ids:
            if busId != 'x' and currTime%busId == 0:
                return (currTime - startTime)*busId
        currTime+= 1

def extended_euclidean(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extended_euclidean(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    _, x, _ = extended_euclidean(a, m)
    return x % m

def crt(m, x):
    while True:
        temp1 = modinv(m[1],m[0]) * x[0] * m[1] + modinv(m[0],m[1]) * x[1] * m[0]
        temp2 = m[0] * m[1]
        x.remove(x[0])
        x.remove(x[0])
        x = [temp1 % temp2] + x
        m.remove(m[0])
        m.remove(m[0])
        m = [temp2] + m
        if len(x) == 1:
            break
    return x[0]

def part2(ids):
    idTuples = [(busId, busId - i) for i, busId in enumerate(ids) if busId != 'x']
    ms = [busId for busId, i in idTuples]
    xs = [i for busId, i in idTuples]

    prod = 1
    for m in ms:
        prod*= m
    s = crt(ms, xs)  
    return s%prod

def main():
    startTime, ids = inputData()
    print("1)", part1(startTime, ids))
    print("2)", part2(ids))

if __name__ == "__main__":
    main()