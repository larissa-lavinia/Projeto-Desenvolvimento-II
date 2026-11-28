#include "struct.hpp"

// Devolve de (0 a 4) da alternativa marcada como CORRETA na questao
// Se nenhuma alternativa for correta, devolve -1.
int alternativaCorreta(const Questao& q) {
    for (int i = 0; i < 5; i++) {
        if (q.alternativas[i].gabarito == ALT_CORRETA) return i;
    }
    return -1;
}

// Passa se a resposta está correta
bool acertou(const Questao& q, int marcada) {

    // Em branco ou fora de A-E nunca conta como acerto.
    if (marcada < 0 || marcada > 4) return false;

    // So acerta se a alternativa marcada for a do tipo CORRETA.
    return q.alternativas[marcada].gabarito == ALT_CORRETA;
}
