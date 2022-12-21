from __future__ import annotations
import re

class Monkey:
    def __init__(self, name, op_a, op_b, operator, constval=None):
        self.name = name
        self.op_a = op_a
        self.op_b = op_b
        self.operator = operator
        self.constval = constval

    def eval (self, monkeys: dict[str, Monkey]) -> int:
        if self.constval is not None:
            return self.constval
        a = monkeys[self.op_a].eval(monkeys)
        b = monkeys[self.op_b].eval(monkeys)
        ops = {
            '+': a + b,
            '-': a - b,
            '*': a * b,
            '/': a // max(b, 1)
        }
        return ops[self.operator]

    def find_x (self, monkeys: dict[str, Monkey], res: int):
        if self.name == 'humn':
            return res
        a = monkeys[self.op_a]
        b = monkeys[self.op_b]
        if a.contains_humn(monkeys):
            # a contains humn, b is a constant
            b = b.eval(monkeys)
            ops = {
                '+': res - b,
                '-': res + b,
                '*': res // max(1, b),
                '/': res * b,
            }
        else:
            a, b = b, a
            # a contains humn, b is a constant
            b = b.eval(monkeys)
            ops = {
                '+': res - b,
                '-': b - res, # b - x = res => x = b - res
                '*': res // max(1, b),
                '/': None,
            }
        return a.find_x(monkeys, ops[self.operator])

    def to_str (self, monkeys: dict[str, Monkey]) -> str:
        if self.name == 'humn':
            return 'x'
        if not self.contains_humn(monkeys):
            return str(self.eval(monkeys))
        a = monkeys[self.op_a]
        b = monkeys[self.op_b]
        return f'({a.to_str(monkeys)} {self.operator} {b.to_str(monkeys)})'

    def contains_humn (self, monkeys: dict[str, Monkey]):
        if self.name == 'humn':
            return True
        if self.constval is not None:
            return False
        a = monkeys[self.op_a]
        b = monkeys[self.op_b]
        return a.contains_humn(monkeys) or b.contains_humn(monkeys)

def read_input () -> list[Monkey]:
    monkeys = {}
    try:
        while True:
            line = input()
            if (res := re.match(r'^(\w+): (\d+)$', line)) is not None:
                name, num = res.groups()
                monkey = Monkey(name, None, None, None, constval=int(num))
            elif (res := re.match(r'^(\w+): (\w+) ([\+\-\*/]) (\w+)$', line)) is not None:
                name, op_a, operator, op_b = res.groups()
                monkey = Monkey(name, op_a, op_b, operator)
            else:
                assert False
            monkeys[monkey.name] = monkey
    except EOFError:
        pass
    return monkeys

def main ():
    monkeys = read_input()
    root = monkeys['root']
    print('part_1:', root.eval(monkeys))
    a = monkeys[root.op_a]
    b = monkeys[root.op_b]
    if b.contains_humn(monkeys):
        a, b = b, a
    res = b.eval(monkeys)
    print('part_2:', a.find_x(monkeys, res))

if __name__ == '__main__':
    main()
