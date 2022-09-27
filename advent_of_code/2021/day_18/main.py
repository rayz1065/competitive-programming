from itertools import permutations
import json

EXPLODE_DEPTH = 4

class SnailfishNumber:
    def __init__(self, left=None, right=None, parent=None, regular_number=None):
        self.left = left
        self.right = right
        self.parent = parent
        self.regular_number = regular_number
        if left is not None:
            left.parent = self
        if right is not None:
            right.parent = self

    def __str__(self):
        if self.is_regular_number():
            return str(self.regular_number)
        return f"[{self.left},{self.right}]"

    def is_regular_number(self):
        return self.regular_number is not None

    def explode(self):
        assert self.parent is not None
        assert self.left.is_regular_number()
        assert self.right.is_regular_number()
        left_num = self.left.regular_number
        right_num = self.right.regular_number

        # turn the number into a zero
        self.left = None
        self.right = None
        self.regular_number = 0

        # pass the left and right regular numbers outward
        parent = self.parent
        absorbes_right = None
        absorbes_left = None
        if parent.left == self:
            # this is the left children of the parent
            absorbes_right = parent.right.leftmost_child()
            pparent = parent.parent
            while pparent is not None and pparent.left == parent:
                pparent, parent = pparent.parent, pparent
            if pparent is not None:
                absorbes_left = pparent.left.rightmost_child()
        else:
            assert parent.right == self
            # this is the right children of the parent
            absorbes_left = parent.left.rightmost_child()
            pparent = parent.parent
            while pparent is not None and pparent.right == parent:
                pparent, parent = pparent.parent, pparent
            if pparent is not None:
                absorbes_right = pparent.right.leftmost_child()

        if absorbes_left is not None:
            absorbes_left.regular_number+= left_num
        if absorbes_right is not None:
            absorbes_right.regular_number+= right_num

    def split(self):
        assert self.is_regular_number()
        assert self.regular_number >= 10
        # split the regular number into a pair
        left_num = self.regular_number//2
        right_num = self.regular_number//2 + self.regular_number%2
        self.left = SnailfishNumber(regular_number=left_num, parent=self)
        self.right = SnailfishNumber(regular_number=right_num, parent=self)
        self.regular_number = None

    def attempt_explode(self, depth):
        if self.is_regular_number():
            return False
        if depth >= EXPLODE_DEPTH:
            # this should be exploded
            self.explode()
            return True
        if self.left.attempt_explode(depth + 1):
            return True
        if self.right.attempt_explode(depth + 1):
            return True
        return False

    def attempt_split(self):
        if self.is_regular_number():
            if self.regular_number >= 10:
                self.split()
                return True
            return False
        if self.left.attempt_split():
            return True
        if self.right.attempt_split():
            return True
        return False

    def leftmost_child(self):
        if self.is_regular_number():
            return self
        return self.left.leftmost_child()

    def rightmost_child(self):
        if self.is_regular_number():
            return self
        return self.right.rightmost_child()

    def reduce_step(self):
        if self.attempt_explode(0):
            # some pair has been exploded
            return True
        if self.attempt_split():
            # some number has been split
            return True
        return False

    def reduce(self):
        while self.reduce_step():
            pass

    def magnitude(self):
        if self.is_regular_number():
            return self.regular_number
        return self.left.magnitude() * 3 + self.right.magnitude() * 2

    def sum(self, other):
        result = SnailfishNumber(left=self.copy(), right=other.copy())
        result.reduce()
        return result

    def copy(self):
        if self.is_regular_number():
            return SnailfishNumber(regular_number=self.regular_number)
        return SnailfishNumber(left=self.left.copy(), right=self.right.copy())

# def parse_regular_number(line, i):
#     j = i
#     while '0' <= line[j] <= '9':
#         j+= 1
#     assert j > i
#     return SnailfishNumber(regular_number=int(line[i:j])), j

# def parse_snailfish_num(line, i):
#     # read the left side of the number
#     assert line[i] == '['
#     i+= 1
#     if line[i] == '[':
#         left, i = parse_snailfish_num(line, i)
#     else:
#         left, i = parse_regular_number(line, i)

#     assert line[i] == ','
#     i+= 1
#     # read the right side of the number
#     if line[i] == '[':
#         right, i = parse_snailfish_num(line, i)
#     else:
#         right, i = parse_regular_number(line, i)

#     assert line[i] == ']'
#     i+= 1
#     snf_num = SnailfishNumber(left=left, right=right)
#     return snf_num, i

def arr_to_number(val):
    if isinstance(val, int):
        return SnailfishNumber(regular_number=val)
    lft, rgt = val
    return SnailfishNumber(left=arr_to_number(lft), right=arr_to_number(rgt))

def read_in():
    problem = []
    try:
        while True:
            line = input()
            arr = json.loads(line)
            num = arr_to_number(arr)
            # print(arr_to_number(arr))
            # num, i = parse_snailfish_num(line, 0)
            # assert i == len(line)
            problem.append(num)
    except EOFError:
        pass
    return problem

def part_1(problem):
    result = problem[0]
    for number in problem[1:]:
        result = result.sum(number)
    return result.magnitude()

def part_2(problem):
    return max(a.sum(b).magnitude() for a, b in permutations(problem, 2))

def main():
    problem = read_in()
    print("part_1:", part_1(problem))
    print("part_2:", part_2(problem))

if __name__ == '__main__':
    main()
