class Solution:
    def partitionLabels(self, s: str) -> list[int]:
        last = {s[i]: i for i in range(len(s))}

        res = []
        i = 0

        while i < len(s):
            end = last[s[i]]
            j = i + 1

            while j < end:
                if last[s[j]] > end:
                    end = last[s[j]]

                j += 1

            res.append(end - i + 1)
            i = end + 1

        return res
