import itertools

def inputData():
    data = []

    try:
        while True:
            data.append(int(input()))
    except EOFError:
        pass

    return data

def findCorrectSum(data, amounts, wantedSum):
    combinations = itertools.combinations(data, r=amounts)
    return next((x for x in combinations if sum(x) == wantedSum), None)

def main():
    data = inputData()
    a, b = findCorrectSum(data, 2, 2020)
    print("1)", a*b, findCorrectSum(data, 2, 2020))
    a, b, c = findCorrectSum(data, 3, 2020)
    print("2)", a*b*c, findCorrectSum(data, 3, 2020))

if __name__ == "__main__":
    main()