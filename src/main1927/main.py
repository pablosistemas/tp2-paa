import sys
import re

maximo_trufas_geral = (0, None)
origem = (6, 6, 0)
max_tempo = 1000
tripla = None
pd = None


def alcancavel(origem, destino):
    distancia = abs(origem[0] - destino[0]) + abs(origem[1] - destino[1])
    tempo_viagem = distancia
    if tempo_viagem <= (destino[2] - origem[2]):
        return True
    return False


def atualiza_maximo_trufas(indice_tripla):
    global maximo_trufas_geral
    if pd[indice_tripla][tripla[indice_tripla][2]][0] > maximo_trufas_geral[0]:
        maximo_trufas_geral = (pd[indice_tripla][tripla[indice_tripla][2]][0], tripla[indice_tripla])


def calcula_trufas(indice_tripla):
    global pd
    if pd[indice_tripla][tripla[indice_tripla][2]] != -1:
        return pd[indice_tripla][tripla[indice_tripla][2]]

    if indice_tripla == 0:
        if alcancavel(origem, tripla[indice_tripla]):
            pd[indice_tripla][tripla[indice_tripla][2]] = (tripla[indice_tripla][3], origem)
            atualiza_maximo_trufas(indice_tripla)
            return pd[indice_tripla][tripla[indice_tripla][2]]
        return (0, None)

    maximo_trufas_anteriores = (0, None)

    # se alcancavel diretamente pela origem
    if alcancavel(origem, tripla[indice_tripla]):
        maximo_trufas_anteriores = (tripla[indice_tripla][3], origem)

    for i in range(indice_tripla):
        trufas_anteriores = calcula_trufas(i)
        if alcancavel(tripla[i], tripla[indice_tripla]):
            incremento = tripla[indice_tripla][3]
            if (trufas_anteriores[0] + incremento) > maximo_trufas_anteriores[0]:
                maximo_trufas_anteriores = (trufas_anteriores[0] + incremento, tripla[i])

    pd[indice_tripla][tripla[indice_tripla][2]] = maximo_trufas_anteriores
    atualiza_maximo_trufas(indice_tripla)

    return pd[indice_tripla][tripla[indice_tripla][2]]


def ordena_por_momento_queda(tripla_l):
    return sorted(tripla_l, key=lambda x: x[2])


def inicializa_pd(n):
    global pd
    pd = [[-1 for j in range(max_tempo + 1)] for i in range(n)]


def main():
    entrada = sys.stdin

    linha = entrada.readline()
    n = int(re.match('(\d+)', linha).group(1))

    global tripla
    inicializa_pd(n)

    tripla = []

    for i in range(n):
        linha = entrada.readline()
        tri = map(int, re.findall(r'\d', linha))
        if [item for item in tripla if item[0] == tri[0]]:
            indice = None
            for idx, item in enumerate(tripla):
                if tri[0] == item[0] and tri[1] == item[1] and tri[2] == item[2]:
                    indice = idx
                    break
            if indice is not None:
                tripla[indice] = (tripla[indice][0], tripla[indice][1], tripla[indice][2], tripla[indice][3] + 1)
        else:
            tripla.append((tri[0], tri[1], tri[2], 1))
    
    tripla = ordena_por_momento_queda(tripla)

    calcula_trufas(len(tripla) - 1)
    print(maximo_trufas_geral[0])

    entrada.close()


if __name__ == "__main__":
    main()
    

'''
for tempo in tempos:
    if alcancavel((tripla[linha - 1][0], tripla[linha - 1][1], tempo), tripla[linha]):
        pd[linha][tripla[linha][2]] = 1 
'''

'''
def calcula_trufas():
    max_trufas = 0
    for linha in range(len(pd)):
        if alcancavel(origem, tripla[linha]):
            pd[linha][tripla[linha][2]] = 1

        # tempos = [idx for idx, valor in enumerate(linha - 1) if valor == 1]
        # if alcancavel((tripla[linha - 1][0], tripla[linha - 1][1], tempo), tripla[linha]):
        for linha_anterior in range(linha):
            if alcancavel(tripla[linha_anterior], tripla[linha]):
                #pd[linha][tripla[linha][2]] = pd[linha][tripla[linha][2]] + pd[linha - 1][tripla[linha - 1][2]]
                pd[linha][tripla[linha][2]] = max(pd[linha][tripla[linha][2]], pd[linha_anterior][tripla[linha_anterior][2]] + 1)
                
        if pd[linha][tripla[linha][2]] > max_trufas:
            max_trufas = pd[linha][tripla[linha][2]]
    return max_trufas
'''
