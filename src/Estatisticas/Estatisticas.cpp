#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <locale>
#include <conio.h>
#include <windows.h>
#include "Estatisticas.h"
#include <iomanip>
#include <cmath>
using namespace std;

const int TAM_MAX = 58203;
NotaDeCorte notas[TAM_MAX];
NotaDeCorte aux[TAM_MAX];

// Percorre um vetor de origem aplicando o filtro escolhido ("tipo") com o "valor" informado,
// gravando os registros correspondentes no vetor global 'aux' e retornando quantos passaram.

namespace ndc{

void menu(){

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");

    char opc;

    while (opc != 8){

        system("cls");

        cout << "Escolha qual dos dados deseja acessar\n" << endl;

        cout << "1 - Notas de corte de cada universidade e curso" << endl;
        cout << "2 - Estatísticas gerais dos participantes" << endl;
        cout << "Backspace - Sair" << endl;

        opc = getch();

        switch (opc){
        case '1':
            system("cls");
            ndc::ConsultarSisu();
            break;
        case '2':
            system("cls");
            ndc::FiltrosParticipantes();
            break;
        case 8:
            cout << "\nAté outro dia";
            getch();
            break;
        }

    }

}

int FiltrarEmAux(NotaDeCorte origem[], int qtdOrigem, const string &tipo, const string &valor) {
    int novoCont = 0;

    for (int i = 0; i < qtdOrigem && novoCont < TAM_MAX; i++) {
        bool bateu = false;

        if (tipo == "municipio") {
            bateu = (origem[i].Munincipio == valor);
        } else if (tipo == "universidade") {
            bateu = (origem[i].SgIes == valor || origem[i].NoIes == valor);
        } else if (tipo == "campus") {
            bateu = (origem[i].Campus == valor);
        } else if (tipo == "estado") {
            bateu = (origem[i].Estado == valor);
        } else if(tipo == "curso"){
            bateu = (origem[i].NomeCurso == valor);
        } else if(tipo == "modalidade"){
            bateu = (origem[i].TipoConcorrencia == valor);
        }


        if (bateu) {
            aux[novoCont] = origem[i];
            novoCont++;
        }
    }

    return novoCont;
}

// Formata e imprime na tela os principais dados de um único registro de NotaDeCorte.
void ExibirRegistro(const NotaDeCorte &n) {
    cout << "\n--------------------------------------------------------\n"
         << "\n\nEdicao: " << n.edicao
         << " | IES: " << n.SgIes
         << " | Curso: " << n.NomeCurso
         << " | Grau: " << n.grau
         << " | Modalidade: " << n.TipoConcorrencia
         << " | Vagas: " << n.Vagas
         << " | Nota Corte: " << n.NotaCorte << endl
         << "Região: " << n.Regiao
         << " | Estado: " << n.Estado
         << " | Munincipio: " << n.Munincipio
         << " | Campus: " << n.Campus
         << "\n--------------------------------------------------------\n" << endl;
}


void ExibirListaNotasCorte(const NotaDeCorte &n) {
    cout << fixed << setprecision(2);
    cout << "\n========================================================\n";
    cout << "Edicao:     " << n.edicao << endl;
    cout << "IES:        " << n.SgIes << " - " << n.NoIes << endl;
    cout << "Campus:     " << n.Campus << " (" << n.Munincipio << " - " << n.Estado << ")" << endl;
    cout << "Curso:      " << n.NomeCurso << " | Grau: " << n.grau << " | Turno: " << n.turno << endl;
    cout << "Modalidade: " << n.TipoConcorrencia << endl;
    cout << "Vagas:      " << n.Vagas << " | Inscritos: " << n.QtdIncricao << endl;

    if (n.NotaCorte > 0.0f) {
        cout << "Nota Corte: " << n.NotaCorte << endl;
    } else {
        cout << "Nota Corte: Nao informada" << endl;
    }
    cout << "========================================================\n";
}


void ExibirListaNotasCorte(NotaDeCorte lista[], int qtd) {
    if (qtd <= 0) {
        cout << "\nNenhuma nota de corte para exibir.\n";
        return;
    }

    ExibirMedias(lista,qtd);

    for (int i = 0; i < qtd; i++) {
        ExibirListaNotasCorte(lista[i]);
    }
}


// Exibe o menu interativo de filtros e acumula/refina os resultados em 'aux' conforme as escolhas do usuário.
void Filtros(NotaDeCorte notas[], int totalRegistros) {
    char opc;
    int cont = 0;
    bool filtroAtivo = false;
    string entrada;

    do {
        cout << "\nEscolha qual filtro deseja aplicar\n" << endl;
        cout << "1 - Munincipio" << endl;
        cout << "2 - Universidade" << endl;
        cout << "3 - Campus" << endl;
        cout << "4 - Estado" << endl;
        cout << "5 - Curso" << endl;
        cout << "6 - Modalidade" << endl;
        cout << "7 - Exibir com os filtros" << endl;
        cout << "8 - Limpar filtros" << endl;
        cout << "Backspace - Sair" << endl;

        opc = getch();

        switch (opc) {
            case '1': {
                cout << "\nDigite o Munincipio que deseja pesquisar: ";
                getline(cin, entrada);

                entrada[0] = toupper(entrada[0]);

                if (!filtroAtivo) {
                    cont = FiltrarEmAux(notas, totalRegistros, "municipio", entrada);
                    filtroAtivo = true;
                } else {
                    cont = FiltrarEmAux(aux, cont, "municipio", entrada);
                }

                cout << "\n" << cont << " registro(s) encontrado(s) com o filtro aplicado." << endl;
                break;
            }
            case '2': {
                cout << "\nDigite a Universidade (sigla ou nome) que deseja pesquisar: ";
                getline(cin, entrada);

                for(int i = 0; i < sizeof(entrada); i++){
                    entrada[i] = toupper(entrada[i]);
                }

                if (!filtroAtivo) {
                    cont = FiltrarEmAux(notas, totalRegistros, "universidade", entrada);
                    filtroAtivo = true;
                } else {
                    cont = FiltrarEmAux(aux, cont, "universidade", entrada);
                }

                cout << "\n" << cont << " registro(s) encontrado(s) com o filtro aplicado." << endl;
                break;
            }
            case '3': {
                cout << "\nDigite o Campus que deseja pesquisar: ";
                getline(cin, entrada);

                if (!filtroAtivo) {
                    cont = FiltrarEmAux(notas, totalRegistros, "campus", entrada);
                    filtroAtivo = true;
                } else {
                    cont = FiltrarEmAux(aux, cont, "campus", entrada);
                }

                cout << "\n" << cont << " registro(s) encontrado(s) com o filtro aplicado." << endl;
                break;
            }
            case '4': {
                cout << "\nDigite a sigla do Estado que deseja pesquisar: ";
                getline(cin, entrada);

                for(int i = 0; i < sizeof(entrada); i++){
                    entrada[i] = toupper(entrada[i]);
                }

                if (!filtroAtivo) {
                    cont = FiltrarEmAux(notas, totalRegistros, "estado", entrada);
                    filtroAtivo = true;
                } else {
                    cont = FiltrarEmAux(aux, cont, "estado", entrada);
                }

                cout << "\n" << cont << " registro(s) encontrado(s) com o filtro aplicado." << endl;
                break;
            }
            case '5': {
                cout << "\nDigite o Curso que deseja pesquisar: ";
                getline(cin, entrada);

                for(int i = 0; i < sizeof(entrada); i++){
                    entrada[i] = toupper(entrada[i]);
                }

                if (!filtroAtivo) {
                    cont = FiltrarEmAux(notas, totalRegistros, "curso", entrada);
                    filtroAtivo = true;
                } else {
                    cont = FiltrarEmAux(aux, cont, "curso", entrada);
                }

                cout << "\n" << cont << " registro(s) encontrado(s) com o filtro aplicado." << endl;
                break;
            }
            case '6': {
                cout << "\nDigite a Modalidade que deseja pesquisar: ";
                getline(cin, entrada);

                if (!filtroAtivo) {
                    cont = FiltrarEmAux(notas, totalRegistros, "modalidade", entrada);
                    filtroAtivo = true;
                } else {
                    cont = FiltrarEmAux(aux, cont, "modalidade", entrada);
                }

                cout << "\n" << cont << " registro(s) encontrado(s) com o filtro aplicado." << endl;
                break;
            }
        case '7':{
    if (!filtroAtivo || cont == 0) {
        cout << "\nNenhum filtro foi aplicado ainda ou nenhum registro corresponde aos filtros." << endl;
    } else {
        ExibirListaNotasCorte(aux, cont);
    }
    getch();
    break;
            }
            case '8': {
                cont = 0;
                filtroAtivo = false;
                cout << "\nFiltros limpos. O proximo filtro partira de todos os registros." << endl;
                break;
            }
            case 8:
                cout << "\nAcabou essa desgraça";
                break;
        }
    } while (opc != 8);
}


// Lê linha por linha o arquivo CSV delimitado por ';', converte os campos para NotaDeCorte
// e preenche o vetor 'notas', retornando o total de registros carregados.
int CarregarArquivo(ifstream &f, NotaDeCorte notas[]) {
    string linha;
    int cont = 0;

    while (getline(f, linha)) {
        if (linha.empty()) {
            continue;
        }
        if (cont >= TAM_MAX) {
            break;
        }

        stringstream ss(linha);
        string segmento;
        NotaDeCorte N;

        getline(ss, segmento, ';');
        N.edicao = segmento;

        getline(ss, segmento, ';');
        if (!segmento.empty() && isdigit(segmento[0])) {
            N.CoIes = stoi(segmento);
        } else {
            N.CoIes = 0;
        }

        getline(ss, segmento, ';');
        N.NoIes = segmento;

        getline(ss, segmento, ';');
        N.SgIes = segmento;

        getline(ss, segmento, ';');
        N.OrganizacaoAcademica = segmento;

        getline(ss, segmento, ';');
        N.Categoria = segmento;

        getline(ss, segmento, ';');
        N.Campus = segmento;

        getline(ss, segmento, ';');
        N.Munincipio = segmento;

        getline(ss, segmento, ';');
        N.Estado = segmento;

        getline(ss, segmento, ';');
        N.Regiao = segmento;

        getline(ss, segmento, ';');
        if (!segmento.empty() && isdigit(segmento[0])) {
            N.CoIesCurso = stoi(segmento);
        } else {
            N.CoIesCurso = 0;
        }

        getline(ss, segmento, ';');
        N.NomeCurso = segmento;

        getline(ss, segmento, ';');
        N.grau = segmento;

        getline(ss, segmento, ';');
        N.turno = segmento;

        getline(ss, segmento, ';');
        if (!segmento.empty()) {
            N.ModConcorrencia = segmento[0];
        } else {
            N.ModConcorrencia = ' ';
        }

        getline(ss, segmento, ';');
        N.TipoConcorrencia = segmento;

        getline(ss, segmento, ';');
        N.DsModConcorrencia = segmento;

        getline(ss, segmento, ';');

        getline(ss, segmento, ';');
        if (!segmento.empty() && isdigit(segmento[0])) {
            N.Vagas = stoi(segmento);
        } else {
            N.Vagas = 0;
        }

        getline(ss, segmento, ';');
        if (!segmento.empty() && (isdigit(segmento[0]) || segmento[0] == '-')) {
            replace(segmento.begin(), segmento.end(), ',', '.');
            N.NotaCorte = stof(segmento);
        } else {
            N.NotaCorte = 0.0f;
        }

        getline(ss, segmento, ';');
        if (!segmento.empty() && isdigit(segmento[0])) {
            N.QtdIncricao = stoi(segmento);
        } else {
            N.QtdIncricao = 0;
        }

        notas[cont] = N;
        cont++;
    }

    return cont;
}


// Abre "2025.txt", carrega os dados e inicia o menu de filtros.
void ConsultarSisu() {

    ifstream inSISU("src/Estatisticas/2025.txt", ios::in);

    if (!inSISU) {
        cout << "Houve uma falha na abertura do arquivo!" << endl;
        exit(1);
    }

    int totalRegistros = CarregarArquivo(inSISU, notas);
    inSISU.close();

    cout << "Total de registros carregados: " << totalRegistros << endl;

    Filtros(notas, totalRegistros);
    getch();
}

//exibe as medias das notas de corte, vagas disponiveis e candidatos inscritos
void ExibirMedias(NotaDeCorte registros[], int quantidade){
    if(quantidade == 0){
        cout << "\nNao ha registros para calcular as medias." << endl;
        return;
    }

    double somaNotas = 0, vagas = 0, inscritos = 0;
    int notasValidas = 0, registrosValidos = 0;

    for(int i = 0; i < quantidade; i++){
        if(registros[i].Vagas == 0 && registros[i].QtdIncricao == 0 && registros[i].NotaCorte == 0.0){
            continue;   //decidi nao considerar os cursos que tem 0 vagas, 0 inscricoes e 0 na nota de corte, para nao afetar a media final
        }

        registrosValidos++;
        vagas = vagas + registros[i].Vagas;
        inscritos = inscritos + registros[i].QtdIncricao;

        if(registros[i].NotaCorte > 0){   //exclui as notas de corte zeradas
            somaNotas = somaNotas + registros[i].NotaCorte;
            notasValidas++;
        }
    }

    if(registrosValidos == 0){
        cout << "\nNao ha registros para calcular as medias." << endl;
        return;
    }
    int mediaVagas = round(vagas / registrosValidos);
    int mediaInscritos = round(inscritos / registrosValidos);

    cout << fixed << setprecision(2);
    cout << "\n--------------------------------------------------------\n";
    cout << "\nMedias dos " << registrosValidos << " registros validos analizados:" << endl;

    if(notasValidas > 0){
        cout << "\nMedia das notas de corte (" << notasValidas << " notas analizadas): " << somaNotas / notasValidas << endl;
    }else{
        cout << "\nMedia das notas de corte: sem notas validas." << endl;
    }
    cout << "Media de vagas por curso: " << mediaVagas << endl;
    cout << "Media de candidatos inscritos por curso: " << mediaInscritos << endl;
    cout << "\n--------------------------------------------------------\n\n";
}


// Dados gerais


void FiltrosParticipantes(){
    const int TotalFiltros = 10;

    string filtros[TotalFiltros], entrada;
    char opc;
    int indice = -1, encontrados;
    bool algumFiltro = false, opcaoValida = false;

    do{
        cout << "\n========================================================\n"
             << "\nEscolha qual filtro deseja aplicar\n" << endl
             << "A - Sexo" << endl
             << "B - Cor/raca" << endl
             << "C - Faixa etaria" << endl
             << "D - Treineiro" << endl
             << "E - Nacionalidade" << endl
             << "F - Municipio da prova" << endl
             << "G - Possui renda" << endl
             << "H - Possui acesso a wifi" << endl
             << "I - Situacao do ensino medio" << endl
             << "J - Tipo do ensino medio" << endl
             << "K - Pesquisar quantidade" << endl
             << "L - Limpar filtros" << endl
             << "X - Sair" << endl
             << "\n========================================================\n";

        opc = toupper(getch());
        indice = -1;

        switch(opc){
            case 'A':
                indice = 0;
                cout << "\n1 - Feminino" << endl
                     << "2 - Masculino" << endl
                     << "\n========================================================\n";
                break;

            case 'B':
                indice = 1;
                cout << "\n1 - Nao declarado" << endl
                     << "2 - Branca" << endl
                     << "3 - Preta" << endl
                     << "4 - Parda" << endl
                     << "5 - Amarela" << endl
                     << "6 - Indigena" << endl
                     << "\n========================================================\n";
                break;

            case 'C':
                indice = 2;
                cout << "\nEscolha a faixa etaria:" << endl
                     << "\n1 - Menor de 17 anos" << endl
                     << "2 - 17 anos" << endl
                     << "3 - 18 anos" << endl
                     << "4 - 19 anos" << endl
                     << "5 - 20 anos" << endl
                     << "6 - 21 anos" << endl
                     << "7 - 22 anos" << endl
                     << "8 - 23 anos" << endl
                     << "9 - 24 anos" << endl
                     << "10 - 25 anos" << endl
                     << "11 - Entre 26 e 30 anos" << endl
                     << "12 - Entre 31 e 35 anos" << endl
                     << "13 - Entre 36 e 40 anos" << endl
                     << "14 - Entre 41 e 45 anos" << endl
                     << "15 - Entre 46 e 50 anos" << endl
                     << "16 - Entre 51 e 55 anos" << endl
                     << "17 - Entre 56 e 60 anos" << endl
                     << "18 - Entre 61 e 65 anos" << endl
                     << "19 - Entre 66 e 70 anos" << endl
                     << "20 - Maior de 70 anos" << endl
                     << "\n========================================================\n";
                 break;

            case 'D':
                indice = 3;
                cout << "\n1 - Nao e treineiro" << endl
                     << "2 - E treineiro" << endl
                     << "\n========================================================\n";
                break;

            case 'E':
                indice = 4;
                cout << "\n1 - Nao informado" << endl
                     << "2 - Brasileiro" << endl
                     << "3 - Brasileiro naturalizado" << endl
                     << "4 - Estrangeiro" << endl
                     << "5 - Brasileiro nascido no exterior" << endl
                     << "\n========================================================\n";
                break;

            case 'F':
                indice = 5;
                cout << "\nDigite o municipio da prova como aparece no CSV: "
                     << "\n========================================================\n";
                break;

            case 'G':
                indice = 6;
                cout << "\n1 - Nao possui renda" << endl
                     << "2 - Possui renda" << endl
                     << "\n========================================================\n";
                break;

            case 'H':
                indice = 7;
                cout << "\n1 - Nao possui acesso a wifi" << endl
                     << "2 - Possui acesso a wifi" << endl
                     << "\n========================================================\n";
                break;

            case 'I':
                indice = 8;
                cout << "\n1 - Ja concluiu o Ensino Medio" << endl
                     << "2 - Esta cursando e concluira em 2025" << endl
                     << "3 - Esta cursando e concluira apos 2025" << endl
                     << "4 - Nao concluiu e nao esta cursando" << endl
                     << "\n========================================================\n";
                break;

            case 'J':
                indice = 9;
                cout << "\n1 - Ensino Regular" << endl
                     << "2 - Educacao Especial" << endl
                     << "\n========================================================\n";
                break;

            case 'K': {
                algumFiltro = false;
                for(int i = 0; i < TotalFiltros; i++){
                    if(filtros[i] != ""){
                        algumFiltro = true;
                    }
                }

                if(algumFiltro == false){
                    cout << "\nNenhum filtro aplicado ou nenhum participante encontrado." << endl
                         << "\n========================================================\n";
                }else{
                    encontrados = Encontrar(filtros);

                    if(encontrados >= 0){
                        cout << "\nParticipantes encontrados: " << encontrados << endl
                             << "\n========================================================\n";
                    }
                }

                getch();
                for(int i = 0; i < TotalFiltros; i++){
                    filtros[i] = "";
                }
                system("cls");
                break;
            }

            case 'L':
                for(int i = 0; i < TotalFiltros; i++){
                    filtros[i] = "";
                }
                cout << "\nFiltros limpos." << endl;
                break;

            case 'X':
                break;

            default:
                cout << "\nOpcao invalida." << endl;
                break;
        }

        if(indice != -1){
            getline(cin, entrada);
            opcaoValida = true;

            if(indice == 0){ //sexo
                if(entrada == "1") entrada = "F";
                else if(entrada == "2") entrada = "M";
                else opcaoValida = false;
            }else if(indice == 1){ //cor/raca
                if(entrada == "1") entrada = "0";
                else if(entrada == "2") entrada = "1";
                else if(entrada == "3") entrada = "2";
                else if(entrada == "4") entrada = "3";
                else if(entrada == "5") entrada = "4";
                else if(entrada == "6") entrada = "5";
                else opcaoValida = false;
            }else if(indice == 3){ //treineiro
                if(entrada == "1") entrada = "0";
                else if(entrada == "2") entrada = "1";
                else opcaoValida = false;
            }else if(indice == 4){ //nacionalidade
                if(entrada == "1") entrada = "0";
                else if(entrada == "2") entrada = "1";
                else if(entrada == "3") entrada = "2";
                else if(entrada == "4") entrada = "3";
                else if(entrada == "5") entrada = "4";
                else opcaoValida = false;
            }else if(indice == 6 || indice == 7){ //renda ou wifi
                if(entrada == "1") entrada = "A";
                else if(entrada == "2") entrada = "B";
                else opcaoValida = false;
            //nao coloquei pra quando o indice seja 2, 8 e 9 pq o proprio valor digitado ja vai ser o valor que ta na tabela
            //e o ndice 5 nao coloquei pq e uma string digitada pelo usuario
            }

            if(opcaoValida && entrada != ""){
                filtros[indice] = entrada;
                cout << "\nFiltro selecionado." << endl;
            }else{
                cout << "\nOpcao invalida." << endl;
            }
        }

    }while(opc != 'X');
}

int Encontrar (string filtros[]) {
    ifstream arquivo("PARTICIPANTES2025.txt");
    int encontrados;

    if(!arquivo.is_open()){
        cout << "Houve um erro ao abrir o arquivo.\n" << endl;
        return -1;
    }
    else {
        string linha;
        string faixaEtaria, sexo, cor, nacionalidade, situacaoEM, tipoEM, treineiro, municipio, renda, wifi;
        encontrados = 0;

        while(getline(arquivo, linha)){ // tirar o /r
            if(!linha.empty() && linha[linha.size()-1]=='\r'){
                linha.erase(linha.size()-1);
            }
            stringstream ss(linha);
            getline(ss, faixaEtaria, ';');

            getline(ss, sexo, ';');

            getline(ss, cor, ';');

            getline(ss, nacionalidade, ';');

            getline(ss, situacaoEM, ';');

            getline(ss, tipoEM, ';');

            getline(ss, treineiro, ';');

            getline(ss, municipio, ';');

            getline(ss, renda, ';');

            getline(ss, wifi, ';');

            bool bateu = true;

            if(filtros[0] != "" && filtros[0] != sexo) {
                bateu = false;
            }
            if(filtros[1] != "" && filtros[1] != cor){
                bateu = false;
            }
            if(filtros[2] != "" && filtros[2] != faixaEtaria){
                bateu = false;
            }
            if(filtros[3] != "" && filtros[3] != treineiro){
                bateu = false;
            }
            if(filtros[4] != "" && filtros[4] != nacionalidade){
                bateu = false;
            }
            if(filtros[5] != "" && filtros[5] != municipio){
                bateu = false;
            }
            if(filtros[6] != "" && filtros[6] != renda){
                bateu = false;
            }
            if(filtros[7] != "" && filtros[7] != wifi){
                bateu = false;
            }
            if(filtros[8] != "" && filtros[8] != situacaoEM){
                bateu = false;
            }
            if(filtros[9] != "" && filtros[9] != tipoEM){
                bateu = false;
            }
            if(bateu){
                encontrados++;
            }
        }
    }
    return encontrados;
}
}
