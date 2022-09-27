SUBJECT_NUMBER = 7
LOOP_DIVISOR = 20201227

def inputData():
    card, door = input(), input()
    return int(card), int(door)

def loopOnce(value, subjectNumber = SUBJECT_NUMBER):
    return (value * subjectNumber)%LOOP_DIVISOR

def findLoopSize(publicKey):
    value = 1
    loop = 0
    while value != publicKey:
        value = loopOnce(value)
        loop+= 1
    return loop

def part1(card, door):
    cardLoop = findLoopSize(card)
    doorLoop = findLoopSize(door)

    cardEnc, doorEnc = 1, 1
    for _ in range(cardLoop):
        cardEnc = loopOnce(cardEnc, door)
    for _ in range(doorLoop):
        doorEnc = loopOnce(doorEnc, card)
    return cardEnc

def main():
    card, door = inputData()
    print("1)", part1(card, door))
    print("2)", 'merry Christmas!')

if __name__ == "__main__":
    main()