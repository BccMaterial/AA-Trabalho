class Solution:
    def diffWaysToCompute(self, expression: str) -> list[int]:
        memo = {}

        def resolver(expr: str) -> list[int]:
            if expr in memo:
                return memo[expr]

            resultados = []

            for i, char in enumerate(expr):
                if char in "+-*":
                    esquerda = resolver(expr[:i])
                    direita = resolver(expr[i + 1:])

                    for e in esquerda:
                        for d in direita:
                            if char == "+":
                                resultados.append(e + d)
                            elif char == "-":
                                resultados.append(e - d)
                            else:
                                resultados.append(e * d)

            #Caso base: apenas um número
            if not resultados:
                resultados.append(int(expr))

            memo[expr] = resultados
            return resultados

        return resolver(expression)

#As possíveis maneiras de colocar parênteses em uma ezpressão de n operadores segue a sequência de números de Catalan.
#C_n ≈ 4^n / n^(3/2)
#Sendo n o número de operadores, a quantidade de resultados possíveis pode crescer de maneira exponencial
#Complexidade de tempo: O(C_n) ou O(4^n / n^(3/2))