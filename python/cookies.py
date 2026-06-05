class Solution:
    def findContentChildren(self, g: list[int], s: list[int]) -> int:
        g.sort()
        s.sort()

        child = 0
        cookie = 0
        content = 0

        while child < len(g) and cookie < len(s):
            if s[cookie] >= g[child]:
                content += 1
                child += 1

            cookie += 1

        return content

#Greedy
#Parte dominante: g.sort()

#Para n = len(g) e m = len(s):
#Ordenar g: O(n log n)
#Ordenar s: O(m log m)
#Percorrer os vetores: O(n + m)

#Complexidade total: O(n log n + m log m)