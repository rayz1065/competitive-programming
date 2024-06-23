from typing import List, Optional


class ListNode:
    def __init__(self, val=0, next_=None):
        self.val = val
        self.next = next_


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        all_sorted = []

        item_score = lambda x: 10**5 if x is None else x.val

        lists.sort(key=item_score)

        while True:
            best = 10**5
            best_i = None
            for i, lst in enumerate(lists):
                if lst is not None and lst.val < best:
                    best = lst.val
                    best_i = i

            if best_i is None:
                break

            all_sorted.append(best)
            lists[best_i] = lists[best_i].next

        res = None
        for val in reversed(all_sorted):
            res = ListNode(val=val, next_=res)

        return res
