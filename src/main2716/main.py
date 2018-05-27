import sys
import re

limite_y = 4000
entrada = None
pd = None
X = None

def get_n_elementos_sequencia(linha):
    match = re.search('(\d+)\n', linha)
    if match:
        return match.group(1)
    return None


def get_indice_coluna(diferenca):
    diferenca_coluna = 2000 + diferenca
    return diferenca_coluna


def get_valor_coluna(coluna):
    return coluna - 2000


def set_valor_coluna(elemento, coluna):
    if coluna >= 0 and coluna < 4001:
        global pd
        pd[elemento][coluna] = 1


def calcula_diferenca_minima():
    pd[0][get_indice_coluna(X[0])] = 1
    pd[0][get_indice_coluna(-X[0])] = 1

    for elemento in range(1, len(pd)):
        indices = [idx for idx, valor in enumerate(pd[elemento - 1]) if valor == 1]
        for indice in indices:
            valor_acumulado = get_valor_coluna(indice)
            coluna = get_indice_coluna(valor_acumulado + X[elemento]) 
            set_valor_coluna(elemento, coluna)
            coluna = get_indice_coluna(valor_acumulado - X[elemento]) 
            set_valor_coluna(elemento, coluna)


def get_valor_minimo_positivo_linha(linha):
    indices = [idx for idx, valor in enumerate(linha) if valor == 1]
    valores = list(map(get_valor_coluna, indices))
    valores = filter(lambda x: x >= 0, valores)
    return min(valores)


def main():
    global entrada
    entrada = sys.stdin

    linha = entrada.readline()
    while linha:
        N = get_n_elementos_sequencia(linha)
        linha = entrada.readline()
        global X
        X = map(int, re.findall(r'\d+', linha))
        global pd
        pd = [[-1 for j in range(4001)] for i in range(len(X))]

        calcula_diferenca_minima()
        minimo = get_valor_minimo_positivo_linha(pd[len(X) - 1])
        print(minimo)

        linha = entrada.readline()
        

if __name__ == "__main__":
    main()
