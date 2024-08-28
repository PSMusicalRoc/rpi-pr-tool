#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

#include <sqlite3.h>

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

    while (application_running)
    {
        // get events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                application_running = false;
            }
        }

        // catch early if user clicks "X"
        if (!application_running)
            break;
        
        // Rendering :)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // load_sqlite_db(&db_handle, "test.sqlite");

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

    // close sqlite database

    finish_application();

    return 0;
}