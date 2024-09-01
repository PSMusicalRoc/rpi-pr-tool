#pragma once

#include <string>

#include <sqlite3.h>
#include <SDL.h>
#include <imgui.h>

// GLOBALS

extern const int BEGIN_WINDOW_WIDTH;
extern const int BEGIN_WINDOW_HEIGHT;
extern int current_windowwidth_px;
extern int current_windowheight_px;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

// ImGUI Fonts
extern ImFont* default_font;
extern ImFont* title_font;
extern ImFont* icon_font;


// INITIALIZATION FUNCTIONS

bool initialize_application();
bool finish_application();
