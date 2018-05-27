#include <inttypes.h>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

template <typename T>
std::vector<T> ordenar_indices(const std::vector<T> &d, const std::vector<T> &p) {
  std::vector<T> idx;
  idx.resize(d.size());
  for(uint32_t i = 0; i < idx.size(); i++) { idx[i] = i; }
  std::sort(idx.begin(), idx.end(),
       [&](T i1, T i2) {
           if (d[i1] != d[i2]) {
               return d[i1] < d[i2];
           } else {
               return p[i1] < p[i2];
           }
       });

  return idx;
}

std::vector<uint32_t> rearranjar(const std::vector<uint32_t>& v, std::vector<uint32_t>& idx) {
    std::vector<uint32_t> novo(v.size());
    uint32_t v_idx = 0;
    std::vector<uint32_t>::iterator it;
    for (it = idx.begin(); it != idx.end(); it++) {
        novo[v_idx++] = v[*it]; 
    }
    return novo;
}

int main(int argc, char **argv) {
    uint32_t N;
    FILE *entrada = stdin; //fopen("data/entrada2115", "r");
    int estado_leitura = fscanf(entrada, "%u\n", &N);

    while (estado_leitura != EOF) {

        std::vector<uint32_t> d(N);
        std::vector<uint32_t> p(N);

        for (uint32_t i = 0; i < N; i++) {
            fscanf(entrada, "%u %u\n", &d[i], &p[i]);
        }

        uint32_t tarefas_concluidas = 0;
        uint32_t instante = 1;

        std::vector<uint32_t> indices = ordenar_indices<uint32_t>(d, p);
        d = rearranjar(d, indices);
        p = rearranjar(p, indices);

        std::vector<uint32_t> auxiliar;
        uint32_t indice = 0;
        while (d[indice] <= instante) {
            auxiliar.push_back(indice++);
        }

        while (tarefas_concluidas < N) {
            instante += p[auxiliar[0]];
            tarefas_concluidas++;

            auxiliar.erase(auxiliar.begin(), auxiliar.begin() + 1);
            while (d[indice] <= instante) {
                auxiliar.push_back(indice++);
            }
        }
        printf("%u\n", instante);

        estado_leitura = fscanf(entrada, "%u\n", &N);
    }
    return 0;
}
