import sys
import os
import bs4
import requests
import argparse
from collections import namedtuple

CSES_SESSION_ENVVAR = "CSES_SESSION"
Task = namedtuple("Task", ["title", "url", "score"])
TaskGroup = namedtuple("TaskGroup", ["title", "tasks"])


def parse_args(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--session_id",
        help="The value of PHPSESSID",
        default=os.environ.get(CSES_SESSION_ENVVAR),
        type=str,
        required=os.environ.get(CSES_SESSION_ENVVAR) is None,
    )
    parser.add_argument(
        "--request_timeout",
        help="The timeout for the problemset request",
        default=10,
    )
    parser.add_argument(
        "--readme",
        help="The path of the original README file",
        type=argparse.FileType("w"),
        default=sys.stdout,
    )
    return parser.parse_args(argv)


def update_readme(args, task_groups):
    new_contents = ["# CSES Problem Set\n", "https://cses.fi"]

    for group in task_groups:
        new_contents.append("")
        new_contents.append(f"## {group.title}\n")

        for task in group.tasks:
            new_contents.append(
                f"- [{task.score}] {task.title} [url](https://cses.fi{task.url})"
            )

    args.readme.write("\n".join(new_contents) + "\n")


def main(argv):
    args = parse_args(argv)

    page_contents = requests.get(
        "https://cses.fi/problemset/",
        cookies={"PHPSESSID": args.session_id},
        timeout=args.request_timeout,
    )
    if not page_contents.ok:
        print(page_contents.status_code, file=sys.stderr)
        raise SystemExit("Error requesting page")

    soup = bs4.BeautifulSoup(page_contents.text, "html.parser")

    body = soup.body
    assert body is not None

    content = body.find("div", class_="content")

    task_groups = []

    for h2 in content.find_all("h2"):
        if h2.text.lower() == "general":
            continue

        group = TaskGroup(h2.text, [])

        ul = h2.find_next_sibling("ul")
        for li in ul.find_all("li"):
            a = li.find("a")
            url = a["href"]
            title = a.text

            icon_class = li.find("span", class_="task-score")["class"]
            score_styles = {
                "full": "x",
                "zero": "0",
            }
            score = score_styles.get(icon_class[-1], " ")

            group.tasks.append(Task(title, url, score))

        task_groups.append(group)

    update_readme(args, task_groups)


if __name__ == "__main__":
    main(sys.argv[1:])
