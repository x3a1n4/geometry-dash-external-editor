#include "ui_manager.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "main_window.h"

namespace gdee::ui{

// Note that these are definitions, just null ones
// Otherwise, it makes a linker error
GLFWwindow* UIManager::window;

int UIManager::Init(){
	// Setup GLFW, make sure it succeeds
	if (!glfwInit())
		return 1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	
	// Create window with graphics context
	window = glfwCreateWindow(1280, 720, "Dear ImGui - Example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	
	// Set config Flags
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // tie window context to glad's opengl funcs
		throw("Unable to context to OpenGL");
		return 1;
	
	// Set screen
	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);
	
	return 0;
}

int UIManager::Loop(){
	
	MainWindow main_window; // NOTE: should this be moved?
	main_window.Init(window, glsl_version);

	while (!glfwWindowShouldClose(window)) {
		// Get all events
		glfwPollEvents();

		// Clear bits
		glClear(GL_COLOR_BUFFER_BIT);

		// Update main window
		main_window.NewFrame();
		main_window.Update();
		main_window.Render();

		// TODO (HIGH): update all windows generated with python

		// TODO (HIGH): add menu bar to GL window: https://github.com/ocornut/imgui/issues/6307 (not worried about the issue, it has nice code)

		// Render multi-viewport windows (popped-out windows)
		// NOTE: original code has an if statement here that checks the config flags. Likely not needed, but noted to be safe
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);

		// Swap the buffers, rendering the window to the screen
		glfwSwapBuffers(window);
	}
	
	main_window.Shutdown();
	
	return 0;
}

}