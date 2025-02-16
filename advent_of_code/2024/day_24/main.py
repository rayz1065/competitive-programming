from functools import cache
from collections import namedtuple
import re

Wire = namedtuple("Wire", ["op1", "operator", "op2", "result"])
WireOperation = namedtuple("WireOperation", ["op1", "operator", "op2"])


def read_input():
    inputs = {}
    wires = []

    while True:
        line = input().strip()
        if line == "":
            break
        variable, value = re.match(r"^(\w+): ([01])$", line).groups()
        inputs[variable] = int(value)

    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        op1, operator, op2, result = re.match(
            r"(\w+) (\w+) (\w+) -> (\w+)", line
        ).groups()
        wires.append(Wire(op1, operator, op2, result))

    return inputs, wires


def make_graph(wires: list[Wire]):
    return {
        wire.result: WireOperation(wire.op1, wire.operator, wire.op2) for wire in wires
    }


def get_values(inputs, wires):
    graph = make_graph(wires)

    @cache
    def compute(variable):
        if variable in inputs:
            return inputs[variable]
        op1, operator, op2 = graph[variable]
        if operator == "AND":
            return compute(op1) & compute(op2)
        elif operator == "XOR":
            return compute(op1) ^ compute(op2)
        elif operator == "OR":
            return compute(op1) | compute(op2)
        else:
            raise ValueError("Invalid operator")

    values = inputs.copy()
    for variable in graph.keys():
        values[variable] = compute(variable)

    return values


def part_1(inputs, wires):
    graph = make_graph(wires)
    values = get_values(inputs, wires)
    outputs = list(reversed(sorted(x for x in graph.keys() if x.startswith("z"))))
    output_values = [values[x] for x in outputs]
    return int("".join(map(str, output_values)), 2)


def part_2(inputs, wires):
    wires = [
        Wire(min(op1, op2), operator, max(op1, op2), result)
        for op1, operator, op2, result in wires
    ]

    def swap_wires(out1, out2):
        index1, wire1 = next((i, x) for i, x in enumerate(wires) if x.result == out1)
        index2, wire2 = next((i, x) for i, x in enumerate(wires) if x.result == out2)
        wires[index1] = Wire(wire1.op1, wire1.operator, wire1.op2, wire2.result)
        wires[index2] = Wire(wire2.op1, wire2.operator, wire2.op2, wire1.result)

    SWAPS = [
        ("vvr", "z08"),
        ("z39", "mqh"),
        ("tfb", "z28"),
        ("rnq", "bkr"),
    ]

    for a, b in SWAPS:
        swap_wires(a, b)

    graph = make_graph(wires)
    outputs = sorted(x for x in graph.keys() if x.startswith("z"))
    wire_keys = {
        (min(op1, op2), operator, max(op1, op2)): result
        for op1, operator, op2, result in wires
    }

    assert len(wire_keys) == len(wires)

    carry = wire_keys["x00", "AND", "y00"]

    blocks = [
        {
            "carry": None,
            "pc1": None,
            "pc2": None,
            "ps": None,
            "z": None,
        }
        for _ in range(46)
    ]
    blocks[0]["carry"] = carry

    for i, output in enumerate(outputs[1:-1]):
        i += 1
        x = f"x{str(i).rjust(2, '0')}"
        y = f"y{str(i).rjust(2, '0')}"
        z = f"z{str(i).rjust(2, '0')}"

        partial_carry_1 = wire_keys[x, "AND", y]
        partial_sum = wire_keys[x, "XOR", y]

        if carry == ".":
            candidates = [
                next(filter(lambda op: op != partial_sum, (op1, op2)))
                for op1, operator, op2, result in wires
                if (op1 == partial_sum or op2 == partial_sum)
                and not result.startswith("z")
                and operator == "AND"
            ]
            assert len(candidates) == 1, f"{i}: {candidates}"
            carry = candidates[0]

        blocks[i - 1]["carry"] = carry

        partial_carry_2 = wire_keys.get(
            (min(partial_sum, carry), "AND", max(partial_sum, carry))
        )
        full_sum = wire_keys.get(
            (min(partial_sum, carry), "XOR", max(partial_sum, carry))
        )

        blocks[i]["pc1"] = partial_carry_1
        blocks[i]["ps"] = partial_sum

        if partial_carry_2 != ".":
            blocks[i]["pc2"] = partial_carry_2
        if full_sum != ".":
            blocks[i]["z"] = full_sum

        full_carry = wire_keys.get(
            (
                min(partial_carry_1, partial_carry_2),
                "OR",
                max(partial_carry_1, partial_carry_2),
            ),
            ".",
        )

        carry = full_carry

    print(" " * 3, end=" ")
    for column in blocks[0]:
        print(column.ljust(6), end=" ")
    print()
    for i, block in enumerate(blocks):
        print(str(i).ljust(3), end=" ")
        for value in block.values():
            print(str("" if value is None else value).ljust(6), end=" ")
        print()

    broken_wires = set(x for pair in SWAPS for x in pair)
    return ",".join(sorted(broken_wires))


def main():
    inputs, wires = read_input()
    print(part_1(inputs, wires))
    print(part_2(inputs, wires))


if __name__ == "__main__":
    main()
