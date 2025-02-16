from typing import List

def pollice_verde(n: int, heights: List[int]) -> int:
    last_height = -1
    last_watered = False
    res = 0
    for height in heights:
        if height < last_height and last_watered:
            # this is still watered
            pass
        elif height < last_height and not last_watered:
            # need to water the previous one, water will flow down
            res += 1
            last_watered = True
        elif height == last_height and not last_watered:
            # need to water the previous one
            res += 1
        else:
            last_watered = False

        last_height = height

    if not last_watered:
        res += 1

    return res
