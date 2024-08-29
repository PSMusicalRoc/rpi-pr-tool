#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

#include <sqlite3.h>
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <ImGuiFileDialog.h>

#include "globals.hpp"
#include "sqlite/tabledef.hpp"

int main(int argc, char** argv)
{
    if (!initialize_application())
    {
        return 1;
    }

    SDL_Event event;
    bool application_running = true;

    IGFD::FileDialogConfig config;
    config.path = ".";
    config.flags = IGFD_FileStyleFlags_::IGFD_FileStyleByTypeFile;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDialog", "Choose File", ".cpp,.h,.hpp", config);

    while (application_running)
    {
        // get events
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                application_running = false;
            }
        }

        // catch early if user clicks "X"
        if (!application_running)
            break;
        
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Rendering :)
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load PR File"))
                {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // ImGui::ShowDemoWindow();
        ImVec2 next_win_pos = ImGui::GetMainViewport()->WorkPos;
        ImGui::SetNextWindowPos(next_win_pos);
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDialog"))
        {
            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // load_sqlite_db(&db_handle, "test.sqlite");

    // close sqlite database

    finish_application();

    return 0;
}

// sqlite3_stmt* statement;
// std::string message = "SELECT * FROM " +
//     std::string(PLAYER_TABLE_NAME) + " ORDER BY " +
//     std::string(PLAYER_TABLE_ROW_PNAME) + " COLLATE NOCASE ASC";
// int ret = sqlite3_prepare_v2(db_handle, message.c_str(), message.size(), &statement, NULL);
// if ( ret != SQLITE_OK)
// {
//     std::cerr << "sqlite3 error: " << sqlite3_errmsg(db_handle) << std::endl;
//     sqlite3_close(db_handle);
//     return 1;
// }

// while ( (ret = sqlite3_step(statement)) == SQLITE_ROW )
// {
//     const unsigned char* pname = sqlite3_column_text(statement, PLAYER_TABLE_ROW_PNAME_IDX);
//     std::cout << "Player: " << pname << std::endl;
// };

// if (ret != SQLITE_DONE)
// {
//     std::cerr << "sqlite3_step error: " << sqlite3_errmsg(db_handle) << std::endl;
// }
// sqlite3_finalize(statement);
