#include <inttypes.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <limits>
#include <tuple>

#define TEMPO_MAXIMO 1000
#define COORD 20

std::vector<std::vector<std::vector<uint32_t> > > dp(COORD+1);
std::vector<std::tuple<uint32_t, uint32_t, uint32_t> > tapioca;

uint32_t NAO_INICIALIZADO = std::numeric_limits<uint32_t>::max();

bool eh_solucao(std::tuple<uint32_t, uint32_t, uint32_t>& coordenada) {
    auto it = std::find_if(tapioca.begin(), tapioca.end(), 
        [&](std::tuple<uint32_t, uint32_t, uint32_t>& t) {
        return std::get<0>(t) == std::get<0>(coordenada) && 
               std::get<1>(t) == std::get<1>(coordenada) && 
               std::get<2>(t) == std::get<2>(coordenada);
    });
    if (it != tapioca.end()) {
        return true;
    }
    return false;
}

uint32_t dp_a(int32_t x, int32_t y, uint32_t tempo, uint32_t positivo) {
    if (x < 0 || x > COORD || y < 0 || y > COORD || tempo > TEMPO_MAXIMO) {
        return 0;
    }

    if (dp[x][y][tempo] != NAO_INICIALIZADO) {
        return dp[x][y][tempo];
    }

    int32_t num_solucoes = std::max(
        dp_a(x-1, y, tempo+1,positivo),
        std::max(dp_a(x, y-1, tempo+1,positivo),
        std::max(dp_a(x+1, y, tempo+1,positivo),
            dp_a(x, y+1, tempo+1,positivo))));

    auto tupla = std::make_tuple<uint32_t, uint32_t, uint32_t>((uint32_t)x, (uint32_t)y, (uint32_t)tempo);
    if (eh_solucao(tupla)) {
        if (dp[x][y][tempo] != NAO_INICIALIZADO) {
            if ((uint32_t)(num_solucoes + 1) > dp[x][y][tempo]){
                dp[x][y][tempo] = (uint32_t)num_solucoes + 1;
            }
        } else {
            dp[x][y][tempo]= (uint32_t)num_solucoes + 1;
        }
    } else {
        if (dp[x][y][tempo] == NAO_INICIALIZADO || (uint32_t)num_solucoes > dp[x][y][tempo]) {
            dp[x][y][tempo] = (uint32_t)num_solucoes;
        }
    }
    return dp[x][y][tempo];
}

int main() {
    uint32_t n;
    fscanf(stdin, "%u\n", &n);

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
    for(uint32_t i = 0; i < n; i++) {
        uint32_t x, y, t;
        fscanf(stdin, "%u %u %u\n", &x, &y, &t);
        tapioca[i] = std::make_tuple(x, y, t);
    }

    dp_a(6, 6, 0, 0);

    fprintf(stdout, "%u\n", dp[6][6][0]);

    return 0;
}
