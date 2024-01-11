#pragma once

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Python/Module/ui.h"

#include <vector>

class UIManager {
public:
	// Initialize UIManager
	void Init(GLFWwindow* window, const char* glsl_version);

	// Register new frame
	void RegisterFrame(UIModule::UI_Object& frame);
	// Unegister new frame
	void UnegisterFrame(UIModule::UI_Object& frame);

	// These functions loop in the game loop
	void NewFrame();
	virtual void Update();
	void Render();

	// Shutsdown at the end (cleans up)
	void Shutdown();
private:
	std::vector<UIModule::UI_Object> allFrames;
};