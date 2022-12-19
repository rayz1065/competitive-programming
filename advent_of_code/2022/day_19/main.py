import re

MAX_TIME = 24

class Blueprint:
    def __init__(self, blueprint_id, ore_robot_cost, clay_robot_cost, obsidian_robot_cost, geode_robot_cost):
        self.blueprint_id = blueprint_id
        self.ore_robot_cost = ore_robot_cost
        self.clay_robot_cost = clay_robot_cost
        self.obsidian_robot_cost = obsidian_robot_cost
        self.geode_robot_cost = geode_robot_cost

class State:
    def __init__(self, blueprint: Blueprint, ore, clay, obsidian, ore_robots, clay_robots, obsidian_robots):
        self.blueprint = blueprint
        self.ore = ore
        self.clay = clay
        self.obsidian = obsidian
        self.ore_robots = ore_robots
        self.clay_robots = clay_robots
        self.obsidian_robots = obsidian_robots

    def __str__(self):
        return f'{self.ore} ore, {self.clay} clay, {self.obsidian} obsidian.\n'\
               f'{self.ore_robots} ore robots, {self.clay_robots} clay robots, '\
               f'{self.obsidian_robots} obsidian robots'

    def copy (self):
        return State(self.blueprint, self.ore, self.clay, self.obsidian, self.ore_robots,
                     self.clay_robots, self.obsidian_robots)

    def spend_resources (self, cost):
        ore_cost, clay_cost, obsidian_cost = cost
        if self.ore >= ore_cost and self.clay >= clay_cost and self.obsidian >= obsidian_cost:
            self.ore -= ore_cost
            self.clay -= clay_cost
            self.obsidian -= obsidian_cost
            return True
        return False

    def make_ore_robot (self):
        if self.spend_resources(self.blueprint.ore_robot_cost):
            self.ore_robots += 1
            return True
        return False

    def make_clay_robot (self):
        if self.spend_resources(self.blueprint.clay_robot_cost):
            self.clay_robots += 1
            return True
        return False

    def make_obsidian_robot (self):
        if self.spend_resources(self.blueprint.obsidian_robot_cost):
            self.obsidian_robots += 1
            return True
        return False

    def make_geode_robot (self):
        if self.spend_resources(self.blueprint.geode_robot_cost):
            return True
        return False

    def make_resources (self):
        self.ore += self.ore_robots
        self.clay += self.clay_robots
        self.obsidian += self.obsidian_robots

def read_input ():
    blueprints = []
    try:
        while True:
            line = input()
            res = re.match(r'^Blueprint (\d+): '
                           r'Each ore robot costs (\d+) ore. '
                           r'Each clay robot costs (\d+) ore. '
                           r'Each obsidian robot costs (\d+) ore and (\d+) clay. '
                           r'Each geode robot costs (\d+) ore and (\d+) obsidian.$',
                           line)
            assert res is not None
            values = tuple(int(x) for x in res.groups())
            blueprints.append(Blueprint(values[0],
                (values[1], 0, 0),
                (values[2], 0, 0),
                (values[3], values[4], 0),
                (values[5], 0, values[6])))
    except EOFError:
        pass
    return blueprints

best_sol = 0

def max_produced_geodes (state: State, curr_time):
    # calculate an upper bound for the amount of geodes produced
    # assume infinite ore
    geodes = 0
    clay = state.clay
    clay_robots = state.clay_robots
    obsidian = state.obsidian
    obsidian_robots = state.obsidian_robots
    while curr_time < MAX_TIME:
        # make even multiple robots at the same time
        if obsidian >= state.blueprint.geode_robot_cost[2]:
            geodes += MAX_TIME - curr_time
            obsidian -= state.blueprint.geode_robot_cost[2]
        obsidian += obsidian_robots
        if clay >= state.blueprint.obsidian_robot_cost[1]:
            obsidian_robots += 1
            clay -= state.blueprint.obsidian_robot_cost[1]
        clay += clay_robots
        clay_robots += 1
        curr_time += 1
    return geodes

def solve (state: State, curr_time, total_geodes=0):
    global best_sol
    if total_geodes + max_produced_geodes(state, curr_time) <= best_sol:
        return 0
    if curr_time == MAX_TIME:
        if total_geodes > best_sol:
            best_sol = total_geodes
        return 0
    new_state = state.copy()
    new_state.make_resources()
    solve(new_state, curr_time + 1, total_geodes) # make nothing
    if state.ore_robots < 4 and (new_state := state.copy()).make_ore_robot():
        new_state.make_resources()
        new_state.ore -= 1
        solve(new_state, curr_time + 1, total_geodes)
    if (new_state := state.copy()).make_clay_robot():
        new_state.make_resources()
        new_state.clay -= 1
        solve(new_state, curr_time + 1, total_geodes)
    if (new_state := state.copy()).make_obsidian_robot():
        new_state.make_resources()
        new_state.obsidian -= 1
        solve(new_state, curr_time + 1, total_geodes)
    if (new_state := state.copy()).make_geode_robot():
        new_state.make_resources()
        solve(new_state, curr_time + 1, total_geodes + (MAX_TIME - curr_time))

def part_1 (blueprints):
    global best_sol
    total = 0
    for blueprint in blueprints:
        best_sol = 0
        state = State(blueprint, 0, 0, 0, 1, 0, 0)
        solve(state, 1)
        total += best_sol * blueprint.blueprint_id
    return total

def part_2 (blueprints):
    global best_sol
    global MAX_TIME
    MAX_TIME = 32
    prod = 1
    for blueprint in blueprints[:3]:
        best_sol = 0
        state = State(blueprint, 0, 0, 0, 1, 0, 0)
        solve(state, 1)
        prod *= best_sol
    return prod

def main ():
    blueprints = read_input()
    print('part_1:', part_1(blueprints))
    print('part_2:', part_2(blueprints))

if __name__ == '__main__':
    main()
