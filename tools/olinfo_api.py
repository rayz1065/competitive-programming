import argparse
import itertools
import json
import os
import re
import sys
import time
from urllib.parse import quote_plus

import requests

TRAINING_TOKEN_ENVVAR = "TRAINING_TOKEN"
TRAINING_BETTER_AUTH_SESSION_TOKEN_ENVVAR = "TRAINING_BETTER_AUTH_SESSION_TOKEN"


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
            "naoi",
        ],
        help="The target competition",
    )
    parser.add_argument(
        "--token",
        help="The token to use for the API requests",
        default=os.environ.get(TRAINING_TOKEN_ENVVAR),
    )
    parser.add_argument(
        "--better_auth_session_token",
        help="The token to use for the API requests",
        default=os.environ.get(TRAINING_BETTER_AUTH_SESSION_TOKEN_ENVVAR),
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
    res = None
    if target == "weoi":
        res = {"search": "weoi_"}
    if target == "naoi":
        res = {"search": "naoi_"}
    if target == "itday":
        res = {"search": "itday_"}
    if target == "abc":
        res = {"tag": "abc"}
    if target == "gator":
        res = {"tag": "gator"}
    if target == "oii":
        res = {"tag": "nazionali"}
    if target == "pre-oii":
        res = {"tag": "pre-oii"}
    if target == "terry":
        res = {"tag": "territoriali"}
    if target == "ois":
        res = {"tag": "ois"}
    if target == "itoi":
        res = {"tag": "ioit"}

    if res is None:
        raise SystemExit(f"Invalid target {target}")

    res.setdefault("tag", "")
    res.setdefault("search", "")

    return res


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


def get_tasks(args):
    search_data = get_search(args.target)
    search = quote_plus(search_data["search"])
    tag = quote_plus(search_data["tag"])

    tasks = []
    for page in itertools.count():
        print(f"Fetching page {page + 1}...", file=sys.stderr)

        response = requests.get(
            f"https://training.olinfo.it/tasks/{page + 1}?tag={tag}&search={search}",
            headers={
                "User-Agent": "Task syncer (https://github.com/rayz1065/competitive-programming)",
                "Accept": "text/x-component",
                # magic next stuff
                "RSC": "1",
                "Next-Router-State-Tree": quote_plus(
                    """["",{"children":["(training)",{"children":["tasks",{"children":[["page","2","d"],{"children":["__PAGE__",{},null,null]},null,null]},null,null]},null,null]},null,null,true]"""
                ),
            },
            cookies={
                "training_token": args.token,
                "better-auth.session_token": args.better_auth_session_token,
            },
            timeout=args.api_timeout,
        )
        response.encoding = response.apparent_encoding

        print(
            f"Fetched page {page + 1} with status {response.status_code}",
            file=sys.stderr,
        )

        if not response.ok:
            raise SystemExit(f"Failed to fetch tasks: {response.text}")

        response_arr = response.text.strip().split("\n")
        found = [x for x in response_arr if '"taskList":' in x]
        if not found and page > 0:
            break

        if len(found) > 1:
            print("\n\n".join(found), file=sys.stderr)
            raise SystemExit("Tasks list duplicates in response")
        if not found:
            print("\n\n".join(response_arr), file=sys.stderr)
            raise SystemExit("Tasks list not found in response")

        data = json.loads(found[0].split(":", maxsplit=1)[1])

        data = [x for x in data if isinstance(x, dict) and "taskList" in x]
        tasks_page = data[0]["taskList"]

        tasks.extend(tasks_page)
        time.sleep(0.1)

    return tasks


def main(argv):
    args = parse_args(argv)
    if not args.token:
        raise SystemExit(f"Set {TRAINING_TOKEN_ENVVAR} or pass --token")

    tasks = get_tasks(args)
    print(f"Found {len(tasks)} tasks", file=sys.stderr)

    if args.readme:
        update_readme(args, tasks)
    else:
        for task in reversed(tasks):
            print(pprint_task(task))


if __name__ == "__main__":
    main(sys.argv[1:])
