#pragma once

#include <string>
#include "struct.hpp"

string aparar(const string& texto);

bool comecaCom(const string& texto, const string& prefixo);

int contarQuestoes(const string& caminho);

Questao* carregarQuestoes(const string& caminho, int& quantidade, bool avisos = true);

Questao* criarSimulado(const Questao banco[], int totalBanco, int quantidade);
