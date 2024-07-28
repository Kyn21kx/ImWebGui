#pragma once

#include "IPanel.hpp"

class HeaderPanel final : public IPanel {
public:
	void OnRender() override;

private:
	bool m_on = false;

};
