#include <inttypes.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <cmath>

int main(int argc, char** argv) {
    uint32_t N;
    std::vector<uint32_t> pesos_trabalhos;

    while(fscanf(stdin, "%u\n", &N) != EOF) {
        uint32_t ptr_rangel, ptr_gugu;
        pesos_trabalhos.resize(N);

        for (uint32_t i = 0; i < N - 1; i++) {
            fscanf(stdin, "%d ", &pesos_trabalhos[i]); 
        }
        fscanf(stdin, "%d\n", &pesos_trabalhos[N-1]); 

        std::sort(pesos_trabalhos.begin(), pesos_trabalhos.end());

        uint32_t soma_rangel = pesos_trabalhos[0];
        uint32_t soma_gugu = pesos_trabalhos[N-1];
        uint32_t num_trabalhos_repartidos = 2;
        ptr_rangel = 1;
        ptr_gugu = N-2;

        while(num_trabalhos_repartidos < N) {
            while(soma_rangel < soma_gugu && ptr_rangel <= ptr_gugu) {
                soma_rangel += pesos_trabalhos[ptr_rangel++];
                num_trabalhos_repartidos++;
            }
            while(soma_gugu < soma_rangel && ptr_rangel <= ptr_gugu) {
                soma_gugu += pesos_trabalhos[ptr_gugu++];
                num_trabalhos_repartidos++;
            }
        }

        fprintf(stdin, "%u\n", (uint32_t)std::abs(soma_gugu - soma_rangel));
    }

    //fclose(arq);
    return 0;
}
