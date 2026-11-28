#pragma once

#include <string>
#include "struct.hpp"
#include "tri.hpp"

string dataHoraAgora();
string letraDaMarcacao(int marcada);
string nomeDoTipo(TipoAlternativa tipo);

bool salvarGabarito(const string& caminho, const Questao simulado[], const int respostas[],
                    const bool acertos[], int n, const tri::ResultadoTRI& r, double notaPond);

bool salvarHistorico(const string& caminho, const tri::ResultadoTRI& r, double notaPond);

string* lerLinhasHistorico(const string& caminho, int& quantidade);

int mostrarHistorico(const string& caminho);

int* lerMarcadasDoGabarito(const string& caminho, int& quantidade);
