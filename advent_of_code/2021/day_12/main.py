class Node:
    def __init__(self, label):
        self.label = label
        self.is_starting = self.label == 'start'
        self.is_ending = self.label == 'end'
        self.is_big_cave = self.label == self.label.upper()
        self.visit_count = 0

class Graph:
    def __init__(self):
        self.nodes = []
        self.nodes_map = dict()
        self.graph = dict()
        self.starting_node = None
        self.ending_node = None

    def get_node(self, label):
        if label not in self.nodes_map:
            node = Node(label)
            self.nodes_map[label] = node
            self.nodes.append(node)
            self.graph[node] = []
            if node.is_starting:
                self.starting_node = node
            if node.is_ending:
                self.ending_node = node
        return self.nodes_map[label]

    def add_branch(self, node_a, node_b):
        self.graph[node_a].append(node_b)
        self.graph[node_b].append(node_a)

    def count_paths(self, can_vis_small_twice):
        return self._count_paths(self.starting_node, can_vis_small_twice)

    def _count_paths(self, node, can_vis_small_twice):
        if node == self.ending_node:
            # reached the end
            return 1
        node.visit_count+= 1
        if not node.is_big_cave and node.visit_count == 2:
            can_vis_small_twice = False
        s = 0
        for other in self.graph[node]:
            if other.is_big_cave or other.visit_count == 0 or \
                (other != self.starting_node and can_vis_small_twice):
                s+= self._count_paths(other, can_vis_small_twice)
        node.visit_count-= 1
        return s

def read_in():
    graph = Graph()
    try:
        while True:
            line = input()
            node_f, node_t = line.split('-')
            node_f = graph.get_node(node_f)
            node_t = graph.get_node(node_t)
            graph.add_branch(node_f, node_t)
    except EOFError:
        pass
    return graph

def part_1(graph):
    return graph.count_paths(False)

def part_2(graph):
    return graph.count_paths(True)

def main():
    graph = read_in()
    print("part_1:", part_1(graph))
    print("part_2:", part_2(graph))

if __name__ == '__main__':
    main()
