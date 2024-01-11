#include "UIManager.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <algorithm>

void UIManager::Init(GLFWwindow* window, const char* glsl_version) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
}

// Register new frame
void UIManager::RegisterFrame(UIModule::UI_Object& frame) {
	allFrames.push_back(frame);
}

// Unegister new frame
void UIManager::UnegisterFrame(UIModule::UI_Object& frame) {
	// TODO: remove!
}

void UIManager::NewFrame() {
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Pre-render here
	for (UIModule::UI_Object& frame : allFrames) {
		UIModule::preRender(&frame);
	}
}

void UIManager::Update() {
	// Update toolbar

	// Update all UIs
	for (UIModule::UI_Object& frame : allFrames) {
		UIModule::render(&frame);
	}

}

void UIManager::Render() {
	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Post-render here
	for (UIModule::UI_Object& frame : allFrames) {
		UIModule::postRender(&frame);
	}
}

void UIManager::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


