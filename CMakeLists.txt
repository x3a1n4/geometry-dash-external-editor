cmake_minimum_required(VERSION 3.8.0)

# Project
project(gdee VERSION 0.1.0 LANGUAGES C CXX)

# Currently in debug mode
include(CTest)
enable_testing()

# Unsure what these do
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Include sub-projects
add_subdirectory("src")
