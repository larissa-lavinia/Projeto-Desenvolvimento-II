#include "salvar_resultados.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

// Data e hora atuais no formato AAAA-MM-DD HH:MM:SS
string dataHoraAgora() {
    time_t agora = time(0);
    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&agora));
    return string(buffer);
}

// Converte a marcacao (0 a 4) na letra A a E; qualquer outro valor vira "NENHUMA"
string letraDaMarcacao(int marcada) {
    if (marcada < 0 || marcada > 4) return "NENHUMA";
    return string(1, char('A' + marcada));
}

// Nome do tipo da alternativa
string nomeDoTipo(TipoAlternativa tipo) {
    if (tipo == ALT_CORRETA) return "CORRETA";
    if (tipo == ALT_DISTRATOR) return "DISTRATOR";
    return "IMPOSSIVEL";
}

// Grava o gabarito do simulado no arquivo e sobrescreve o anterior
// Para cada questao, as alternativas, a marcada, a correta e o resultado.
// O formato e o mesmo do questoes.txt, entao o gabarito pode ser lido pelo mesmo parser
bool salvarGabarito(const string& caminho, const Questao simulado[], const int respostas[],
                    const bool acertos[], int n, const tri::ResultadoTRI& r, double notaPond) {
    ofstream arq(caminho.c_str());
    if (!arq.is_open()) return false;

    // Numeros sempre com 2 casas decimais.
    arq << fixed << setprecision(2);

    arq << "# Gabarito gerado automaticamente pelo simulado. Nao edite." << endl;
    arq << "#SIMULADO" << endl;
    arq << "DATA: " << dataHoraAgora() << endl;
    arq << "TOTAL: " << r.total << endl;
    arq << "ACERTOS: " << r.acertos << endl;
    arq << "HABILIDADE: " << r.habilidade << endl;
    arq << "NOTA_TRI: " << r.nota << endl;
    arq << "NOTA_PONDERADA: " << notaPond << endl;

    // Um bloco por questao.
    for (int i = 0; i < n; i++) {
        arq << "#QUESTAO" << endl;
        arq << "NUMERO: " << i + 1 << endl;
        arq << "ENUNCIADO: " << simulado[i].enunciado << endl;
        for (int a = 0; a < 5; a++) {
            arq << char('A' + a) << ") " << simulado[i].alternativas[a].texto
                << " | " << nomeDoTipo(simulado[i].alternativas[a].gabarito) << endl;
        }
        arq << "DIFICULDADE: " << simulado[i].dificuldade << endl;
        arq << "MARCADA: " << letraDaMarcacao(respostas[i]) << endl;
        arq << "CORRETA: " << letraDaMarcacao(alternativaCorreta(simulado[i])) << endl;
        if (respostas[i] < 0 || respostas[i] > 4) arq << "RESULTADO: BRANCO" << endl;
        else arq << "RESULTADO: " << (acertos[i] ? "ACERTOU" : "ERROU") << endl;
        arq << "#FIM" << endl;
    }

    arq << "#FIMSIMULADO" << endl;
    arq.close();
    return true;
}

// Acrescenta uma linha no fim do historico com data;acertos;total;habilidade;nota TRI;nota ponderada.
bool salvarHistorico(const string& caminho, const tri::ResultadoTRI& r, double notaPond) {
    ofstream arq(caminho.c_str(), ios::app);
    if (!arq.is_open()) return false;

    arq << fixed << setprecision(2);
    arq << dataHoraAgora() << ";" << r.acertos << ";" << r.total << ";"
        << r.habilidade << ";" << r.nota << ";" << notaPond << endl;
    arq.close();
    return true;
}

// Devolve as linhas do historico num vetor alocado, sem imprimir nada
// quantidade recebe quantas linhas foram lidas (linhas vazias sao puladas)
// Quem chama faz delete[]. Retorna NULL se o arquivo nao abrir ou estiver vazio
string* lerLinhasHistorico(const string& caminho, int& quantidade) {
    quantidade = 0;

    ifstream arq(caminho.c_str());
    if (!arq.is_open()) return NULL;

    // Conta as linhas nao vazias para saber o tamanho do vetor
    string linha;
    int total = 0;
    while (getline(arq, linha)) {
        if (linha != "") total++;
    }
    if (total == 0) return NULL;

    // Volta ao inicio do arquivo para ler de novo e guardar as linhas
    arq.clear();
    arq.seekg(0);
    string* linhas = new string[total];
    while (getline(arq, linha) && quantidade < total) {
        if (linha == "") continue;
        linhas[quantidade] = linha;
        quantidade++;
    }
    return linhas;
}

// Imprime as tentativas anteriores e devolve quantas existem
int mostrarHistorico(const string& caminho) {
    int quantidade = 0;
    string* linhas = lerLinhasHistorico(caminho, quantidade);
    if (linhas == NULL) return 0;

    for (int i = 0; i < quantidade; i++) {
        cout << i + 1 << ") " << linhas[i] << endl;
    }
    delete[] linhas;
    return quantidade;
}

// Le de volta as respostas marcadas em um gabarito salvo
int* lerMarcadasDoGabarito(const string& caminho, int& quantidade) {
    quantidade = 0;

    ifstream arq(caminho.c_str());
    if (!arq.is_open()) return NULL;

    string linha;
    int total = 0;
    while (getline(arq, linha)) {
        if (linha == "#QUESTAO") total++;
    }
    if (total == 0) return NULL;

    // Volta ao inicio do arquivo para ler de novo e aguarda as marcacoes
    arq.clear();
    arq.seekg(0);
    int* marcadas = new int[total];
    while (getline(arq, linha) && quantidade < total) {
        if (linha.compare(0, 9, "MARCADA: ") == 0) {
            char letra = (linha.size() > 9) ? linha[9] : 'N';
            if (letra >= 'A' && letra <= 'E') marcadas[quantidade] = letra - 'A';
            else marcadas[quantidade] = -1;
            quantidade++;
        }
    }
    return marcadas;
}
