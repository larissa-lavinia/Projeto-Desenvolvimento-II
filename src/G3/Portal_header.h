//Arquivo de cabeçalho do portal, vai conter a assinatura das funções do portal
#ifndef MODULO_ESTUDOS_H
#define MODULO_ESTUDOS_H

struct Materia {
    const char* nome;
    const char* arquivo;
    const char* conteudo;
};

struct Area {
    const char* nome;
    Materia* materias;
    int totalMaterias;
};

struct PortalEstudos {
    Area* areas;
    int totalAreas;
};

// 1. Inicializa a estrutura na memória e gera os arquivos .txt no disco
PortalEstudos iniciarPortalEstudos();

// 2. Lê o arquivo .txt de uma matéria específica e retorna o conteúdo do arquivo..
// Retorna nullptr se o arquivo não puder ser aberto
char* lerConteudoDoArquivo(const Materia& materia);

// 3. Libera a memória do texto lido quando o usuário fechar a janela/matéria na ImGui
void liberarTextoLido(char*& texto);

// 4. Libera toda a estrutura principal ao encerrar o programa
void encerrarPortalEstudos(PortalEstudos& portal);

#endif










