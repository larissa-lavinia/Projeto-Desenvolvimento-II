#include "tri.hpp"
#include <cmath>

namespace tri {

double probabAcerto(double habilidade, const ParamQuestao& questao) {

    // Curva logistica: cresce de 0 a 1 conforme a habilidade passa da dificuldade
    double parteVariavel = 1.0 / (1.0 + exp(-questao.discriminacao * (habilidade - questao.dificuldade)));

    // O chute garante um : mesmo quem nao sabe nada acerta com probabilidade 'chute'
    return questao.chute + (1.0 - questao.chute) * parteVariavel;
}

// Mede o quanto uma habilidade "explica" o gabarito do aluno
// Quanto maior o valor, mais essa habilidade combina com os acertos e erros que ele teve
double calcularCombinacao(double habilidade, const ParamQuestao questoes[], const bool acertou[], int totalQuestoes) {
    double combinacao = 0.0;

    for (int i = 0; i < totalQuestoes; i++) {

        double probabilidade = probabAcerto(habilidade, questoes[i]);

        if (probabilidade < 0.000001) probabilidade = 0.000001;
        if (probabilidade > 0.999999) probabilidade = 0.999999;

        if (acertou[i]) {

            // Acertou: soma o log da chance de acertar.
            combinacao += log(probabilidade);
        } else {

            // Errou (ou deixou em branco): soma o log da chance de errar.
            combinacao += log(1.0 - probabilidade);
        }
    }
    return combinacao;
}

// Estima a habilidade do aluno testando valores de -4.00 a +4.00=
// e ficando com o que melhor combina com o resultado dele
double estimarHabilidade(const ParamQuestao questoes[], const bool acertou[], int totalQuestoes) {

    // Sem questoes nao ha o que estimar: habilidade neutra
    if (totalQuestoes <= 0) return 0.0;

    double melhorHabilidade = 0.0;
    double melhorCombinacao = -999999999.0;

    // O passo e inteiro (-400 a 400) e dividido por 100 para evitar erro de soma de decimais.
    for (int passo = -400; passo <= 400; passo++) {
        double habilidadeTestada = passo / 100.0;
        double combinacao = calcularCombinacao(habilidadeTestada, questoes, acertou, totalQuestoes);

        if (combinacao > melhorCombinacao) {
            melhorCombinacao = combinacao;
            melhorHabilidade = habilidadeTestada;
        }
    }
    return melhorHabilidade;
}

// Converte a habilidade para a escala da nota: media 500 e desvio 100 (limites 100 a 900)
double habilidadeParaNota(double habilidade) {
    return 500.0 + 100.0 * habilidade;
}

// Conta os acertos, estima a habilidade e devolve tudo junto com a nota TRI
ResultadoTRI calcularNota(const ParamQuestao questoes[], const bool acertou[], int totalQuestoes) {
    ResultadoTRI resultado;
    resultado.total = totalQuestoes;
    resultado.acertos = 0;

    for (int i = 0; i < totalQuestoes; i++) {
        if (acertou[i]) resultado.acertos++;
    }

    resultado.habilidade = estimarHabilidade(questoes, acertou, totalQuestoes);
    resultado.nota = habilidadeParaNota(resultado.habilidade);
    return resultado;
}

// Nota simples de comparacao (0 a 1000): cada questao vale 1 + dificuldade
// entao acertar questoes dificeis vale mais
double notaPonderada(const ParamQuestao questoes[], const bool acertou[], int totalQuestoes) {
    double somaAcertos = 0.0;
    double somaTotal = 0.0;

    for (int i = 0; i < totalQuestoes; i++) {
        // O peso nunca fica abaixo de 0.1, para questoes muito faceis nao valerem zero ou negativo.
        double peso = 1.0 + questoes[i].dificuldade;
        if (peso < 0.1) peso = 0.1;

        somaTotal += peso;
        if (acertou[i]) somaAcertos += peso;
    }

    if (somaTotal == 0.0) return 0.0;
    return (somaAcertos / somaTotal) * 1000.0;
}

// Converte o percentual de acerto da turma (0 a 1) em dificuldade da TRI
// Muita gente acertando = questao facil = dificuldade negativa
double dificuldadePorPercentual(double percentualAcerto) {
    double p = percentualAcerto;
    // Limita entre 2% e 98% para a conta nao estourar em 0% ou 100%.
    if (p < 0.02) p = 0.02;
    if (p > 0.98) p = 0.98;
    return -log(p / (1.0 - p));
}

// Parametros usados quando a questao so informa a dificuldade:
// discriminacao 1.0 e chute 0.2 (1 chance em 5 alternativas).
ParamQuestao paramPadrao(double dificuldade) {
    ParamQuestao p;
    p.discriminacao = 1.0;
    p.dificuldade = dificuldade;
    p.chute = 0.2;
    return p;
}

}
