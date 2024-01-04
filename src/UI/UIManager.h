#pragma once

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class UIManager {
public:
	// Initialize UIManager
	void Init(GLFWwindow* window, const char* glsl_version);

	// These functions loop in the game loop
	void NewFrame();
	virtual void Update();
	void Render();

	// Shutsdown at the end (cleans up)
	void Shutdown();
};