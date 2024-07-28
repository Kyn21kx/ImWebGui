#pragma once

#include "IPanel.hpp"

class HeaderPanel final : public IPanel {
public:
	HeaderPanel(const HeaderPanel &) = default;
	HeaderPanel(HeaderPanel &&) = default;
	HeaderPanel &operator=(const HeaderPanel &) = default;
	HeaderPanel &operator=(HeaderPanel &&) = default;

	void OnRender() override;

};
