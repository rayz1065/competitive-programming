import sys
import bs4


def main():
    html = "".join(sys.stdin)
    soup = bs4.BeautifulSoup(html, "html.parser")

    body = soup.body
    content = body.find("div", class_="content")

    print("# CSES Problem Set", end="\n\n")
    print("https://cses.fi")

    for h2 in content.find_all("h2"):
        if h2.text.lower() == "general":
            continue

        print()
        print(f"## {h2.text}", end="\n\n")

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

            print(f"- [{score}] {title} [url](https://cses.fi{url})")


if __name__ == "__main__":
    main()
