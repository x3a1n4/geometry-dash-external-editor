# CMakeList.txt : CMake project for gdee, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
# TODO: separate build!
add_executable (gdee 
	"main.cpp" 
	"UI/ui.cpp" "UI/ui.h" "UI/CustomImGui.cpp" "UI/CustomImGui.h" 
	"Python/AddonManager.cpp" "Python/AddonManager.h"
	"Python/Addon.cpp" "Python/Addon.h"
	"UI/UIManager.cpp" "UI/UIManager.h"  
	"Python/Module/object.cpp" "Python/Module/ui.cpp" "Python/Module/gdee.h" "Python/Module/gdee.cpp" "Python/Module/object.h" "Python/Module/ui.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET gdee PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

# Add external packages
find_package(glad CONFIG REQUIRED)
target_link_libraries(gdee PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(gdee PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(gdee PRIVATE imgui::imgui)

find_package(Python3 COMPONENTS Development REQUIRED)
target_link_libraries(gdee PRIVATE Python3::Python)
