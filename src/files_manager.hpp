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

/** @brief Envio de requisição a outro módulo
 * 
 * Escreve a requisição no arquivo de conexão do módulo receptor
 * Escreve o estado da requisição no arquivo de controle do módulo receptor
 * 
 * @param moduleId    Identificador do módulo receptor (ajuda a definir os arquivos que serão utilizados)
 * @param requestCode Requisição contendo ano, estado, dado a ser consultado e id do emissor
 * 
 * @return ReturnCode::SUCCESS        Requisição gravada e sinalizada com sucesso.
 * @return ReturnCode::BADREQUEST     Campos do Request ou id do módulo fora dos valores válidos.
 * @return ReturnCode::FILEERROR      Falha ao abrir ou gravar os arquivos.
 */
ReturnCode send(uint8_t moduleId, Request requestCode);

/** @brief Envio de resposta de requisição a outro módulo
 * 
 * Escreve a resposta no arquivo de conexão do módulo receptor
 * Escreve o estado da resposta no arquivo de controle do módulo receptor
 * 
 * @param moduleId    Identificador do módulo receptor (ajuda a definir os arquivos que serão utilizados)
 * 
 * @return ReturnCode::SUCCESS        Resposta gravada e sinalizada com sucesso.
 * @return ReturnCode::BADREQUEST     Id do módulo fora dos valores válidos.
 * @return ReturnCode::FILEERROR      Falha ao abrir ou gravar os arquivos.
 */
ReturnCode send(uint8_t moduleId);

/** @brief Recebe requisição de outro módulo
 * 
 * Lê o estado da requisição no próprio arquivo de controle
 * Lê a requisição escrita no próprio arquivo de conexão
 * 
 * @param moduleId      Identificador próprio (módulo receptor)
 * 
 * @return requisição.
 */
Request receive(uint8_t moduleId);

/** @brief Recebe o estado resposta a uma requisição feita
 * 
 * Lê o estado da resposta no próprio arquivo de controle
 * 
 * @param moduleId Identificador próprio (módulo receptor)
 * 
 * @return ReturnCode::SUCCESS        Resposta está em condições de ser lida.
 * @return ReturnCode::DATANOTFOUND   Requisição não retornou dados.
 * @return ReturnCode::FILEERROR      Erro ao tentar abrir os arquivos.
 */
ReturnCode receiveResponse(uint8_t moduleId);

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

/** @brief Quantidade de inscritos
 * 
 * Calcula o total de inscritos em uma edição especifica
 * 
 * @param year      Ano a ser consultado.
 * @param uf        Estado a ser consultado, dado que o valor é igual à posição da uf em ordem alfabética, a partir do zero. Para consulta geral
 *                  de todos os estados, valor do parâmetro deve ser 255.
 * 
 * @return quantidade de inscritos.
 */
int getTotalEntrants(uint8_t year, uint8_t uf);