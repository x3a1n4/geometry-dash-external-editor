#include "ui.h"

namespace gdee::python::api{

// define the gdee.ui python module

// features:
/*

UI class (extendable in python)
    - Update()
    // these will be called from ui_manager
    // extend base_window somehow?

gdee.ui.RegisterWindow(window) // how to actually load the window in the first place
gdee.ui.UnregisterWindow(window)
*/ 

// imgui bindings will hopefully be from pyimgui
// can maybe transfer imgui context, we'll see!
// https://pyimgui.readthedocs.io/en/latest/guide/first-steps.html

// example update code in python:
/*
imgui.begin("Custom window", True)

imgui.text("Hello, world!")

if imgui.button("OK"):
    print(f"String: {self.string}")
    print(f"Float: {self.f}")

_, self.string = imgui.input_text("A String", self.string, 256)

_, self.f = imgui.slider_float("float", self.f, 0.25, 1.5)

imgui.end()
*/

// we're writing our own dear imgui bindings, why not

}