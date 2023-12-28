#include "UIManager.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class UIManager {
public:
	void Init(GLFWwindow* window, const char* glsl_version) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui::StyleColorsDark();
	}

	void NewFrame() {
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Pre-render here
	}

	void Update() {
		// Update toolbar

		// Update all UIs
		// Do this by calling an update() function from each main

	}

	void Render() {
		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Post-render here
	}

	void Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};



