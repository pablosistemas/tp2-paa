#include <inttypes.h>
#include <algorithm>
#include <stdio.h>
#include <vector>

void le_arquivo_em_vetor(FILE *entrada, std::vector<uint32_t>& vetor, uint32_t S) {
    for (uint32_t j = 0; j < S - 1; j++) {
        fscanf(entrada, "%u ", &vetor[j]);
    }
    fscanf(entrada, "%u\n", &vetor[S-1]);
}

int main() {
    FILE *entrada = fopen("data/entrada2095", "r");
    if (entrada == NULL) {
        return -1;
    }

    uint32_t S;
    fscanf(entrada, "%u\n", &S);
    std::vector<uint32_t> Qi, Si;
    Qi.resize(S);
    Si.resize(S);
    le_arquivo_em_vetor(entrada, Qi, S);
    le_arquivo_em_vetor(entrada, Si, S);

    std::sort(Qi.begin(), Qi.end());
    std::sort(Si.begin(), Si.end());

    uint32_t num_vitorias = 0;
    uint32_t num_soldados_noglonia = 0;
    uint32_t num_soldados_quadradonia = 0;
    while(num_soldados_noglonia < S) {
        if (Si[num_soldados_noglonia++] > Qi[num_soldados_quadradonia]) {
            num_soldados_quadradonia++;
            num_vitorias++;
        }
    }

    fprintf(stdout, "%u\n", num_vitorias);

    fclose(entrada);
}
