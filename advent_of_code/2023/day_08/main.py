import re
from collections import namedtuple
from math import lcm

Node = namedtuple("Node", ["curr", "left", "right"])


def read_lines():
    while True:
        try:
            line = input().strip()
            if line == "":
                continue

            res = re.match(r"^(\w+)\s+=\s+\((\w+),\s+(\w+)\)$", line)
            curr, left, right = res.groups()
        except EOFError:
            break
        yield Node(curr, left, right)


def build_graph(nodes: list[Node]):
    graph = {}
    for node in nodes:
        graph[node.curr] = node

    return graph


def part_1(instructions, nodes: list[Node], curr="AAA"):
    graph = build_graph(nodes)
    steps = 0
    while not curr.endswith("Z"):
        instruction = instructions[steps % len(instructions)]
        curr = graph[curr].left if instruction == "L" else graph[curr].right
        steps += 1

    return steps


def part_2(instructions, nodes: list[Node]):
    # this assumes there is a unique ending node for each starting node
    periods = []
    for node in nodes:
        if not node.curr.endswith("A"):
            # not a starting node
            continue

        steps = part_1(instructions, nodes, node.curr)
        periods.append(steps)

    return lcm(*periods)


def main():
    instructions = input().strip()
    nodes = list(read_lines())
    print("part_1:", part_1(instructions, nodes))
    print("part_2:", part_2(instructions, nodes))


if __name__ == "__main__":
    main()
