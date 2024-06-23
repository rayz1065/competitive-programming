from typing import Optional


class ListNode:
    def __init__(self, val=0, next_=None):
        self.val = val
        self.next = next_


class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        previous = None
        new_head = None

        while head is not None:
            section = [head]

            crawl = head.next
            for _ in range(k - 1):
                if crawl is not None:
                    section.append(crawl)
                    crawl = crawl.next

            if len(section) != k:
                break

            next_head = section[-1].next

            # invert all edges inside
            for i in range(k - 1):
                section[i + 1].next = section[i]

            # link from previous to end
            if previous is not None:
                previous.next = section[-1]
            else:
                new_head = section[-1]

            # link from head to next head
            head.next = next_head
            previous = head

            head = next_head

        return new_head
