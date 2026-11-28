#pragma once

#include <cmath>

using namespace std;

namespace tri {

struct ParamQuestao {
    double discriminacao;
    double dificuldade;
    double chute;
};

struct ResultadoTRI {
    double habilidade;
    double nota;
    int acertos;
    int total;
};

double probabAcerto(double habilidade, const ParamQuestao& questao);
double calcularCombinacao(double habilidade, const ParamQuestao questoes[], const bool acertou[], int totalQuestoes);
double estimarHabilidade(const ParamQuestao questoes[], const bool acertou[], int totalQuestoes);
double habilidadeParaNota(double habilidade);
ResultadoTRI calcularNota(const ParamQuestao questoes[], const bool acertou[], int totalQuestoes);
double notaPonderada(const ParamQuestao questoes[], const bool acertou[], int totalQuestoes);
double dificuldadePorPercentual(double percentualAcerto);
ParamQuestao paramPadrao(double dificuldade);

}
