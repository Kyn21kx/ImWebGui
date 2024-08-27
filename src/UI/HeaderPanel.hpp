#pragma once

#include "Defaults/Image.hpp"
#include "IPanel.hpp"

class HeaderPanel final : public IPanel {
public:
	HeaderPanel();
	void OnRender() override;

private:
	Image m_twitterImage = {};

};
