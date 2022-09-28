t = int(input())

def read_input ():
    input()
    return input().split()

def solve ():
    stack = []
    for bracket in brackets:
        if len(stack) == 0 or stack[-1] != bracket:
            stack.append(bracket)
        else:
            stack.pop()
    return int(len(stack) == 0)

for _ in range(t):
    brackets = read_input()
    print(int(solve()))
