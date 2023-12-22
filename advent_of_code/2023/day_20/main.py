import re
from collections import namedtuple
from math import lcm


Module = namedtuple("Module", ["name", "operation", "targets"])


class StatefulModule:
    def __init__(self, module: Module, inputs):
        self.name = module.name
        self.operation = module.operation
        self.targets = module.targets
        self.input_states = {x: 0 for x in inputs}
        self.output = 0
        self.outputs_counts = [0, 0]

    def __str__(self):
        return (
            f"{self.name} {self.operation} {self.targets}"
            + f"\ninputs: {self.input_states}, output: {self.output}"
        )

    def consume(self, input_, signal):
        self.input_states[input_] = signal

        if self.operation == "%":
            # toggle
            if signal == 1:
                # output nothing
                return None

            self.output = 1 - self.output

        elif self.operation == "&":
            # AND and invert
            if all(self.input_states.values()):
                self.output = 0
            else:
                self.output = 1

        elif self.operation is None:
            self.output = signal

        else:
            assert False, f"Unknown operation {self.operation}"

        self.outputs_counts[self.output] += 1
        return self.output


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(r"^([%&])?(\w+) -> ([\w\s,]+)$", line)
        operation, name, targets = res.groups()
        targets = [x.strip() for x in targets.split(",")]
        yield Module(name, operation, targets)


def make_stateful_modules(modules: list[Module]):
    input_maps = {module.name: [] for module in modules}
    input_maps["broadcaster"].append("button")

    outputs = set()

    for module in modules:
        for target in module.targets:
            if target not in input_maps:
                input_maps.setdefault(target, [])
                outputs.add(target)

            input_maps[target].append(module.name)

    all_modules = [
        StatefulModule(module, input_maps[module.name]) for module in modules
    ] + [StatefulModule(Module(name, "&", []), input_maps[name]) for name in outputs]

    return {x.name: x for x in all_modules}


def simulate_press(modules_map: dict[str, StatefulModule], track_module=None):
    track_results = []

    ff = [("broadcaster", "button", 0, 0)]
    pulses_count = 0

    while len(ff) > 0:
        pulses_count += 1
        name, from_input, signal, time = ff[0]
        ff = ff[1:]
        module = modules_map[name]
        output = module.consume(from_input, signal)

        if name == track_module:
            track_results.append((time, output))

        if output is None:
            continue

        for target in module.targets:
            ff.append((target, module.name, output, time + 1))

    return track_results


def part_1(modules: list[Module]):
    modules_map = make_stateful_modules(modules)
    repetitions = 1000
    for _ in range(repetitions):
        simulate_press(modules_map)

    outputs_counts = [repetitions, 0]
    for module in modules_map.values():
        outputs_counts[0] += module.outputs_counts[0] * len(module.targets)
        outputs_counts[1] += module.outputs_counts[1] * len(module.targets)

    return outputs_counts[0] * outputs_counts[1]


def find_computation_tree(modules_map: dict[str, StatefulModule], name: str):
    res = set([name])
    ff = [name]
    while len(ff) > 0:
        name = ff.pop()
        for other in modules_map[name].input_states:
            if other in res or other == "button":
                continue

            res.add(other)
            ff.append(other)

    return res


def serialize_computation_tree(computation_tree, modules_map):
    return tuple(modules_map[x].output for x in computation_tree)


def find_computation_cycle(modules: list[Module], name: str):
    modules_map = make_stateful_modules(modules)
    computation_tree = find_computation_tree(modules_map, name)

    observed_states = {}
    state = serialize_computation_tree(computation_tree, modules_map)
    curr_time = 0

    while state not in observed_states:
        observed_states[state] = curr_time
        curr_time += 1
        track_result = simulate_press(modules_map, track_module=name)
        state = serialize_computation_tree(computation_tree, modules_map)

    return curr_time - 1


def part_2(modules: list[Module]):
    modules_map = make_stateful_modules(modules)
    output_module = modules_map["rx"]
    output_module = modules_map[list(output_module.input_states)[0]]
    return lcm(
        *(
            find_computation_cycle(modules, name)
            for name in output_module.input_states.keys()
        )
    )


def main():
    modules = list(read_lines())
    print("part_1:", part_1(modules))
    print("part_2:", part_2(modules))


if __name__ == "__main__":
    main()
