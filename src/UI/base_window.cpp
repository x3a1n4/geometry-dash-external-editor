#include "base_window.h"

namespace gdee::ui{

void BaseWindow::Init(GLFWwindow* window, const char* glsl_version) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
}

void BaseWindow::NewFrame() {
	// feed inputs to dear imgui, start new frame

	// from https://github.com/ocornut/imgui/wiki/Getting-Started
	// (5) Start of main loop: call backends' ImGui_ImplXXX_NewFrame() functions + call ImGui::NewFrame()
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void BaseWindow::Update() {
    // this method should be overridden
	ImGui::Begin("Base Window");
	ImGui::End();
}

void BaseWindow::Render() {
	// Render dear imgui into screen
	// FIXME: move rendering methods out of BaseWindow, and into a proper rendering handler
	// (for now, just move into ui_manager, can separate into own file if it gets too bulky)
	// Windows should only change Update() anyways

	// End of main loop: call ImGui::Render() + call Render function of Rendering backend (e.g. ImGui_ImplDX11_Render())
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void BaseWindow::Shutdown() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

}