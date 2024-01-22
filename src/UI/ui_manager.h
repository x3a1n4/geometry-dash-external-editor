#pragma once

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace gdee::ui{

class UIManager {
public:
    static int Init();
    static int Loop();

private:
    // GL 3.0 + GLSL 130
    static constexpr const char* glsl_version{"#version 130"}; // https://stackoverflow.com/questions/1639154/how-to-declare-a-static-const-char-in-your-header-file

    static GLFWwindow* window;
};

}