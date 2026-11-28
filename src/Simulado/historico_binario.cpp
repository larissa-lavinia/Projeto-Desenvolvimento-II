#include "historico_binario.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "salvar_resultados.hpp"

// Acrescenta um registro no fim do arquivo binario
bool salvarHistoricoBinario(const string& caminho, const tri::ResultadoTRI& r, double notaPond) {
    ofstream arq(caminho.c_str(), ios::binary | ios::app);
    if (!arq.is_open()) return false;

    RegistroHistorico reg;
    memset(&reg, 0, sizeof(reg));                       // zera tudo (inclusive o preenchimento)
    strncpy(reg.data, dataHoraAgora().c_str(), sizeof(reg.data) - 1);
    reg.acertos = r.acertos;
    reg.total = r.total;
    reg.habilidade = r.habilidade;
    reg.notaTRI = r.nota;
    reg.notaPonderada = notaPond;

    arq.write(reinterpret_cast<const char*>(&reg), sizeof(reg));
    arq.close();
    return true;
}

// Tamanho do arquivo dividido pelo tamanho de um registro
int contarRegistrosBinario(const string& caminho) {
    ifstream arq(caminho.c_str(), ios::binary);
    if (!arq.is_open()) return 0;
    arq.seekg(0, ios::end);
    return (int)(arq.tellg() / sizeof(RegistroHistorico));
}

bool lerRegistroBinario(const string& caminho, int posicao, RegistroHistorico& reg) {
    if (posicao < 0) return false;
    ifstream arq(caminho.c_str(), ios::binary);
    if (!arq.is_open()) return false;

    arq.seekg((streamoff)posicao * sizeof(RegistroHistorico), ios::beg);
    arq.read(reinterpret_cast<char*>(&reg), sizeof(reg));
    return arq.gcount() == (streamsize)sizeof(reg);
}

RegistroHistorico* lerHistoricoBinario(const string& caminho, int& quantidade) {
    quantidade = contarRegistrosBinario(caminho);
    if (quantidade <= 0) { quantidade = 0; return NULL; }

    ifstream arq(caminho.c_str(), ios::binary);
    if (!arq.is_open()) { quantidade = 0; return NULL; }

    RegistroHistorico* registros = new RegistroHistorico[quantidade];
    arq.read(reinterpret_cast<char*>(registros), quantidade * sizeof(RegistroHistorico));
    return registros;
}

// Imprime o historico e devolve quantos registros mostrou
int mostrarHistoricoBinario(const string& caminho) {
    int n = 0;
    RegistroHistorico* h = lerHistoricoBinario(caminho, n);
    if (h == NULL) {
        cout << "Historico binario vazio." << endl;
        return 0;
    }
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ") " << h[i].data << " | " << h[i].acertos << "/" << h[i].total
             << " | habilidade " << h[i].habilidade << " | nota TRI " << h[i].notaTRI
             << " | ponderada " << h[i].notaPonderada << endl;
    }
    delete[] h;
    return n;
}
