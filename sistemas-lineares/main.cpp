#include <iostream>
#include <vector>
#include <string>

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

bool isNumber(char c) {
    return (c == '0' || c == '1' ||c == '2' ||c == '3' ||c == '4' ||c == '5' ||c == '6' ||c == '7' ||c == '8' || c == '9' || c == '.');
}

class Tuple {
    public:
        char c;
        int index;
        Tuple(char cc, int i): c(cc), index(i) {}
};


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
                P[aux_empresas].push_back(1.0);
            } else {
                P[aux_empresas].push_back(0.0);
            }
        }
        A.push_back(line);
        aux_empresas++;
    }
    // calculate expenses and subtract from the incomes
    for (int i = 0; i < A.size(); i++) {
        float gain = 0.0;
        for (int t = 0; t < A.size(); t++) {
            gain += A[t][i];
        }
        A[i][i] = A[i][i] - gain;
    }
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            A[i][j] = -A[i][j];
        }
    }
    for (int i = 0; i < A.size(); i++) {
        if (A[i][i] == 0.0) {
            for (int j = 0; j < A.size(); j++) {
                if (A[j][i] != 0.0 && A[i][j] != 0.0) {
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
            value = 0.0;
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
                line.push_back(1.0);
            } else {
                line.push_back(0.0);
            }
        }
        L.push_back(line);
    }
    PA = U;
    for (int i = 0; i < U.size(); i++) {
        if (U[i][i] != 0.0) { // a(esxalon_PA[i][i]) + b = 0 -> a = -b/(esxalon_PA[i][i]);
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
                if (PA[i][t] != 0.0) {
                    float x = (PA[i][t] - line[t])/U[t][t];
                    line[t] = x;
                    for (int j = t + 1; j < line.size(); j++) {
                        line[j] = line[j] + U[t][j]*x;
                    }
                } else {
                    line[t] = 0.0;
                }
            } else if (t == i) {
                line[t] = 1.0;
            } else {
                line[t] = 0.0;
            }
        }
        L[i] = line;
    }
    for (int i = 0; i < P.size(); i++) {
        std::cout << "| ";
        for (int j = 0; j < P[i].size(); j++) {
            printf("%.1f ", P[i][j]);
        }
        std::cout << "| | ";
        for (int j = 0; j < A[i].size(); j++) {
            printf("%.1f ", A[i][j]);
        }

        if (i == P.size()/2) {
            std::cout << "| = | ";
        } else {
            std::cout << "|   | ";
        }
        
        for (int j = 0; j < L.size(); j++) {
            printf("%.1f ", L[i][j]);
        }
        std::cout << "| | ";
        for (int j = 0; j < U.size(); j++) {
            printf("%.1f ", U[i][j]);
        }
        std::cout << "|\n";
    }
    
    /*
    for (int i = U.size() - 1; i >= 0; i--) {
        bool lineOfZeros = true;
        bool lineDependsOnVariable = false;
        for (int j = 0; j < U.size(); j++) {
            if (U[i][j] != 0) {
                lineOfZeros = false;
                for (int t = 0; t < solution.size(); t++) {
                    
                }
            }
        }
        if (lineOfZeros) {
           
        }
    }
    */
    std::vector<std::string> solutions(n_empresas);
    std::vector<std::string> variables(n_empresas);
    for (int i = U.size() - 1; i >= 0; i--) {
        float value;
        solutions[i] = "k"+std::to_string(i)+"=(";
        for (int j = 0; j < U.size(); j++) {
            if (j != i) {
                if (U[i][j] != 0) {
                    solutions[i] = solutions[i] + std::to_string(-U[i][j]) + "*k" + std::to_string(j) + "+";
                } 
            }
        }
        solutions[i] = solutions[i] + ")/" + std::to_string(U[i][i]);
    }
    for (int i = solutions.size() - 1; i >= 0; i--) {
        int variableIndex = -1;
        int peek = 1;
        int firstParentheses = 0;
        for (int j = 1; j < solutions[i].length(); j++) {
            while (isNumber(solutions[i].at(peek))) {
                peek++;
            }
            if (peek != j) {
                std::string n = solutions[i].substr(j, peek - 1);
                variableIndex = std::stoi(n);
                j = peek;
            }

            while (solutions[i].at(peek) != '(') {
                firstParentheses = j;
                peek++;
            } 
            peek++;
            j = peek;
            bool insideBracket = solutions[i].at(peek) != ')';

            while (solutions[i].at(peek) != '/') {
                peek++;
            }
            peek++;
            j = peek;

            while (isNumber(solutions[i].at(peek)) && peek < solutions[i].size() - 1) {
                peek++;
            }

            if (j != peek) {
                std::string n = solutions[i].substr(j, peek);
                float devisor = std::stof(n);
                j = peek;
                if (devisor == 0) {
                    if (insideBracket) {
                        variables[variableIndex] = "nosolution";
                    } else {
                        if (variableIndex == solutions.size() / 2) {
                            variables[variableIndex] = "|k"+std::to_string(variableIndex)+"| = | " + "variable |";
                        } else {
                            variables[variableIndex] = "|k"+std::to_string(variableIndex)+"|   | " + "variable |";
                        }
                        
                    }
                } else {
                    if (variableIndex == solutions.size() / 2) {
                        variables[variableIndex] = "|k"+std::to_string(variableIndex)+"| = | " + solutions[i].substr(firstParentheses + 1, solutions[i].size() - 1) + " |";

                    } else {
                        variables[variableIndex] = "|k"+std::to_string(variableIndex)+"|   | " + solutions[i].substr(firstParentheses + 1, solutions[i].size() - 1) + " |";

                    }
                }
            }
        }
    }
    std::cout<< "\n\n\n";
    for (int i = 0; i < variables.size(); i++) {
        std::cout << variables[i] << "\n";
    }
    return 0;
}
// 