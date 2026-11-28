#include "aplicar_prova.hpp"
#include <iostream>

// Le uma linha inteira do teclado. Devolve false se a entrada acabou (fim de arquivo)
bool lerLinha(string& linha) {
    if (!getline(cin, linha)) return false;
    return true;
}

// Pergunta quantas questoes o aluno quer (1 ate maximo) e repete ate vir um valor valido
// Devolve 0 se a entrada acabar antes de uma resposta valida
int lerQuantidade(int maximo) {
    string linha;

    while (true) {
        cout << "Quantas questoes voce quer no simulado (1 a " << maximo << ")? ";
        if (!lerLinha(linha)) return 0;

        // Aceita so digitos
        bool soDigitos = !linha.empty();
        int quantidade = 0;
        for (size_t i = 0; i < linha.size(); i++) {
            if (linha[i] < '0' || linha[i] > '9') { soDigitos = false; break; }
            if (quantidade < 100000) quantidade = quantidade * 10 + (linha[i] - '0');
        }

        if (soDigitos && quantidade >= 1 && quantidade <= maximo) return quantidade;
        cout << "Valor invalido. Digite um numero entre 1 e " << maximo << "." << endl;
    }
}

// Mostra o numero da questao, o enunciado e as alternativas A a E
void mostrarQuestao(const Questao& q, int numero, int total) {
    cout << "\nQuestao " << numero << " de " << total << endl;
    cout << q.enunciado << endl;
    for (int i = 0; i < 5; i++) {
        // char('A' + i) transforma 0..4 em A..E
        cout << "  " << char('A' + i) << ") " << q.alternativas[i].texto << endl;
    }
}

// Le a resposta e devolve 0 a 4 (A a E) ou -1 se ficar em branco
// Maiusculas e minusculas valem; espacos antes da letra sao ignorados
int lerResposta() {
    string linha;
    cout << "Sua resposta (A-E, outra tecla = em branco): ";
    if (!lerLinha(linha)) return -1;

    for (size_t i = 0; i < linha.size(); i++) {
        char letra = linha[i];
        // Pula espacos, tabs e '\r' ate achar o primeiro caractere de verdade
        if (letra == ' ' || letra == '\t' || letra == '\r') continue;

        // Primeiro caractere: se for a-e vira maiuscula; se for A-E vale como resposta
        if (letra >= 'a' && letra <= 'e') letra = letra - 'a' + 'A';
        if (letra >= 'A' && letra <= 'E') return letra - 'A';
        // Qualquer outro caractere = em branco
        return -1;
    }
    return -1;
}

// Aplica a prova: mostra cada questao, le a resposta e guarda em respostas[i]
void aplicarSimulado(const Questao simulado[], int n, int respostas[]) {
    for (int i = 0; i < n; i++) {
        mostrarQuestao(simulado[i], i + 1, n);
        respostas[i] = lerResposta();
    }
}
