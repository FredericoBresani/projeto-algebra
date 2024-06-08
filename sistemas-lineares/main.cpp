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

Ax = b

PA = LU


*/


int main() {
    int n_empresas, aux_empresas = 0;
    bool conditionMet = false;
    scanf("%i", &n_empresas);
    std::vector<std::vector<float>> P(n_empresas);
    std::vector<std::vector<float>> A;
    std::vector<std::vector<float>> L;
    std::vector<std::vector<float>> U;
    std::vector<std::vector<float>> PA;
    while (aux_empresas < n_empresas) {
        float percentage;
        std::vector<float> line;
        for (int i = 0; i < n_empresas; i++) {
            scanf("%f", &percentage);
            line.push_back(percentage);
            if (i == aux_empresas) {
                P[aux_empresas].push_back(1);
            } else {
                P[aux_empresas].push_back(0);
            }
        }
        A.push_back(line);
        aux_empresas++;
    }
    // calculate expenses and subtract from the incomes
    for (int i = 0; i < A.size(); i++) {
        if (A[i][i] == 0) {
            for (int j = 0; j < A.size(); j++) {
                if (A[j][i] != 0 && A[i][j] != 0) {
                    std::vector<float> temp = P[j];
                    P[j] = P[i];
                    P[i] = temp;
                }
            }
        }
    }
    for (int i = 0; i < P.size(); i++) {
        std::vector<float> line;
        float value;
        for (int t = 0; t < P.size(); t++) {
            value = 0;
            for (int j = 0; j < P.size(); j++) {
                value = value + P[i][j]*A[j][t];
            }
            line.push_back(value);
        }
        U.push_back(line);
    }
    for (int i = 0; i < P.size(); i++) {
        std::vector<float> line;
        for (int j = 0; j < P.size(); j++) {
            if (i == j) {
                line.push_back(1);
            } else {
                line.push_back(0);
            }
        }
        L.push_back(line);
    }
    PA = U;
    for (int i = 0; i < U.size(); i++) {
        if (U[i][i] != 0) { // a(esxalon_PA[i][i]) + b = 0 -> a = -b/(esxalon_PA[i][i]);
            for (int j = i; j < U.size(); j++) {
                if (j != i) {
                    std::vector<float> temp;
                    for (int t = 0; t < U[i].size(); t++) {
                        temp.push_back(U[j][t] + U[i][t]*(-U[j][i]/U[i][i]));
                    }
                    U[j] = temp;
                }
            }
        }
    }
    for (int i = 0; i < U.size(); i++) {
        std::vector<float> line(U.size());
        for (int t = 0; t < U.size(); t++) {
            if (t < i) {
                if (PA[i][t] != 0) {
                    float x = (PA[i][t] - line[t])/U[t][i];
                    line[t] = x;
                    for (int j = t + 1; j < line.size(); j++) {
                        line[j] = line[j] + U[t][j]*x;
                    }
                } else {
                    line[t] = 0;
                }
            } else if (t == i) {
                line[t] = 1;
            } else {
                line[t] = 0;
            }
        }
        L[i] = line;
    }
    for (int i = 0; i < P.size(); i++) {
        std::cout << "| ";
        for (int j = 0; j < P[i].size(); j++) {
            std::cout << P[i][j] << " ";
        }
        std::cout << "| | ";
        for (int j = 0; j < A[i].size(); j++) {
            std::cout << A[i][j] << " ";
        }

        if (i == P.size()/2) {
            std::cout << "| = | ";
        } else {
            std::cout << "|   | ";
        }
        
        for (int j = 0; j < L.size(); j++) {
            std::cout << L[i][j] << " ";
        }
        std::cout << "| | ";
        for (int j = 0; j < U.size(); j++) {
            std::cout << U[i][j] << " ";
        }
        std::cout << "|\n";
    }
    return 0;
}