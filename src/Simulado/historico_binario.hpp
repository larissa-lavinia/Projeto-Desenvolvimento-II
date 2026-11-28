#pragma once

#include <string>
#include "tri.hpp"

using namespace std;

// Um registro = uma tentativa. Tamanho fixo, por isso da para ir direto ao registro N.
struct RegistroHistorico {
    char data[20];          // AAAA-MM-DD HH:MM:SS
    int acertos;
    int total;
    double habilidade;
    double notaTRI;
    double notaPonderada;
};

bool salvarHistoricoBinario(const string& caminho, const tri::ResultadoTRI& r, double notaPond);

int contarRegistrosBinario(const string& caminho);

// posicao comeca em 0. Usa seekg para ir direto ao registro, sem ler os anteriores.
bool lerRegistroBinario(const string& caminho, int posicao, RegistroHistorico& reg);

// Quem chama faz delete[]. Retorna NULL se o arquivo nao abrir ou estiver vazio.
RegistroHistorico* lerHistoricoBinario(const string& caminho, int& quantidade);

int mostrarHistoricoBinario(const string& caminho);
