#include "app/control_room.hpp"

#include "imgui.h"
#include "nucleo/estruturas.hpp"
#include "ui/home_screen.hpp"
#include "ui/pagina1_screen.hpp"
#include "ui/pagina2_screen.hpp"
#include "ui/pagina3_screen.hpp"

namespace {
    AppPage currentPage = AppPage::Home;

    void DrawNavigationButton(const char* label, AppPage page) {
        const bool selected = currentPage == page;

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleColor(ImGuiCol_Button,
            selected ? ImVec4(0.20f, 0.72f, 0.60f, 1.0f) : ImVec4(0.10f, 0.15f, 0.23f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.23f, 0.34f, 0.43f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.18f, 0.58f, 0.51f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text,
            selected ? ImVec4(0.04f, 0.10f, 0.13f, 1.0f) : ImVec4(0.84f, 0.88f, 0.93f, 1.0f));

        if (ImGui::Button(label, ImVec2(112.0f, 38.0f))) {
            if (page != currentPage) currentPage = page;
        }

        ImGui::PopStyleColor(4);
        ImGui::PopStyleVar();
    }

    void DrawCurrentPage() {
        switch (currentPage) {
        case AppPage::Home:
            DrawHomeScreen();
            break;
        case AppPage::Pagina1:
            DrawPagina1Screen();
            break;
        case AppPage::Pagina2:
            DrawPagina2Screen();
            break;
        case AppPage::Pagina3:
            DrawPagina3Screen();
            break;
        }
    }
}

void Tests() {
    Bit::BitUnitTest();
}

void Init() {
    Tests();
}

void Update() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.047f, 0.078f, 0.137f, 1.0f));

    const ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("ENEMzandia", nullptr, flags);

    const ImVec2 origin = ImGui::GetWindowPos();
    const ImVec2 size = ImGui::GetWindowSize();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddRectFilled(origin, ImVec2(origin.x + size.x, origin.y + size.y), IM_COL32(12, 20, 35, 255));

    // Cabeçalho compartilhado entre as quatro páginas.
    const ImVec2 logo(origin.x + 42.0f, origin.y + 24.0f);
    drawList->AddRectFilled(logo, ImVec2(logo.x + 38.0f, logo.y + 38.0f), IM_COL32(91, 224, 190, 255), 9.0f);
    drawList->AddText(ImGui::GetFont(), 23.0f, ImVec2(logo.x + 11.0f, logo.y + 6.0f), IM_COL32(12, 20, 35, 255), "E");
    drawList->AddText(ImGui::GetFont(), 17.0f, ImVec2(logo.x + 50.0f, logo.y + 2.0f), IM_COL32(240, 245, 250, 255), "ENEMzandia");
    drawList->AddText(ImGui::GetFont(), 10.0f, ImVec2(logo.x + 51.0f, logo.y + 23.0f), IM_COL32(112, 132, 155, 255), "PROJETO ACADÊMICO • UFS");

    ImGui::SetCursorPos(ImVec2(size.x - 4.0f * 112.0f - 3.0f * 10.0f - 42.0f, 24.0f));
    DrawNavigationButton("Home", AppPage::Home);
    ImGui::SameLine(0.0f, 10.0f);
    DrawNavigationButton("Pagina1", AppPage::Pagina1);
    ImGui::SameLine(0.0f, 10.0f);
    DrawNavigationButton("Pagina2", AppPage::Pagina2);
    ImGui::SameLine(0.0f, 10.0f);
    DrawNavigationButton("Pagina3", AppPage::Pagina3);

    drawList->AddLine(ImVec2(origin.x + 42.0f, origin.y + 82.0f),
        ImVec2(origin.x + size.x - 42.0f, origin.y + 82.0f), IM_COL32(43, 61, 83, 255));

    DrawCurrentPage();

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(3);
}
