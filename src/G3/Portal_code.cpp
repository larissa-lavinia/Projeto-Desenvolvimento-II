//Arquivo responsável por implementar as funções do portal, vai conter a implementação das funções do portal
#include "Portal_header.h"
#include <iostream>
#include <fstream>

using namespace std;

// Função interna (privada ao .cpp) para gerar os arquivos .txt no disco
void gerarArquivosNoDisco(const PortalEstudos& portal) {
    for (int i = 0; i < portal.totalAreas; i++) {
        for (int j = 0; j < portal.areas[i].totalMaterias; j++) {
            ofstream arquivo(portal.areas[i].materias[j].arquivo);

            if (arquivo.is_open()) {
                arquivo << portal.areas[i].materias[j].conteudo;
                arquivo.close();
            }
        }
    }
}

PortalEstudos iniciarPortalEstudos() {
    Materia* matLinguagens = new Materia[5]{
        {
            "Lingua Portuguesa",
            "lingua_portuguesa.txt",
            "LINGUA PORTUGUESA - ENEM\n\n"
            "1. Interpretacao de texto\n"
            "Interpretar e compreender o sentido de um texto, identificando sua ideia principal, as informacoes explicitas e implicitas, a finalidade e o ponto de vista do autor.\n"
            "Dica: observe o titulo, o contexto, o genero textual e as palavras que indicam opiniao ou conclusao.\n"
            "Exemplo: em uma campanha que incentiva a economia de agua, a finalidade principal costuma ser conscientizar e convencer o leitor a mudar um comportamento.\n"
            "Como aparece no ENEM?\n"
            "Em textos, charges, tirinhas, noticias, propagandas e campanhas. A questao geralmente exige compreender o sentido global, e nao apenas localizar uma palavra.\n\n"
            "2. Generos textuais\n"
            "Sao formas de comunicacao que possuem estrutura, linguagem e finalidade proprias. Exemplos: noticia, reportagem, artigo de opiniao, carta, cronica, receita, propaganda, meme e charge.\n"
            "Exemplo: uma noticia informa um acontecimento; um artigo de opiniao defende um ponto de vista.\n"
            "Como aparece no ENEM?\n"
            "A prova apresenta um texto e pergunta sua finalidade, seu publico-alvo ou a caracteristica que permite identificar o genero.\n\n"
            "3. Variacao linguistica\n"
            "A lingua varia conforme a regiao, a situacao, a idade, o grupo social e o contexto. A linguagem formal costuma ser usada em situacoes mais monitoradas; a informal aparece em conversas cotidianas.\n"
            "Nao existe apenas uma maneira de falar. As variedades linguisticas fazem parte da identidade dos falantes. O preconceito linguistico ocorre quando uma variedade e tratada como inferior.\n"
            "Exemplo: uma conversa entre amigos pode usar girias, enquanto um documento oficial exige maior formalidade.\n"
            "Como aparece no ENEM?\n"
            "Em textos que mostram sotaques, girias, regionalismos e diferentes situacoes de comunicacao. A prova pode abordar identidade cultural e preconceito linguistico.\n\n"
            "4. Funcoes da linguagem\n"
            "Referencial: destaca a informacao.\n"
            "Emotiva: evidencia sentimentos do emissor.\n"
            "Conativa ou apelativa: busca influenciar o receptor.\n"
            "Fatica: testa ou mantem o canal de comunicacao.\n"
            "Metalinguistica: usa a linguagem para explicar a propria linguagem.\n"
            "Poetica: valoriza a forma da mensagem.\n"
            "Exemplo: \"Compre agora!\" apresenta funcao conativa, pois tenta convencer o leitor.\n"
            "Como aparece no ENEM?\n"
            "Em propagandas, poemas, noticias e campanhas, pedindo para identificar a intencao predominante da mensagem.\n\n"
            "5. Coesao e coerencia\n"
            "Coesao e a ligacao entre palavras, frases e paragrafos por meio de pronomes, conjuncoes e outras expressoes.\n"
            "Coerencia e a construcao de um sentido logico para o texto.\n"
            "Exemplo: \"Estudei bastante, portanto fui bem na prova.\" O conectivo \"portanto\" indica conclusao.\n"
            "Como aparece no ENEM?\n"
            "Na analise de conectivos, retomadas de termos, organizacao das ideias e relacoes de causa, consequencia, oposicao e conclusao.\n\n"
            "6. Figuras de linguagem\n"
            "Metafora: comparacao implicita. Exemplo: \"A vida e uma estrada.\"\n"
            "Comparacao: aproxima elementos usando \"como\". Exemplo: \"Forte como um touro.\"\n"
            "Personificacao: atribui caracteristicas humanas a seres ou objetos.\n"
            "Hiperbole: exagero intencional.\n"
            "Ironia: expressa uma ideia sugerindo o contrario.\n"
            "Eufemismo: suaviza uma expressao.\n"
            "Como aparece no ENEM?\n"
            "Em poemas, musicas, charges e textos literarios, relacionando o efeito de sentido produzido pela figura de linguagem.\n"
        },
        {
            "Literatura",
            "literatura.txt",
            "LITERATURA - ENEM\n\n"
            "1. Escolas literarias\n"
            "As escolas literarias sao movimentos que apresentam caracteristicas historicas, culturais e esteticas...\n"
            // (Cole aqui o restante do texto de Literatura do arquivo anterior)
        },
        {
            "Lingua Inglesa",
            "lingua_inglesa.txt",
            "LINGUA INGLESA - ENEM\n\n"
            "1. Interpretacao de textos\n"
            "A prova de ingles prioriza a compreensao, e nao a traducao de cada palavra...\n"
            // (Cole aqui o restante do texto de Ingles do arquivo anterior)
        },
        {
            "Lingua Espanhola",
            "lingua_espanhola.txt",
            "LINGUA ESPANHOLA - ENEM\n\n"
            "1. Interpretacao de textos\n"
            "A prova exige compreender o sentido geral e a finalidade de textos em espanhol...\n"
            // (Cole aqui o restante do texto de Espanhol do arquivo anterior)
        },
        {
            "Artes",
            "artes.txt",
            "ARTES - ENEM\n\n"
            "1. Artes visuais e arte contemporanea\n"
            "As artes visuais incluem pintura, desenho, escultura, fotografia, gravura, instalacao...\n"
            // (Cole aqui o restante do texto de Artes do arquivo anterior)
        }
    };

    Materia* matHumanas = new Materia[4]{
        {"Historia", "historia.txt", "HISTORIA - ENEM\n\n1. Brasil Colonia..."},
        {"Geografia", "geografia.txt", "GEOGRAFIA - ENEM\n\n1. Meio ambiente e questoes ambientais..."},
        {"Filosofia", "filosofia.txt", "FILOSOFIA - ENEM\n\n1. Filosofia politica..."},
        {"Sociologia", "sociologia.txt", "SOCIOLOGIA - ENEM\n\n1. Cultura e sociedade..."}
    };

    Materia* matNatureza = new Materia[3]{
        {"Biologia", "biologia.txt", "BIOLOGIA - ENEM\n\n1. Ecologia..."},
        {"Fisica", "fisica.txt", "FISICA - ENEM\n\n1. Eletrodinamica..."},
        {"Quimica", "quimica.txt", "QUIMICA - ENEM\n\n1. Quimica organica..."}
    };

    Materia* matMatematica = new Materia[1]{
        {"Matematica", "matematica.txt", "MATEMATICA - ENEM\n\n1. Estatistica..."}
    };

    Materia* matRedacao = new Materia[1]{
        {"Redacao", "redacao.txt", "REDACAO - ENEM\n\n1. Estrutura do texto dissertativo-argumentativo..."}
    };

    PortalEstudos portal;
    portal.totalAreas = 5;
    portal.areas = new Area[portal.totalAreas]{
        {"Linguagens, Codigos e suas Tecnologias", matLinguagens, 5},
        {"Ciencias Humanas e suas Tecnologias", matHumanas, 4},
        {"Ciencias da Natureza e suas Tecnologias", matNatureza, 3},
        {"Matematica e suas Tecnologias", matMatematica, 1},
        {"Redacao", matRedacao, 1}
    };

    // Cria todos os .txt assim que o módulo é iniciado
    gerarArquivosNoDisco(portal);

    return portal;
}

char* lerConteudoDoArquivo(const Materia& materia) {
    // Abre o arquivo posicionando o cursor no final (ios::ate) para descobrir o tamanho exato em bytes
    ifstream arquivo(materia.arquivo, ios::ate);

    if (!arquivo.is_open()) {
        return nullptr;
    }

    streamsize tamanho = arquivo.tellg();
    arquivo.seekg(0, ios::beg); // Volta o cursor para o início do arquivo

    // Aloca dinamicamente o buffer exato + 1 byte para o caractere nulo '\0'
    char* buffer = new char[tamanho + 1];

    if (arquivo.read(buffer, tamanho)) {
        buffer[arquivo.gcount()] = '\0'; // Finaliza a C-string corretamente
    } else {
        buffer[arquivo.gcount()] = '\0';
    }

    arquivo.close();
    return buffer;
}

void liberarTextoLido(char*& texto) {
    if (texto != nullptr) {
        delete[] texto;
        texto = nullptr;
    }
}

void encerrarPortalEstudos(PortalEstudos& portal) {
    if (portal.areas != nullptr) {
        for (int i = 0; i < portal.totalAreas; i++) {
            delete[] portal.areas[i].materias;
        }
        delete[] portal.areas;
        portal.areas = nullptr;
        portal.totalAreas = 0;
    }
}