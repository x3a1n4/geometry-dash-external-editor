#pragma once

#include "base_window.h"

namespace gdee::ui{

class MainWindow : public BaseWindow {
public:
    virtual void Update() override;
private:
    // temporary members for testing
	float clear_color[3] = { .0f, .0f, .0f };
};


}