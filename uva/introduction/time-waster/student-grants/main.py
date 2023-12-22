def simulate(n_students, max_k):
    missing = [40] * n_students
    queue = list(range(n_students))
    curr_k = 1
    output_store = 1
    result = []

    while len(queue) > 0:
        student = queue[0]
        queue = queue[1:]
        payed_out = min(missing[student], output_store)

        missing[student] -= payed_out
        output_store -= payed_out
        if missing[student] > 0:
            queue.append(student)
        else:
            result.append(student)

        if output_store == 0:
            curr_k = (curr_k % max_k) + 1
            output_store = curr_k

    return result


def main ():
    while True:
        n_students, max_k = (int(x) for x in input().strip().split())
        if (n_students, max_k) == (0, 0):
            break

        result = simulate(n_students, max_k)

        print(''.join(str(x + 1).rjust(3) for x in result))


if __name__ == '__main__':
    main()
