import sys
import bs4


def main():
    html = "".join(sys.stdin)
    soup = bs4.BeautifulSoup(html, "html.parser")

    body = soup.body

    calendar = body.find("pre", class_="calendar")

    days = calendar.find_all("a")

    days_map = {}

    for day in days:
        day_index = next(
            int(x.replace("calendar-day", ""))
            for x in day["class"]
            if x.startswith("calendar-day")
        )
        very_complete = "calendar-verycomplete" in day["class"]
        complete = "calendar-complete" in day["class"]
        days_map[day_index] = {
            "score": "x" if very_complete else "*" if complete else " ",
            "url": day["href"],
            "title": f"Day {day_index}",
        }

    for day_index in sorted(days_map):
        day = days_map[day_index]
        score = day["score"]
        title = day["title"]
        url = day["url"]
        print(f"- [{score}] {title} [url](https://adventofcode.com{url})")


if __name__ == "__main__":
    main()
