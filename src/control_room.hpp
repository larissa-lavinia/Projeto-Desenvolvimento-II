#pragma once

#include <imgui.h>
#include "nucleo/estruturas.hpp"

void Tests() {
	Bit::BitUnitTest();

}

void Init() {
	Tests();
}

void Update() {
	ImGui::SetNextWindowPos(ImVec2(0, 0)); ImGui::SetNextWindowSize(ImVec2(200, 100));
	ImGui::Begin("#arquivos", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::Text("SECAO TESTE ARQUVIOS");
	ImGui::End();
}