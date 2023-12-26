import re
import sys
from collections import namedtuple
from itertools import tee

Graph = namedtuple("Graph", ["nodes", "edges", "adjacencies"])


def pairwise(it):
    a, b = tee(it)
    next(b, None)
    return zip(a, b)


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(r"^(\w+): ([\w\s]+)$", line)
        a, bs = res.groups()
        bs = bs.split()

        for b in bs:
            yield a, b


def build_graph(edges):
    nodes = set(node for edge in edges for node in edge)
    adjacencies = {node: set() for node in nodes}
    for a, b in edges:
        adjacencies[a].add(b)
        adjacencies[b].add(a)

    return Graph(nodes, edges, adjacencies)


def dfs(graph: Graph, a, capacities: dict):
    visited = set([a])
    ff = [a]

    while len(ff) > 0:
        a = ff.pop()
        for b in graph.adjacencies[a]:
            if b in visited or capacities[a, b] == 0:
                continue

            visited.add(b)
            ff.append(b)

    return visited


def find_augmenting(graph: Graph, capacities: dict, node, sink):
    parents = {node: -1}
    ff = [node]

    while len(ff) > 0:
        node = ff[0]
        ff = ff[1:]

        for b in graph.adjacencies[node]:
            if b in parents or capacities[node, b] == 0:
                continue

            parents[b] = node
            ff.append(b)

    if sink not in parents:
        return None

    node = sink
    result = []
    while node != -1:
        result.append(node)
        node = parents[node]

    return list(reversed(result))


def max_flow(graph: Graph, source, sink):
    capacities = {}
    for a, b in graph.edges:
        capacities[a, b] = 1
        capacities[b, a] = 1

    flow = 0
    while (augmenting := find_augmenting(graph, capacities, source, sink)) is not None:
        flow += 1
        for a, b in pairwise(augmenting):
            capacities[a, b] -= 1
            capacities[b, a] += 1

    return flow, capacities


def part_1(graph: Graph):
    for a, b in pairwise(graph.nodes):
        flow, capacities = max_flow(graph, a, b)
        if flow <= 3:
            cc = len(dfs(graph, a, capacities))
            return cc * (len(graph.nodes) - cc)

    return None


def main():
    edges = list(read_lines())
    graph = build_graph(edges)
    print("part_1:", part_1(graph))


if __name__ == "__main__":
    main()
