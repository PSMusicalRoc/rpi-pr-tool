#include "globals.hpp"
#include "sqlite/tabledef.hpp"

#include <iostream>

sqlite3* db_handle = NULL;

const int BEGIN_WINDOW_WIDTH = 1280;
const int BEGIN_WINDOW_HEIGHT = 720;
int current_windowwidth_px = BEGIN_WINDOW_WIDTH;
int current_windowheight_px = BEGIN_WINDOW_HEIGHT;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_application()
{
    // initialize sdl2

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL Error: Could not initialize SDL." << std::endl;
        sqlite3_close(db_handle);
        return false;
    }

    int window_flags = SDL_WINDOW_ALLOW_HIGHDPI;
    window = SDL_CreateWindow("Power Rankings Manager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        current_windowwidth_px, current_windowheight_px, window_flags);
    if (window == NULL)
    {
        std::cerr << "SDL Window failed to create: " << SDL_GetError() << std::endl;
        SDL_Quit();
        sqlite3_close(db_handle);
        return false;
    }

    int renderer_flags = 0;
    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (renderer == NULL)
    {
        std::cerr << "SDL Renderer failed to create: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        sqlite3_close(db_handle);
        return false;
    }

    return true;
}

bool finish_application()
{
    // SDL deinitialization
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // close sqlite db
    if (db_handle != NULL)
        sqlite3_close(db_handle);
    return true;
}
