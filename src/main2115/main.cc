#include <inttypes.h>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <tuple>

template <typename T>
std::vector<T> ordenar_indices_por_tempo_disponibilidade(const std::vector<std::tuple<uint32_t, uint32_t> > &tarefas) {
  std::vector<T> idx;
  idx.resize(tarefas.size());
  for(uint32_t i = 0; i < idx.size(); i++) { idx[i] = i; }
  std::sort(idx.begin(), idx.end(),
       [&](T i1, T i2) {
           auto d1 = std::get<0>(tarefas[i1]);
           auto d2 = std::get<0>(tarefas[i2]);
           if (d1 != d2) {
               return d1 < d2;
           } else {
               return std::get<1>(tarefas[i1]) < std::get<1>(tarefas[i2]);
           }
       });

  return idx;
}

std::vector<std::tuple<uint32_t, uint32_t> > rearranjar(const std::vector<std::tuple<uint32_t, uint32_t> > &tarefas, std::vector<uint32_t>& idx) {
    std::vector<std::tuple<uint32_t, uint32_t> > novo(tarefas.size());
    uint32_t v_idx = 0;
    std::vector<uint32_t>::iterator it;
    for (it = idx.begin(); it != idx.end(); it++) {
        std::get<0>(novo[v_idx]) = std::get<0>(tarefas[*it]); 
        std::get<1>(novo[v_idx]) = std::get<1>(tarefas[*it]);
        v_idx++;
    }
    return novo;
}

uint32_t calcula_menor_instante(std::vector<std::tuple<uint32_t, uint32_t> >& tarefas) {
    uint32_t instante = std::get<0>(tarefas[0]) + std::get<1>(tarefas[0]);
    std::vector<std::tuple<uint32_t, uint32_t> >::iterator it = tarefas.begin() + 1;
    for (; it != tarefas.end(); it++) {
        if (instante < std::get<0>(*it)) {
            instante = std::get<0>(*it);
        }
        instante = instante + std::get<1>(*it);
    }
    return instante;
}

int main(int argc, char **argv) {
    uint32_t N;
    FILE *entrada = stdin;
    int estado_leitura = fscanf(entrada, "%u\n", &N);

    while (estado_leitura != EOF) {

        std::vector<std::tuple<uint32_t, uint32_t> > tarefas(N);
        
        uint32_t d, p;
        for (uint32_t i = 0; i < N; i++) {
            fscanf(entrada, "%u %u\n", &d, &p);
            std::get<0>(tarefas[i]) = d;
            std::get<1>(tarefas[i]) = p;
        }

        std::vector<uint32_t> indices = ordenar_indices_por_tempo_disponibilidade<uint32_t>(tarefas);
        tarefas = rearranjar(tarefas, indices);

        printf("%d\n", calcula_menor_instante(tarefas));

        estado_leitura = fscanf(entrada, "%u\n", &N);
    }
    return 0;
}
