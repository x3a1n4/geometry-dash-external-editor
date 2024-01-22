#include <iostream>

#include "UI/ui_manager.h"

int main(int, char**){
    std::cout << "Hello, from gdee!\n";

    // open UI
    typedef gdee::ui::UIManager UIManager;
    UIManager::Init();

    // start UI loop
    UIManager::Loop();
}