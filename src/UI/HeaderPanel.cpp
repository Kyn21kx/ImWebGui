#include "HeaderPanel.hpp"
#include "Constants.hpp"
#include "imgui/imgui.h"
#include <cstdio>

void HeaderPanel::OnRender() {
	//Draw a common header here
	ImGui::Begin("Header", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::SetWindowPos(ImVec2(0, 0));

    // Add logo or title
    ImGui::SetWindowFontScale(0.9f);
    ImGui::Text("Aspis.NET");

    // Adjust the position to the right for the navigation buttons
    const float displaySizeX = ImGui::GetIO().DisplaySize.x;
    float buttonWidth = 30.0f; // Approximate width of a button
    float spacing = 10.0f;     // Spacing between buttons
    float totalButtonWidth = 0.9f * (3 * buttonWidth * spacing); // 3 buttons with spacing

    ImGui::SameLine(totalButtonWidth - ImGui::GetStyle().WindowPadding.x);

    // Add buttons for navigation
    if (ImGui::Button("Home"))
    {
        // Navigate to home
    }
    ImGui::SameLine();
    if (ImGui::Button("About"))
    {
        // Navigate to about
    }
    ImGui::SameLine();
    if (ImGui::Button("Contact"))
    {
        // Navigate to contact
    }

    ImGui::SetWindowFontScale(0.5f);
    ImGui::Text("A small framework for C# web applications");

    ImVec2 size(displaySizeX, Constants::HEADER_HEIGHT);
    ImGui::SetWindowSize(size);
    ImGui::End();
}
