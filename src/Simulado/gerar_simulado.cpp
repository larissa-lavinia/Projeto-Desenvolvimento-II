#include "gerar_simulado.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "tri.hpp"

// Tira espacos, tabs e \r do comeco e do fim do texto
string aparar(const string& texto) {
    size_t inicio = 0;
    size_t fim = texto.size();

    while (inicio < fim && (texto[inicio] == ' ' || texto[inicio] == '\t' || texto[inicio] == '\r')) inicio++;
    while (fim > inicio && (texto[fim - 1] == ' ' || texto[fim - 1] == '\t' || texto[fim - 1] == '\r')) fim--;

    return texto.substr(inicio, fim - inicio);
}

// Diz se o texto comeca exatamente como deveria
bool comecaCom(const string& texto, const string& prefixo) {
    return texto.compare(0, prefixo.size(), prefixo) == 0;
}

// Conta quantas questoes o arquivo tem para saber qual o tamanho do vetor
// Retorna -1 se nao conseguir abrir o arquivo
int contarQuestoes(const string& caminho) {
    ifstream arq(caminho.c_str());
    if (!arq.is_open()) return -1;

    string linha;
    int total = 0;
    while (getline(arq, linha)) {
        if (aparar(linha) == "#QUESTAO") total++;
    }
    return total;
}

// Le o arquivo de questoes e retorna um vetor alocado
// Recebe quantas questoes validas foram carregadas
// Questoes com erro sao ignoradas
Questao* carregarQuestoes(const string& caminho, int& quantidade, bool avisos) {
    quantidade = 0;

    // Conta as questoes para alocar o vetor com o tamanho certo
    int total = contarQuestoes(caminho);
    if (total <= 0) return NULL;

    Questao* banco = new Questao[total];

    ifstream arq(caminho.c_str());
    if (!arq.is_open()) {
        delete[] banco;
        return NULL;
    }

    string linha;
    Questao q;          // questao que esta sendo montada
    bool lendo = false;  // true entre #QUESTAO e #FIM
    bool erro = false;   // true se alguma linha da questao atual estiver mal formatada
    bool vista[5];       // quais alternativas (A a E) apareceram na questao atual
    int numeroNoArquivo = 0;

    while (getline(arq, linha)) {
        linha = aparar(linha);

        // Zera tudo para ler a proxima questao
        if (linha == "#QUESTAO") {
            lendo = true;
            erro = false;
            numeroNoArquivo++;

            q.enunciado = "";
            q.dificuldade = 0.0;
            for (int i = 0; i < 5; i++) {
                q.alternativas[i].texto = "";
                q.alternativas[i].gabarito = ALT_IMPOSSIVEL;
                vista[i] = false;
            }
        }

        // valida a questão e, se estiver certa, guarda no banco
        else if (linha == "#FIM") {
            if (lendo) {
                int corretas = 0;
                int faltando = 0;
                for (int i = 0; i < 5; i++) {
                    if (!vista[i]) faltando++;
                    if (q.alternativas[i].gabarito == ALT_CORRETA) corretas++;
                }

                if (erro) {
                    if (avisos) cout << "Aviso: questao " << numeroNoArquivo << " do arquivo ignorada (linha mal formatada)." << endl;
                } else if (q.enunciado == "") {
                    if (avisos) cout << "Aviso: questao " << numeroNoArquivo << " do arquivo ignorada (sem enunciado)." << endl;
                } else if (faltando > 0) {
                    if (avisos) cout << "Aviso: questao " << numeroNoArquivo << " do arquivo ignorada (precisa das 5 alternativas A a E)." << endl;
                } else if (corretas != 1) {
                    if (avisos) cout << "Aviso: questao " << numeroNoArquivo << " do arquivo ignorada (precisa de exatamente 1 CORRETA)." << endl;
                } else {
                    banco[quantidade] = q;
                    quantidade++;
                }
            }
            lendo = false;
        }

        else if (lendo) {
            if (comecaCom(linha, "ENUNCIADO:")) {
                q.enunciado = aparar(linha.substr(10));
            }
            else if (comecaCom(linha, "TEXTO:")) {
                q.enunciado = aparar(linha.substr(6));
            }
            else if (comecaCom(linha, "DIFICULDADE:")) {
                q.dificuldade = atof(aparar(linha.substr(12)).c_str());
            }
            else if (comecaCom(linha, "PERCENTUAL:")) {
                q.dificuldade = tri::dificuldadePorPercentual(atof(aparar(linha.substr(11)).c_str()));
            }
            else if (linha.size() >= 2 && linha[1] == ')' && linha[0] >= 'A' && linha[0] <= 'E') {
                int indice = linha[0] - 'A';
                string resto = aparar(linha.substr(2));
                size_t barra = resto.rfind('|');

                if (barra == string::npos) {
                    erro = true;
                } else {
                    q.alternativas[indice].texto = aparar(resto.substr(0, barra));
                    string tipo = aparar(resto.substr(barra + 1));

                    if (tipo == "CORRETA") q.alternativas[indice].gabarito = ALT_CORRETA;
                    else if (tipo == "DISTRATOR") q.alternativas[indice].gabarito = ALT_DISTRATOR;
                    else if (tipo == "IMPOSSIVEL") q.alternativas[indice].gabarito = ALT_IMPOSSIVEL;
                    else erro = true;

                    vista[indice] = true;
                }
            }
        }

    }

    if (quantidade == 0) {
        delete[] banco;
        return NULL;
    }
    return banco;
}

// Sorteia quantas questoes e retorna num novo vetor
// Se pedir mais do que o banco tem, usa o total do banco
// Devolve NULL se banco ou quantidade forem menores ou iguais a zero
Questao* criarSimulado(const Questao banco[], int totalBanco, int quantidade) {
    if (totalBanco <= 0 || quantidade <= 0) return NULL;
    if (quantidade > totalBanco) quantidade = totalBanco;

    int* indices = new int[totalBanco];
    for (int i = 0; i < totalBanco; i++) indices[i] = i;

    // Embaralha os indices
    for (int i = totalBanco - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Copia as questoes sorteadas
    Questao* simulado = new Questao[quantidade];
    for (int i = 0; i < quantidade; i++) {
        simulado[i] = banco[indices[i]];
    }

    delete[] indices;
    return simulado;
}
