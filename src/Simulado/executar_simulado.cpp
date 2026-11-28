#include "executar_simulado.hpp"

#include <iostream>
#include "gerar_simulado.hpp"
#include "aplicar_prova.hpp"
#include "salvar_resultados.hpp"
#include "historico_binario.hpp"

// Confere cada resposta (acertos[i]) e monta os parametros da TRI de cada questao
void corrigirSimulado(const Questao simulado[], const int respostas[], int n,
                      tri::ParamQuestao params[], bool acertos[]) {
    for (int i = 0; i < n; i++) {
        acertos[i] = acertou(simulado[i], respostas[i]);
        params[i] = tri::paramPadrao(simulado[i].dificuldade);
    }
}

// Correcao + nota TRI + nota ponderada de uma vez
ResultadoSimulado avaliarSimulado(const Questao simulado[], const int respostas[], int n, bool acertos[]) {
    tri::ParamQuestao* params = new tri::ParamQuestao[n > 0 ? n : 1];
    corrigirSimulado(simulado, respostas, n, params, acertos);

    ResultadoSimulado r;
    r.resultadoTRI = tri::calcularNota(params, acertos, n);
    r.notaPonderada = tri::notaPonderada(params, acertos, n);

    delete[] params;
    return r;
}

// Mostra o que o aluno marcou em cada questao e as notas finais
void mostrarResultado(const Questao simulado[], const int respostas[], const bool acertos[],
                      int n, const ResultadoSimulado& r) {
    cout << "\n===== RESULTADO =====" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Questao " << i + 1 << ": ";
        if (respostas[i] == -1) cout << "em branco";
        else cout << "marcou " << char('A' + respostas[i]);
        cout << " | correta " << char('A' + alternativaCorreta(simulado[i]))
                  << (acertos[i] ? " | ACERTOU" : " | errou") << endl;
    }

    cout << "\nAcertos: " << r.resultadoTRI.acertos << "/" << r.resultadoTRI.total << endl;
    cout << "Habilidade estimada: " << r.resultadoTRI.habilidade << endl;
    cout << "Nota TRI: " << r.resultadoTRI.nota << endl;
    cout << "Nota ponderada (comparacao): " << r.notaPonderada << endl;
}

// carrega as questoes, pergunta quantas, aplica a prova,
// corrige, mostra o resultado e salva o gabarito e o historico.
int rodarSimulado(const string& arqQuestoes, const string& arqGabarito, const string& arqHistorico,
                  const string& arqBinario) {

    // Carrega o banco de questoes do arquivo
    int totalBanco = 0;
    Questao* banco = carregarQuestoes(arqQuestoes, totalBanco);
    if (banco == NULL) {
        cout << "Nao consegui carregar questoes de \"" << arqQuestoes << "\"." << endl;
        cout << "Confira se o arquivo existe na pasta do programa e se tem questoes validas." << endl;
        return 1;
    }
    cout << totalBanco << " questoes disponiveis no arquivo." << endl;

    // Pergunta quantas questoes o aluno quer
    int n = lerQuantidade(totalBanco);
    if (n <= 0) {
        delete[] banco;
        return 1;
    }

    // Sorteia o simulado
    Questao* simulado = criarSimulado(banco, totalBanco, n);
    delete[] banco;
    if (simulado == NULL) return 1;

    int* respostas = new int[n];
    bool* acertos = new bool[n];

    // Aplica a prova e guarda as respostas
    aplicarSimulado(simulado, n, respostas);

    // Corrige e calcula as notas e depois mostra o resultadp
    ResultadoSimulado r = avaliarSimulado(simulado, respostas, n, acertos);
    mostrarResultado(simulado, respostas, acertos, n, r);

    // Salva o gabarito e o historico, se algum falhar, avisa e devolve 1
    int codigo = 0;
    if (salvarGabarito(arqGabarito, simulado, respostas, acertos, n, r.resultadoTRI, r.notaPonderada)) {
        cout << "\nGabarito salvo em \"" << arqGabarito << "\"." << endl;
    } else {
        cout << "\nErro: nao consegui salvar o gabarito em \"" << arqGabarito << "\"." << endl;
        codigo = 1;
    }
    if (!salvarHistorico(arqHistorico, r.resultadoTRI, r.notaPonderada)) {
        cout << "Erro: nao consegui salvar o historico em \"" << arqHistorico << "\"." << endl;
        codigo = 1;
    }
    if (!salvarHistoricoBinario(arqBinario, r.resultadoTRI, r.notaPonderada)) {
        cout << "Erro: nao consegui salvar o historico binario em \"" << arqBinario << "\"." << endl;
        codigo = 1;
    }

    // Libera a memoria alocada
    delete[] simulado;
    delete[] respostas;
    delete[] acertos;

    return codigo;
}
