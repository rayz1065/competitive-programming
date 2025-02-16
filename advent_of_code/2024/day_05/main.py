from itertools import combinations


def read_input():
    graph = {}
    while True:
        line = input().strip()
        if line == "":
            break
        a, b = (int(x) for x in line.split("|"))
        graph.setdefault(a, set()).add(b)
        graph.setdefault(b, set())

    manuals = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        manuals.append(tuple(int(x) for x in line.split(",")))

    return graph, manuals


def check_manual(graph, manual):
    return all(a not in graph[b] for a, b in combinations(manual, r=2))


def _make_topo(graph, a, topo, visited):
    if a in visited:
        return
    visited.add(a)

    for b in graph[a]:
        _make_topo(graph, b, topo, visited)

    topo.append(a)


def make_topo(graph):
    visited = set()
    res = []
    for v in graph.keys():
        _make_topo(graph, v, res, visited)
    return res


def project_graph(graph, vertices):
    vertices = set(vertices)
    graph = dict(
        (a, set(x for x in b if x in vertices))
        for a, b in graph.items()
        if a in vertices
    )
    return graph


def part_1(graph, manuals):
    return sum(
        manual[len(manual) // 2] for manual in manuals if check_manual(graph, manual)
    )


def part_2(graph, manuals):
    manuals = [x for x in manuals if not check_manual(graph, x)]

    res = 0
    for manual in manuals:
        graph_manual = project_graph(graph, manual)
        topo = make_topo(graph_manual)
        ordering = {x: i for i, x in enumerate(topo)}
        manual = sorted(manual, key=lambda x: -ordering[x])
        res += manual[len(manual) // 2]

    return res


def main():
    graph, manuals = read_input()
    print("part1:", part_1(graph, manuals))
    print("part2:", part_2(graph, manuals))


if __name__ == "__main__":
    main()
