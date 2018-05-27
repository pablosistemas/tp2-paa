import sys
import re

pd = None
tripla = None
origem = (6,6,0)
max_tempo = 1000

def alcancavel(origem, destino):
    distancia = abs(origem[0] - destino[0]) + abs(origem[1] - destino[1])
    tempo_viagem = distancia
    if tempo_viagem <= (destino[2] - origem[2]):
        return True
    return False

        
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

def main():
    #entrada = open('data/entrada1927', 'r')
    entrada = sys.stdin

    linha = entrada.readline()
    n = int(re.match('(\d+)', linha).group(1))

    global pd, tripla
    pd = [[-1 for j in range(max_tempo + 1)] for i in range(n)]
    tripla = []

    for i in range(n):
        linha = entrada.readline()
        tripla.append(map(int, re.findall(r'\d', linha)))
    
    tripla = sorted(tripla, key=lambda x: x[2])
    max_trufas = calcula_trufas()
    print(max_trufas)

    entrada.close()


if __name__ == "__main__":
    main()
    

'''
for tempo in tempos:
    if alcancavel((tripla[linha - 1][0], tripla[linha - 1][1], tempo), tripla[linha]):
        pd[linha][tripla[linha][2]] = 1 
'''
