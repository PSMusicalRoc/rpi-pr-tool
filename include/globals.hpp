#pragma once

#include <string>

#include <sqlite3.h>
#include <SDL.h>
#include <imgui.h>

// GLOBALS

/** Initial window width (px) */
extern const int BEGIN_WINDOW_WIDTH;
/** Initial window height (px) */
extern const int BEGIN_WINDOW_HEIGHT;

/** @todo currently unused? */
extern int current_windowwidth_px;
/** @todo currently unused? */
extern int current_windowheight_px;

/** The backend window pointer */
extern SDL_Window* window;
/** The backend renderer pointer */
extern SDL_Renderer* renderer;

// ImGUI Fonts
/**
 * The default font, contains a normal sized sans serif
 * font and fontawesome icons
 */
extern ImFont* default_font;

/**
 * A "title" font - larger and bolder than default.
 */
extern ImFont* title_font;


// INITIALIZATION FUNCTIONS

/**
 * Initializes the application - does
 * SDL and ImGUI initialization primarily.
 */
bool initialize_application();

/**
 * De-initializes the application, which includes
 * closing any open databases, exits ImGUI backends
 * and deallocates SDL resources.
 */
bool finish_application();
