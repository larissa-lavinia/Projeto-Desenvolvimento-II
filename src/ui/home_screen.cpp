#include "ui/home_screen.hpp"

#include "imgui.h"

#include <cfloat>

namespace {
    void DrawCenteredText(float centerX, float y, float fontSize, ImU32 color, const char* text) {
        const ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text);
        ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), fontSize,
            ImVec2(centerX - textSize.x * 0.5f, y), color, text);
    }
}

void DrawHomeScreen() {
    const ImVec2 origin = ImGui::GetWindowPos();
    const ImVec2 size = ImGui::GetWindowSize();
    const float centerX = origin.x + size.x * 0.5f;
    const float centerY = origin.y + size.y * 0.49f;

    DrawCenteredText(centerX, centerY - 72.0f, 14.0f, IM_COL32(91, 224, 190, 255),
        "PROGRAMAÇÃO II  /  UFS");
    DrawCenteredText(centerX, centerY - 31.0f, 38.0f, IM_COL32(240, 245, 250, 255),
        "Bem-vinda ao ENEMzandia");
    DrawCenteredText(centerX, centerY + 30.0f, 16.0f, IM_COL32(164, 179, 198, 255),
        "Um projeto acadêmico para organizar informações de participantes e respostas do ENEM.");
    DrawCenteredText(centerX, centerY + 58.0f, 15.0f, IM_COL32(112, 132, 155, 255),
        "Use o menu acima para conhecer as páginas que serão desenvolvidas pela equipe.");

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddRectFilled(ImVec2(centerX - 28.0f, centerY + 103.0f),
        ImVec2(centerX + 28.0f, centerY + 106.0f), IM_COL32(91, 224, 190, 255), 2.0f);
}
