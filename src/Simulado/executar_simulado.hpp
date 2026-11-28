#pragma once

#include <string>
#include "struct.hpp"
#include "tri.hpp"

struct ResultadoSimulado {
    tri::ResultadoTRI resultadoTRI;
    double notaPonderada;
};

void corrigirSimulado(const Questao simulado[], const int respostas[], int n,
                      tri::ParamQuestao params[], bool acertos[]);

ResultadoSimulado avaliarSimulado(const Questao simulado[], const int respostas[], int n, bool acertos[]);

void mostrarResultado(const Questao simulado[], const int respostas[], const bool acertos[],
                      int n, const ResultadoSimulado& r);

int rodarSimulado(const string& arqQuestoes, const string& arqGabarito, const string& arqHistorico,
                  const string& arqBinario = "historico.dat");
