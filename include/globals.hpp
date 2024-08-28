#pragma once

#include <string>

#include <sqlite3.h>
#include <SDL2/SDL.h>

// GLOBALS

extern sqlite3* db_handle;

extern const int BEGIN_WINDOW_WIDTH;
extern const int BEGIN_WINDOW_HEIGHT;
extern int current_windowwidth_px;
extern int current_windowheight_px;

extern SDL_Window* window;
extern SDL_Renderer* renderer;


// INITIALIZATION FUNCTIONS

bool initialize_application();
bool finish_application();
