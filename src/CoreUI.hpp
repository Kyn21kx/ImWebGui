#pragma once
#include "IPanel.hpp"
#include "UI/HeaderPanel.hpp"
#include <vector>
class CoreUI {
public:
	static void InitializePanels() {
		s_panels.push_back(CreatePanel<HeaderPanel>());
	}

	static void DrawPanels() {
		for(const auto& panel : s_panels) {
			panel->OnRender();
		}
	}

private:
	static inline std::vector<std::unique_ptr<IPanel>> s_panels;

	template <class T> static std::unique_ptr<T> CreatePanel()
    {
        return std::make_unique<T>();
    }
};
