#include "HeaderPanel.hpp"
#include "imgui/imgui.h"
#include <cstdio>

void HeaderPanel::OnRender() {
	ImGui::Checkbox("This is a test button", &this->m_on);
	if (this->m_on) {
		ImGui::Text("Hey there!");
	}
}
