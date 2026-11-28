// Segundo arquivo .cpp que inclui TODOS os headers do modulo.
// Se algum header definisse funcao (em vez de so declarar), o alvo "Testes" nao linkaria
// (erro "multiple definition"). Serve de prova de que os headers sao seguros para o grupo 5.

#include "struct.hpp"
#include "tri.hpp"
#include "gerar_simulado.hpp"
#include "aplicar_prova.hpp"
#include "salvar_resultados.hpp"
#include "executar_simulado.hpp"

bool verificarIncludes() {
    return true;
}
