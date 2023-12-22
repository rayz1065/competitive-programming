import re
from collections import namedtuple

Workflow = namedtuple("Workflow", ["name", "rules"])
Part = namedtuple("Part", ["x", "m", "a", "s"])


class Rule:
    def __init__(self, target: str):
        self.target = target

    def check(self, part: Part):
        raise NotImplementedError

    def split(self, part_min: Part, part_max: Part):
        raise NotImplementedError


class UnconditionalRule(Rule):
    def __init__(self, target: str):
        super().__init__(target)

    def check(self, part):
        return True

    def split(self, part_min: Part, part_max: Part):
        return [(part_min, part_max)]


class ConditionalRule(Rule):
    def __init__(self, variable, sign, value, target: str):
        super().__init__(target)
        self.variable = variable
        self.sign = sign
        self.value = value

    def check(self, part: Part):
        value = getattr(part, self.variable)
        if self.sign == "<":
            return value < self.value
        if self.sign == ">":
            return value > self.value

        assert False, f"{sign} not known"

    def split(self, part_min: Part, part_max: Part):
        if self.check(part_min) == self.check(part_max):
            # this all maps to the same branch
            return [(part_min, part_max)]

        split_point_a = part_max._asdict()
        split_point_b = part_min._asdict()

        if self.sign == "<":
            split_point_a[self.variable] = self.value - 1
            split_point_b[self.variable] = self.value
        else:
            split_point_a[self.variable] = self.value
            split_point_b[self.variable] = self.value + 1

        split_point_a = Part(**split_point_a)
        split_point_b = Part(**split_point_b)

        return [(part_min, split_point_a), (split_point_b, part_max)]


def read_workflows():
    while True:
        try:
            line = input().strip()
            if line == "":
                break
        except EOFError:
            break

        res = re.match(r"^(\w+)\{(.+)\}$", line)
        name = res[1]
        rules_str = res[2].split(",")
        rules = []

        for rule in rules_str:
            if ":" in rule:
                res = re.match(r"^([xmas])([<>])(\d+):(\w+)$", rule)
                rules.append(ConditionalRule(res[1], res[2], int(res[3]), res[4]))
            else:
                rules.append(UnconditionalRule(rule))

        yield Workflow(name, rules)


def read_parts():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(r"\{x=(\d+),m=(\d+),a=(\d+),s=(\d+)\}", line)
        yield Part(*(int(x) for x in res.groups()))


def find_rule(rules: list[Rule], part: Part):
    for rule in rules:
        if rule.check(part):
            return rule

    assert False


def follow_workflows(workflows: list[Workflow], part: list[Part]):
    workflows_dict = {name: rules for name, rules in workflows}
    curr = "in"
    while curr not in "AR":
        curr = find_rule(workflows_dict[curr], part).target

    return curr


def part_1(workflows: list[Workflow], parts: list[Part]):
    return sum(sum(part) for part in parts if follow_workflows(workflows, part) == "A")


def part_2(workflows: list[Workflow], parts: list[Part]):
    workflows_dict = {name: rules for name, rules in workflows}

    part_min = Part(1, 1, 1, 1)
    part_max = Part(4000, 4000, 4000, 4000)

    ff = [("in", (part_min, part_max))]
    accepted_ranges = []

    while len(ff) > 0:
        curr, (part_min, part_max) = ff.pop()

        if curr == "A":
            accepted_ranges.append((part_min, part_max))
            continue
        if curr == "R":
            continue

        rules = workflows_dict[curr]

        for rule in rules:
            new_splits = rule.split(part_min, part_max)
            part_min, part_max = None, None

            for new_part_min, new_part_max in new_splits:
                assert rule.check(new_part_min) == rule.check(new_part_max)

                # check where they are assigned
                if rule.check(new_part_min):
                    # passed through a different workflow
                    ff.append((rule.target, (new_part_min, new_part_max)))
                else:
                    # needs to check next rule
                    assert part_min is None
                    part_min, part_max = new_part_min, new_part_max

            if part_min is None:
                # everything already consumed
                break

    sum_ = 0
    for part_min, part_max in accepted_ranges:
        prod_ = 1
        for x, x2 in zip(part_min, part_max):
            prod_ *= x2 - x + 1
        sum_ += prod_

    return sum_


def main():
    workflows = list(read_workflows())
    parts = list(read_parts())

    print("part_1:", part_1(workflows, parts))
    print("part_2:", part_2(workflows, parts))


if __name__ == "__main__":
    main()
