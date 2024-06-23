from typing import Optional


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def solve(self, root):
        # (path up to root, internal path)
        children = [self.solve(x) for x in (root.left, root.right) if x is not None]

        # don't take any node, or take just the root
        path_to_root = max(0, root.val)

        # take the root and a child
        if children:
            path_to_root = max(path_to_root, root.val + max(x[0] for x in children))

        # take just the root
        internal = root.val

        if children:
            # root and one child
            internal = max(internal, internal + max(x[0] for x in children))

            # best child
            internal = max(internal, max(x[1] for x in children))

        if len(children) == 2:
            # both children
            internal = max(internal, sum(x[0] for x in children) + root.val)

        return path_to_root, internal

    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        res = self.solve(root)

        return res[1]
