#include <stdio.h>
#include <inttypes.h>

int main() {
    FILE* entrada;
    entrada = fopen("data/entrada", "r");

    uint32_t n;
    int estado_entrada = fscanf(entrada, "%u\n", n);

    for(int i = 0; i < n; i++) {
        
    }

    fclose(entrada);

}