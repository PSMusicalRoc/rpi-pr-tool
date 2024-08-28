#include "sqlite/tabledef.hpp"
#include <iostream>

bool load_sqlite_db(sqlite3** db_ptr, const std::string& filename)
{
    int ret = sqlite3_open(filename.c_str(), db_ptr);

    if ( ret != SQLITE_OK )
    {
        std::cerr << "sqlite3 error: " << sqlite3_errmsg(*db_ptr) << std::endl;
        return false;
    }

    // initialize db if not already
    if (!doesPlayerTableExist(*db_ptr))
    {
        if (!addPlayerTableToDB(*db_ptr))
        {
            std::cerr << "Failed to add Players Table to DB." << std::endl;
            sqlite3_close(*db_ptr);
            return false;
        }
    }
    if (!doesTournamentTableExist(*db_ptr))
    {
        if (!addTournamentTableToDB(*db_ptr))
        {
            std::cerr << "Failed to add Tournaments Table to DB." << std::endl;
            sqlite3_close(*db_ptr);
            return false;
        }
    }

    return true;
}