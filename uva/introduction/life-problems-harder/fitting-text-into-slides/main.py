MIN_FONT = 8
MAX_FONT = 28

def can_fit (paragraphs, slide_size, font):
    remaining_lines = slide_size[1] // font
    max_columns = slide_size[0] // font

    for paragraph in paragraphs:
        columns = max_columns
        space_needed = False
        for word in paragraph.split(' '):
            if len(word) > max_columns:
                return False

            if space_needed:
                # add space
                columns -= 1

            if columns - len(word) < 0:
                # start new line
                columns = max_columns - (len(word) + 1)
                remaining_lines -= 1
                space_needed = False
            else:
                # put on current line
                columns -= len(word)
                space_needed = True

        remaining_lines -= 1

    return remaining_lines >= 0


def best_fit (paragraphs, slide_size):
    return next((font for font in range(MAX_FONT, MIN_FONT - 1, -1)
                if can_fit(paragraphs, slide_size, font)), None)


def main ():
    t = int(input().strip())
    for _ in range(t):
        n = int(input().strip())
        paragraphs = [input().strip() for _ in range(n)]
        slide_size = tuple(int(x) for x in input().strip().split())

        font = best_fit(paragraphs, slide_size)
        print('No solution' if font is None else font)


if __name__ == '__main__':
    main()
