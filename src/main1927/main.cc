#include <inttypes.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <limits>
#include <tuple>

#define TEMPO_MAXIMO 1000
#define COORD 20

typedef std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> tipo_tupla;
std::vector<std::vector<std::vector<uint32_t> > > dp(COORD+1);
std::vector<tipo_tupla> tapioca;

uint32_t NAO_INICIALIZADO = std::numeric_limits<uint32_t>::max();

std::vector<tipo_tupla>::iterator eh_solucao(std::tuple<uint32_t, uint32_t, uint32_t>& coordenada) {
    auto it = std::find_if(tapioca.begin(), tapioca.end(), 
        [&](std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>& t) {
        return std::get<0>(t) == std::get<0>(coordenada) && 
               std::get<1>(t) == std::get<1>(coordenada) && 
               std::get<2>(t) == std::get<2>(coordenada);
    });
    return it;
}

uint32_t dp_a(int32_t x, int32_t y, uint32_t tempo, uint32_t positivo) {
    if (x < 0 || x > COORD || y < 0 || y > COORD || tempo > TEMPO_MAXIMO) {
        return 0;
    }

    if (dp[x][y][tempo] != NAO_INICIALIZADO) {
        return dp[x][y][tempo];
    }

    int32_t num_solucoes = std::max(
        dp_a(x-1, y, tempo+1, positivo),
        std::max(dp_a(x, y-1, tempo+1, positivo),
        std::max(dp_a(x+1, y, tempo+1, positivo),
            std::max(dp_a(x, y+1, tempo+1, positivo),
                    dp_a(x, y, tempo+1, positivo)))));

    auto tupla = std::make_tuple<uint32_t, uint32_t, uint32_t>((uint32_t)x, (uint32_t)y, (uint32_t)tempo);
    auto it = eh_solucao(tupla);
    if (it != tapioca.end()) {
        uint32_t incremento = std::get<3>(*it);
        if (dp[x][y][tempo] != NAO_INICIALIZADO) {
            if ((uint32_t)(num_solucoes + incremento) > dp[x][y][tempo]){
                dp[x][y][tempo] = (uint32_t)num_solucoes + incremento;
            }
        } else {
            dp[x][y][tempo] = (uint32_t)num_solucoes + incremento;
        }
    } else {
        if (dp[x][y][tempo] == NAO_INICIALIZADO || (uint32_t)num_solucoes > dp[x][y][tempo]) {
            dp[x][y][tempo] = (uint32_t)num_solucoes;
        }
    }
    return dp[x][y][tempo];
}

std::vector<tipo_tupla>::iterator tapioca_repetida(uint32_t x, uint32_t y, uint32_t t) {
    auto it = tapioca.begin();
    for(; it != tapioca.end(); it++) {
        if (std::get<0>(*it) == x && std::get<1>(*it) == y && std::get<2>(*it) == t) {
            return it;
        }
    }
    return it;
}

int main() {
    uint32_t n;
    FILE *entrada = stdin;
    fscanf(entrada, "%u\n", &n);

    for(auto it = dp.begin(); it != dp.end(); it++){
        it->resize(COORD + 1);
        for(auto iti = it->begin(); iti != it->end(); iti++){
            iti->resize(1001);
            for(auto itii = iti->begin(); itii != iti->end(); itii++) {
                *itii = NAO_INICIALIZADO;
            }
        }
    }

    tapioca.resize(n);
    uint32_t proximo_elemento = 0;
    for(uint32_t i = 0; i < n; i++) {
        uint32_t x, y, t;
        fscanf(entrada, "%u %u %u\n", &x, &y, &t);
        auto it = tapioca_repetida(x, y, t);
        if (it == tapioca.end())
            tapioca[proximo_elemento++] = std::make_tuple(x, y, t, 1);
        else {
            std::get<3>(*it) = std::get<3>(*it) + 1;
        }
    }

    dp_a(6, 6, 0, 0);

    fprintf(stdout, "%u\n", dp[6][6][0]);
    fclose(entrada);

    return 0;
}
