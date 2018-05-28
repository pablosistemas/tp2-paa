import sys
import re

coordenada_maxima = 2000
limite_y = coordenada_maxima * 2 + 1
indices = [0 for i in range(limite_y)]
iterador_indices = 0
pd = None
X = None


def get_indice_coluna(diferenca):
    diferenca_coluna = coordenada_maxima + diferenca
    return diferenca_coluna


def get_valor_coluna(coluna):
    return coluna - coordenada_maxima


def set_valor_coluna(elemento, valor_acumulado, diferenca):
    global pd, indices, iterador_indices
    coluna = get_indice_coluna(valor_acumulado + diferenca)
    if coluna >= 0 and coluna < limite_y and pd[elemento][coluna] == -1:
        pd[elemento][coluna] = 1
        indices[iterador_indices] = coluna
        iterador_indices = iterador_indices + 1

    coluna = get_indice_coluna(valor_acumulado - diferenca)
    if coluna >= 0 and coluna < limite_y and pd[elemento][coluna] == -1:
        pd[elemento][coluna] = 1
        indices[iterador_indices] = coluna
        iterador_indices = iterador_indices + 1
        

def calcula_diferenca_minima():
    global iterador_indices
    iterador_indices = 0
    set_valor_coluna(0, 0, X[0])

    for elemento in range(1, len(pd)):
        indices_antigos = [ idx for idx in indices[0:iterador_indices] ]
        iterador_indices = 0
        for indice in indices_antigos:
            valor_acumulado = get_valor_coluna(indice)
            set_valor_coluna(elemento, valor_acumulado, X[elemento])


def get_valor_minimo_positivo_linha(linha):
    for i in range(coordenada_maxima, limite_y):
        if linha[i] != -1:
            return i - coordenada_maxima


def main():
    global X, pd, diferenca_minima
    entrada = sys.stdin #open("data/entrada2716", "r") #sys.stdin

    linha = entrada.readline()
    while linha:
        N = int(re.match('(\d+)', linha).group(1))
        linha = entrada.readline()
        X = map(int, re.findall(r'\d+', linha))
        pd = [[-1 for j in range(limite_y)] for i in range(len(X))]
        calcula_diferenca_minima()
        minimo = get_valor_minimo_positivo_linha(pd[len(X) - 1])
        print(minimo)

        linha = entrada.readline()
    
    entrada.close()    

if __name__ == "__main__":
    main()
