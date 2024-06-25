import heapq


class MedianFinder:

    def __init__(self):
        self.left_heap = []  # great first
        self.right_heap = []  # small first

    def addNum(self, num: int) -> None:
        if not self.left_heap or num < -self.left_heap[0]:
            heapq.heappush(self.left_heap, -num)
        else:
            heapq.heappush(self.right_heap, num)

        while len(self.left_heap) > len(self.right_heap):
            heapq.heappush(self.right_heap, -self.left_heap[0])
            heapq.heappop(self.left_heap)

        while len(self.left_heap) < len(self.right_heap):
            heapq.heappush(self.left_heap, -self.right_heap[0])
            heapq.heappop(self.right_heap)

    def findMedian(self) -> float:
        if len(self.left_heap) > len(self.right_heap):
            return -self.left_heap[0]
        return (-self.left_heap[0] + self.right_heap[0]) / 2


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
