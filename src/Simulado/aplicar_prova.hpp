#pragma once

#include <string>
#include "struct.hpp"

bool lerLinha(string& linha);

int lerQuantidade(int maximo);

void mostrarQuestao(const Questao& q, int numero, int total);

int lerResposta();

void aplicarSimulado(const Questao simulado[], int n, int respostas[]);
