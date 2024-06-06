#include <iostream>
#include <vector>

/* 
 Empresa   |                                             Cada linha representa as comrpras de um empresa
 Compradora|_Empresa_1 |_Empresa_2_|__...__|_Empresa_k_| Onde cada pi representa o custo de 1 unidade da produção da empresa i
 Empresa 1 |___1.0p1___|___7.2p2___|__...__|___9.3pk___| 
 Empresa 2 |___2.1p1___|___2.0p2___|__...__|___3.3pk___|
    .      |     .           .         .         .     |
    .      |     .           .         .         .     |
    .      |_____.___________._________._________._____|
 Empresa k |___6.3p1___|___1.4p2___|__...__|___5.0pk___|



 Uma empresa gasta a soma dos valores na sua linha:

 0.0p1 + 7.2p2 + ... + 9.3pk = Gasto da empresa 1

 Uma empresa ganha a soma da sula colina:

 0.0p1 + 2.1p1 + ... + 6.3p1

 Para resolver o problema precisamos igualar a soma de cada a linha a soma da sua respectiva coluna,
 criando o seguinte sistema

 1.0p1 + 7.2p2 + ... + 9.3pk = 1.0p1 + 2.1p1 + ... + 6.3p1
 2.1p1 + 2.0p2 + ... + 3.3pk = 7.2p2 + 2.0p2 + ... + 1.4p2
                  .                             . 
                  .                             .
                  .                             .
 6.3p1 + 1.4p2 + ... + 5.0pk = 9.3pk + 3.3pk + ... + 5.0pk

 Que pode ser traduzido no seguinte sistema matricial:
 _                   _   _  _     _                         _
| 1.0   7.2  ...  9.3 | | p1 |   | (1.0 + 2.1 + ... + 6.3)p1 |
| 2.1   2.0  ...  3.3 | | p2 |   | (7.2 + 2.0 + ... + 1.4)p2 |
|  .          .       | | .  |   |               .           | 
|        .    .       | | .  | = |               .           |
|             .       | | .  |   |               .           |
| 6.3   1.4  ...  5.0 | | pk |   | (9.3 + 3.3 + ... + 5.0)pk |
--                  --   -  -     --                       --

subtraindo o lado direito dos dois lados, temos:
 _                                                                                                          _   _  _     _  
| (1.0 - (1.0 + 2.1 + ... + 6.3))                  7.2                ...              9.3                   | | p1 |   | 0 |
|               2.1                  (2.0 - (7.2 + 2.0 + ... + 1.4))  ...              3.3                   | | p2 |   | 0 |
|                                                                      .                                     | | .  |   | . |
|                                                                      .                                     | | .  | = | . |
|                                                                      .                                     | | .  |   | . |
|               6.3                                1.4                ...   (5.0 - (9.3 + 3.3 + ... + 5.0))  | | pk |   | 0 |
--                                                                                                         --   -  -     --  


*/


int main() {
    int n_empresas, aux_empresas = 0;
    std::vector<std::vector<float>> matrix;
    scanf("%i", &n_empresas);
    while (aux_empresas < n_empresas) {
        float percentage;
        std::vector<float> line;
        for (int i = 0; i < n_empresas; i++) {
            scanf("%f", &percentage);
            line.push_back(percentage);
        }
        matrix.push_back(line);
        aux_empresas++;
    }
    for (auto line : matrix) {
        for (auto n : line) {
            std::cout << n << " ";
        }
        std::cout << "\n";
    }
    return 0;
}