#include "ContentPanel.hpp"
#include "Constants.hpp"
#include "UI/Components.hpp"
#include "imgui/imgui.h"

void ContentPanel::OnRender() {
	//Spacing after the header
	Components::SpacingVertical(Constants::HEADER_HEIGHT);
	ImGui::Text("Hello world");
	Components::Spinner("Loading...", 3.f, 10, 0xFFFFFF);
}
