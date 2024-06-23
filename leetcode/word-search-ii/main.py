from typing import List


class Solution:
    def in_range(self, r, c):
        return 0 <= r < len(self.board) and 0 <= c < len(self.board[r])

    def recompute_children(self, trie):
        trie["_children"] = int(trie["_flag"])
        for letter, child in trie.items():
            if not letter.startswith("_"):
                trie["_children"] += child["_children"]

    def make_trie(self, words):
        flag = False

        children_by_letter = {}

        for word in words:
            if word:
                children_by_letter.setdefault(word[0], [])
                children_by_letter[word[0]].append(word[1:])
            else:
                flag = True

        res = {"_flag": flag}
        for letter, words2 in children_by_letter.items():
            res[letter] = self.make_trie(words2)

        self.recompute_children(res)

        return res

    def explore_grid(self, trie, curr, r, c):
        if trie["_flag"]:
            self.found.add(curr)
            trie["_flag"] = False

        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            new_r, new_c = r + dr, c + dc
            if not self.in_range(new_r, new_c) or self.used[new_r][new_c]:
                continue

            cell = self.board[new_r][new_c]
            if (
                self.board[new_r][new_c] not in trie
                or trie[self.board[new_r][new_c]]["_children"] == 0
            ):
                continue

            self.used[new_r][new_c] = True
            res = self.explore_grid(
                trie[cell],
                curr + cell,
                new_r,
                new_c,
            )
            self.used[new_r][new_c] = False

            if res:
                return res

        self.recompute_children(trie)

        return False

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        self.found = set()
        self.used = [[False] * len(board[0]) for _ in enumerate(board)]
        self.board = board
        trie = self.make_trie(words)

        for r, row in enumerate(board):
            for c, cell in enumerate(row):
                if cell in trie:
                    self.used[r][c] = True
                    self.explore_grid(trie[cell], cell, r, c)
                    self.used[r][c] = False

        return list(self.found)
