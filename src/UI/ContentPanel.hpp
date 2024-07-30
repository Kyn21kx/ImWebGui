#pragma once

#include "IPanel.hpp"
class ContentPanel final : public IPanel {
public:
	void OnRender() override;
};
