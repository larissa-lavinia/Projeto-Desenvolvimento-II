#include "ui/pagina2_screen.hpp"

#include "imgui.h"

void DrawPagina2Screen() {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const ImVec2 origin = ImGui::GetWindowPos();

    drawList->AddText(ImGui::GetFont(), 30.0f, ImVec2(origin.x + 64.0f, origin.y + 150.0f),
        IM_COL32(240, 245, 250, 255), "Pagina2");
    drawList->AddText(ImGui::GetFont(), 16.0f, ImVec2(origin.x + 64.0f, origin.y + 198.0f),
        IM_COL32(164, 179, 198, 255), "Espaço reservado para a funcionalidade da segunda página.");
}
