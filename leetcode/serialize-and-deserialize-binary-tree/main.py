import json


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x, left, right):
        self.val = x
        self.left = left
        self.right = right


class Codec:

    def objectify(self, root):
        if root is None:
            return root
        return [root.val, self.objectify(root.left), self.objectify(root.right)]

    def serialize(self, root):
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        return json.dumps(self.objectify(root))

    def deobjectify(self, root):
        if root is None:
            return root
        val, left, right = root
        return TreeNode(val, self.deobjectify(left), self.deobjectify(right))

    def deserialize(self, data):
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        return self.deobjectify(json.loads(data))


# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# ans = deser.deserialize(ser.serialize(root))
