#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
/// @brief Custom UI components for ImGui
class Components {

	public:
	static void SpacingVertical(float height) {
		ImGui::Dummy(ImVec2(0.0f, height));
	}

	static bool Spinner(const char *label, float radius, int thickness, const uint32_t &color) {
		ImGuiWindow *window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
		{
		    return false;
		}

		ImGuiContext &g = *GImGui;
		const ImGuiStyle &style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
		{
		    return false;
		}

		// Render
		window->DrawList->PathClear();

		int numSegments = 30;
		int start = abs(ImSin(g.Time * 1.8f) * ((float)numSegments - 5));

		const float a_min = IM_PI * 2.0f * ((float)start) / (float)numSegments;
		const float a_max = IM_PI * 2.0f * ((float)numSegments - 3) / (float)numSegments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for (int i = 0; i < numSegments; i++)
		{
		    const float a = a_min + ((float)i / (float)numSegments) * (a_max - a_min);
		    window->DrawList->PathLineTo(
		        ImVec2(centre.x + ImCos(a + g.Time * 8) * radius, centre.y + ImSin(a + g.Time * 8) * radius));
		}

		window->DrawList->PathStroke(color, 0, thickness);
		return true;
	}

};
