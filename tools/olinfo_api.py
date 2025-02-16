import re
import sys
import os
import requests
import argparse

TRAINING_TOKEN_ENVVAR = "TRAINING_TOKEN"


def parse_args(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "target",
        choices=[
            "weoi",
            "itday",
            "abc",
            "gator",
            "oii",
            "pre-oii",
            "terry",
            "ois",
            "itoi",
        ],
        help="The target competition",
    )
    parser.add_argument(
        "--token",
        help="The token to use for the API requests",
        default=os.environ.get(TRAINING_TOKEN_ENVVAR),
    )
    parser.add_argument(
        "--readme",
        help="The path of the original README file",
        type=argparse.FileType("r+"),
    )
    parser.add_argument(
        "--api_timeout",
        help="The timeout for the API requests",
        default=10,
    )
    return parser.parse_args(argv)


def get_search(target):
    if target == "weoi":
        return {"search": "weoi_"}
    if target == "itday":
        return {"search": "itday_"}
    if target == "abc":
        return {"tag": "abc"}
    if target == "gator":
        return {"tag": "gator"}
    if target == "oii":
        return {"tag": "nazionali"}
    if target == "pre-oii":
        return {"tag": "pre-oii"}
    if target == "terry":
        return {"tag": "territoriali"}
    if target == "ois":
        return {"tag": "ois"}
    if target == "itoi":
        return {"tag": "ioit"}
    raise SystemExit(f"Invalid target {target}")


def get_url(task):
    return f"https://training.olinfo.it/#/task/{task['name']}/statement"


def pprint_task(task):
    solved = "score" in task and task["score"] == 100
    check = "x" if solved else " "
    url = get_url(task)
    return f"- [{check}] {task['title']} ({task['name']}) [url]({url})"


def update_readme(args, tasks):
    tasks_by_url = {get_url(task): task for task in tasks}
    unmatched = set(tasks_by_url)

    f = args.readme
    readme_contents = f.readlines()

    updated_lines = 0
    for i, line in enumerate(readme_contents):
        match = re.match(r".+\[url\]\((.*)\)", line)
        if match is None:
            continue
        url = match.group(1)
        task = tasks_by_url.get(url)
        if task is None:
            continue
        if readme_contents[i] != (replacement := pprint_task(task) + "\n"):
            readme_contents[i] = replacement
            updated_lines += 1
        if url not in unmatched:
            print(f"Duplicate entry {url}", file=sys.stderr)
        else:
            unmatched.remove(url)

    print(f"Updated {updated_lines} lines", file=sys.stderr)

    if unmatched:
        print(f"Found {len(unmatched)} unmatched tasks", file=sys.stderr)

        readme_contents.append("\n## Unsorted\n\n")
        for task in reversed(tasks):
            if get_url(task) not in unmatched:
                continue
            readme_contents.append(pprint_task(task) + "\n")

    f.seek(0)
    f.writelines(readme_contents)


def main(argv):
    args = parse_args(argv)
    if not args.token:
        raise SystemExit(f"Set {TRAINING_TOKEN_ENVVAR} or pass --token")

    response = requests.post(
        "https://training.olinfo.it/api/task",
        headers={
            "Content-Type": "application/json",
            "Cookie": f"training_token={args.token}",
        },
        json={
            "action": "list",
            "first": 0,
            "last": 9999,
            **get_search(args.target),
        },
        timeout=args.api_timeout,
    )
    if not response.ok:
        raise SystemExit(f"Failed to fetch tasks: {response.text}")

    tasks = response.json()["tasks"]
    print(f"Found {len(tasks)} tasks", file=sys.stderr)

    if args.readme:
        update_readme(args, tasks)
    else:
        for task in reversed(tasks):
            print(pprint_task(task))


if __name__ == "__main__":
    main(sys.argv[1:])
