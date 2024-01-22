cmake_minimum_required(VERSION 3.8.0)

# Just set a global executable for now, may look at cleaning up later
set(SOURCES
    main.cpp
    
    UI/base_window.cpp
    UI/base_window.h
    UI/main_window.cpp
    UI/main_window.h
    UI/ui_manager.cpp
    UI/ui_manager.h

    Python/generic_addon.cpp
    Python/generic_addon.h
    Python/addon_manager.cpp
    Python/addon_manager.h

    Python/Module/gdee.cpp
    Python/Module/gdee.h
)

add_executable(gdee ${SOURCES})

# Set C++ version to C++20
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET gdee PROPERTY CXX_STANDARD 20)
endif()

# Add external packages
find_package(glad CONFIG REQUIRED)
target_link_libraries(gdee PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(gdee PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(gdee PRIVATE imgui::imgui)

find_package(Python3 COMPONENTS Development REQUIRED)
target_link_libraries(gdee PRIVATE Python3::Python)