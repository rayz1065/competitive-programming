import re
from typing import List
import queue

ENTITY_COSTS = {
    'A': 1,
    'B': 10,
    'C': 100,
    'D': 1000
}

STACK_SIZE = 4

class PriorityItem:
    def __init__(self, priority, item):
        self.priority = priority
        self.item = item

    def __lt__(self, other):
        return self.priority < other.priority

class Node:
    def is_empty(self):
        raise NotImplementedError

    def enter_cost(self):
        raise NotImplementedError

    def exit_cost(self):
        raise NotImplementedError

    def can_enter(self, entity):
        raise NotImplementedError

    def enter(self, entity, backwards=False):
        raise NotImplementedError

    def exit(self):
        raise NotImplementedError

    def get_entity(self):
        raise NotImplementedError

    def is_room(self):
        raise NotImplementedError

class SimpleNode(Node):
    def __init__(self, node_id):
        self.content = None
        self.node_id = node_id

    def is_empty(self):
        return self.content == None

    def enter_cost(self):
        return 0

    def exit_cost(self):
        return 0

    def can_enter(self, _):
        return self.is_empty()

    def enter(self, entity, backwards=False):
        self.content = entity

    def exit(self):
        assert not self.is_empty()
        content = self.content
        self.content = None
        return content

    def get_entity(self):
        assert not self.is_empty()
        return self.content

    def is_room(self):
        return False

    def __str__(self):
        content_str = '-'
        if self.content is not None:
            content_str = self.content
        return f"{self.node_id}({content_str})"

class RoomNode(Node):
    def __init__(self, inhabitant):
        self.node_id = f'.{inhabitant}'
        self.inhabitant = inhabitant
        self.stack = []

    def is_empty(self):
        return len(self.stack) == 0

    def enter_cost(self):
        return STACK_SIZE - len(self.stack) - 1

    def exit_cost(self):
        return STACK_SIZE - len(self.stack)

    def can_enter(self, entity):
        if entity != self.inhabitant:
            return False
        return self.no_intruders()

    def enter(self, entity, backwards=False):
        if not backwards:
            assert self.can_enter(entity)
        self.stack.append(entity)

    def exit(self):
        assert not self.is_empty()
        return self.stack.pop()

    def get_entity(self):
        return self.stack[len(self.stack) - 1]

    def __str__(self):
        return f'{self.node_id} {self.stack}'

    def is_room(self):
        return True

    def no_intruders(self):
        return all(x == self.inhabitant for x in self.stack)

    def is_solved(self):
        return self.no_intruders() and len(self.stack) == STACK_SIZE

class Map:
    rooms: List[RoomNode]
    nodes: List[Node]

    def __init__(self):
        self.rooms = []
        self.nodes = []
        self.graph = {}
        self.moves = []
        self.total_cost = 0
        self.djikstra_memo = {}

        #############
        #01.2.3.4.56#
        ###A#B#C#D###
          #.#.#.#.#
          #########

        for i in range(7):
            self.nodes.append(SimpleNode(str(i)))
        for i in range(4):
            room = RoomNode(chr(ord('A') + i))
            self.rooms.append(room)
            self.nodes.append(room)
        self.add_branch(self.nodes[0], self.nodes[1], 1)
        self.add_branch(self.nodes[5], self.nodes[6], 1)
        for i in range(1, 5):
            self.add_branch(self.nodes[i], self.nodes[i + 1], 2)
        for i in range(4):
            left_node  = self.nodes[i + 1]
            right_node = self.nodes[i + 2]
            self.add_branch(left_node,  self.rooms[i], 2)
            self.add_branch(right_node, self.rooms[i], 2)

    def add_branch(self, node_a, node_b, val):
        self.graph.setdefault(node_a, {})
        self.graph.setdefault(node_b, {})
        self.graph[node_a][node_b] = val
        self.graph[node_b][node_a] = val

    def find_room(self, entity):
        return next(room for room in self.rooms if room.inhabitant == entity)

    def dfs(self, node, visited):
        if visited[node]:
            return
        visited[node] = True
        for other in self.graph[node]:
            if other.is_room():
                # we cannot go trough it to go anywhere
                visited[other] = True
            elif other.is_empty():
                self.dfs(other, visited)

    def djikstra(self, node):
        dist = { x: None for x in self.nodes }
        dist[node] = 0
        ff = queue.PriorityQueue()
        ff.put_nowait(PriorityItem(dist[node], node))
        while not ff.empty():
            item = ff.get_nowait()
            node = item.item
            for other in self.graph[node]:
                new_dist = dist[node] + self.graph[node][other]
                if dist[other] is None or dist[other] > new_dist:
                    dist[other] = new_dist
                    ff.put_nowait(PriorityItem(dist[other], other))
        return dist

    def dist(self, node_a, node_b):
        if node_a not in self.djikstra_memo:
            self.djikstra_memo[node_a] = self.djikstra(node_a)
        return self.djikstra_memo[node_a][node_b] + node_a.exit_cost() + node_b.enter_cost()

    def can_reach(self, node_a, node_b):
        visited = { node: False for node in self.nodes }
        self.dfs(node_a, visited)
        return visited[node_b]

    def move(self, node_a, node_b):
        # assert self.check_move(node_a, node_b), f"cannot move from {node_a} to {node_b}"
        dist = self.dist(node_a, node_b)
        self.moves.append((node_a, node_b))
        content = node_a.exit()
        node_b.enter(content)
        self.total_cost+= dist * ENTITY_COSTS[content]
        return dist * ENTITY_COSTS[content]

    def undo_move(self):
        node_a, node_b = self.moves.pop()
        dist = self.dist(node_b, node_a)
        content = node_b.exit()
        node_a.enter(content, backwards=True)
        self.total_cost-= dist * ENTITY_COSTS[content]

    def check_move(self, node_a, node_b):
        if not node_a.is_room() and not node_b.is_room():
            # corridor to corridor move is invalid
            return False
        if node_a.is_empty() or not node_b.can_enter(node_a.get_entity()):
            # nothing to move or no space to move to
            return False
        if node_a.is_room() and node_a.no_intruders():
            # cannot move entity already at right place
            return False
        return self.can_reach(node_a, node_b)

    def find_all_moves(self):
        moves = []
        for node_a in self.nodes:
            for node_b in self.nodes:
                if self.check_move(node_a, node_b):
                    moves.append((node_a, node_b))
        return moves

    def cost_estimate_lb(self):
        # unsolved_rooms = (room for room in self.rooms if not room.is_solved())
        estimate = self.total_cost
        return estimate

    def is_solved(self):
        return all(x.is_solved() for x in self.rooms)

def read_in():
    assert input() ==  '#############'
    assert input() ==  '#...........#'
                    #  '###A#B#C#D###'
                    #  '  #D#C#B#A#'
                    #  '  #D#B#A#C#'
                    #  '  #A#B#C#D#'
    room_rows = [input() for _ in range(STACK_SIZE)]
    assert input() ==  '  #########'

    problem = Map()

    rooms_row_re = re.compile(r'^..#(\w)#(\w)#(\w)#(\w)##?#?$')
    for rooms_row in reversed(room_rows):
        match = rooms_row_re.match(rooms_row)
        assert match is not None
        for j, entity in enumerate(match.groups()):
            problem.rooms[j].stack.append(entity)

    return problem

def _solve(problem, partial):
    if partial is not None and problem.cost_estimate_lb() >= partial:
        # prune: already worse than partial result
        return None
    moves = problem.find_all_moves()
    if len(moves) == 0:
        if problem.is_solved():
            print(problem.total_cost)
            for node_a, node_b in problem.moves:
                print(f"{node_a.node_id}\t->\t{node_b.node_id}")
            return problem.total_cost
        return None

    for node_a, node_b in moves:
        if node_b.is_room():
            moves = [(node_a, node_b)]
            break

    for node_a, node_b in moves:
        # print(f"{node_a} -> {node_b}")
        problem.move(node_a, node_b)
        res = _solve(problem, partial)
        if res is not None and (partial is None or res < partial):
            partial = res
        problem.undo_move()
    return partial

def solve(problem):
    return _solve(problem, None)

def main():
    problem = read_in()
    print("solution:", solve(problem))

if __name__ == '__main__':
    main()
