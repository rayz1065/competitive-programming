def leave_blank (page, n):
    if page > n:
        return 'Blank'
    return page


def main ():
    while True:
        n = int(input().strip())
        if n == 0:
            break

        pages_count = n // 4 + (n % 4 > 0)
        pages_cap = pages_count * 4

        print(f'Printing order for {n} pages:')
        for page in range(pages_count):
            front = (pages_cap - page * 2, page * 2 + 1)
            back = (page * 2 + 2, pages_cap - page * 2 - 1)
            front = tuple(leave_blank(x, n) for x in front)
            back = tuple(leave_blank(x, n) for x in back)
            print(f'Sheet {page + 1}, front: {front[0]}, {front[1]}')
            if back != ('Blank', 'Blank'):
                print(f'Sheet {page + 1}, back : {back[0]}, {back[1]}')


if __name__ == '__main__':
    main()
