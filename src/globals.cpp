#include "globals.hpp"
#include "sqlite/tabledef.hpp"
#include "sqlite/PRDatabase.hpp"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <iostream>

const int BEGIN_WINDOW_WIDTH = 1280;
const int BEGIN_WINDOW_HEIGHT = 720;
int current_windowwidth_px = BEGIN_WINDOW_WIDTH;
int current_windowheight_px = BEGIN_WINDOW_HEIGHT;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

ImFont* default_font = NULL;
ImFont* title_font = NULL;

bool initialize_application()
{
    // initialize sdl2

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL Error: Could not initialize SDL." << std::endl;
        return false;
    }

    // this currently doesn't really do what i want,
    // i figure that DPI shenangians will come up
    // eventually. For now, none of my concern.
    // int window_flags = SDL_WINDOW_ALLOW_HIGHDPI;
    int window_flags = SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("Power Rankings Manager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        current_windowwidth_px, current_windowheight_px, window_flags);
    if (window == NULL)
    {
        std::cerr << "SDL Window failed to create: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    int renderer_flags = 0;
    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (renderer == NULL)
    {
        std::cerr << "SDL Renderer failed to create: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // disable logs and ini
    io.LogFilename = NULL;
    io.IniFilename = NULL;
    default_font = io.Fonts->AddFontFromFileTTF("res/fonts/OpenSans.ttf", 30);
    title_font = io.Fonts->AddFontFromFileTTF("res/fonts/OpenSans-Bold.ttf", 50);

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    return true;
}

bool finish_application()
{
    // destroy ImGUI stuff
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    // SDL deinitialization
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // close sqlite db
    PRDatabase::destroy();

    // all done :)
    return true;
}
