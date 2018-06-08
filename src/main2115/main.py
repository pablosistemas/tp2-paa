import sys
import re

dp = None
dp_ordenado = None

def ordena_por_tempo_fim(dpl):
    return sorted(dpl, key=lambda x: x[0])


def calcula_menor_instante():
    instante = dp_ordenado[0][0] + dp_ordenado[0][1]
    for tupla in dp_ordenado[1:]:
        if instante < tupla[0]:
            instante = tupla[0]
        instante = instante + tupla[1]
    return instante


def main():
    entrada = sys.stdin

    linha = entrada.readline()
    global dp, dp_ordenado

    while linha:
        N = int(re.search('(\d+)\n', linha).group(1))
        dp = []
        for i in range(N):
            linha = entrada.readline()
            dp.append(list(map(int, re.findall(r'\d+', linha))))
        dp_ordenado = ordena_por_tempo_fim(dp)
        instante = calcula_menor_instante()
        print(instante)

        linha = entrada.readline()


if __name__ == "__main__":
    main()
