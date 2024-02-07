#include <iostream>

#include "UI/ui_manager.h"
#include "Python/addon_manager.h"

int main(int, char**){
    std::cout << "Hello, from gdee!\n";

    // load python
    typedef gdee::python::AddonManager AddonManager;
    AddonManager::Init();

    // open UI
    typedef gdee::ui::UIManager UIManager;
    UIManager::Init();

    // start UI loop
    UIManager::Loop();
}