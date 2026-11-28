#pragma once

#include <string>
using namespace std;

enum TipoAlternativa {
    ALT_IMPOSSIVEL,
    ALT_DISTRATOR,
    ALT_CORRETA
};

struct Alternativas {
    string texto;
    TipoAlternativa gabarito;
};

struct Questao {
    string enunciado;
    Alternativas alternativas[5];
    double dificuldade;
};

int alternativaCorreta(const Questao& q);
bool acertou(const Questao& q, int marcada);
