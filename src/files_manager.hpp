#pragma once

#include <fstream>

typedef struct request {
    uint8_t id;
    uint8_t year;
    uint8_t state;
    uint8_t requiredData;
} Request;

enum ReturnCode {
    SUCCESS,
    DATANOTFOUND,
    BADREQUEST,
    FILEERROR,
    UNEXPECTEDERROR,
};

/** @brief Função de ativação de módulo
 * 
 * Ativa o processamento de funções internas do módulo.
 * Deixa o módulo ativo para receber requisições e enviar respostas.
 * 
 * @param cod   Código de seleção do módulo. Se 0, a requisição é do próprio núcleo. Se 1, a requisição é de outro módulo.
 * 
 * @return ReturnCode::SUCCESS      Resposta gravada com sucesso.
 * @return ReturnCode::BADREQUEST   Requisição inválida.
 * @return ReturnCode::FILEERROR    Falha ao abrir ou gravar o arquivo.
 */
ReturnCode module4Execution(uint8_t cod);

/** @brief Envio de requisição a outro módulo
 * 
 * Escreve a requisição no arquivo de conexão do módulo receptor
 * 
 * @param moduleId    Identificador do módulo receptor (ajuda a definir os arquivos que serão utilizados)
 * @param requestCode Requisição contendo ano, estado, dado a ser consultado e id do emissor
 * 
 * @return ReturnCode::SUCCESS        Requisição gravada com sucesso.
 * @return ReturnCode::BADREQUEST     Campos do Request ou id do módulo fora dos valores válidos.
 * @return ReturnCode::FILEERROR      Falha ao abrir ou gravar o arquivo.
 */
ReturnCode send(uint8_t moduleId, Request requestCode);

/** @brief Recebimento de requisição vinda de outro módulo
 * 
 * Lê a requisição no próprio arquivo de conexão
 * 
 * @param moduleId    Identificador próprio
 * 
 * @return requisição recebida
 */

Request receive(uint8_t moduleId);

/** @brief Inicialização de microdados
 * 
 * Lê arquivo .csv a partir do caminho passado e cria arquivo binário
 * correspondente com os dados gravados.
 * 
 * @param path          Caminho do arquivo .csv informado.
 * @param year          Ano do arquivo informado.
 * @param fileType      Tipo dos microdados: 0 - Resultados, 1 - Social.
 * 
 * @return ReturnCode::SUCCESS        Arquivo binário gravado com sucesso.
 * @return ReturnCode::BADREQUEST     Tipo dos microdados não corresponde.
 * @return ReturnCode::FILEERROR      Erro ao tentar abrir o arquivo.
 */
ReturnCode initializeDataFile(std::string path, uint8_t year, uint8_t fileType);