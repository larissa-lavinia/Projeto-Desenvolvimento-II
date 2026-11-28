#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <string>
#include <fstream>

using namespace std;

struct NotaDeCorte{
    string edicao;
    int CoIes;
    string NoIes;
    string SgIes;
    string OrganizacaoAcademica;
    string Categoria;
    string Campus;
    string Munincipio;
    string Estado;
    string Regiao;
    int CoIesCurso;
    string NomeCurso;
    string grau;
    string turno;
    char ModConcorrencia;
    string TipoConcorrencia;
    string DsModConcorrencia;
    int Vagas;
    float NotaCorte;
    int QtdIncricao;
};

namespace ndc{

void menu();

int CarregarArquivo(ifstream &f, NotaDeCorte notas[]);
void ConsultarSisu();
void Filtros(NotaDeCorte notas[], int totalRegistros);
void ExibirRegistro(const NotaDeCorte &n);
void ExibirListaNotasCorte(const NotaDeCorte &n);
void ExibirListaNotasCorte(NotaDeCorte lista[], int qtd);
int AplicarFiltro(NotaDeCorte vetor[], int totalRegistros, const string &campo, const string &valor);
void ExibirMedias(NotaDeCorte registros[], int quantidade);
void FiltrosParticipantes();
int Encontrar (string filtros[]);

}

#endif
