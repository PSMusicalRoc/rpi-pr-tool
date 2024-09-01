#include "sqlite/PRDatabase.hpp"

#include <iostream>

PRDatabase* PRDatabase::_db_reference = NULL;

PRDatabase::PRDatabase()
    :_sql_database(NULL) {}

void PRDatabase::cacheIfChanged()
{
    if (!_has_changed)
        return;
    // cache
}

PRDatabase* PRDatabase::get()
{
    if (_db_reference == NULL)
    {
        _db_reference = new PRDatabase();
    }
    return _db_reference;
}


void PRDatabase::destroy()
{
    if (_db_reference != NULL)
    {
        _db_reference->closeDB();
        delete _db_reference;
    }
    _db_reference = NULL;
}

bool PRDatabase::loadDB(const std::string& filename)
{
    if (isDBLoaded())
    {
        closeDB();
    }

    int ret = sqlite3_open(filename.c_str(), &_sql_database);

    if ( ret != SQLITE_OK )
    {
        std::cerr << "sqlite3 error: " << sqlite3_errmsg(_sql_database) << std::endl;
        return false;
    }

    // initialize db if not already
    // if (!doesPlayerTableExist(_sql_database))
    // {
    //     if (!addPlayerTableToDB(_sql_database))
    //     {
    //         std::cerr << "Failed to add Players Table to DB." << std::endl;
    //         sqlite3_close(_sql_database);
    //         return false;
    //     }
    // }
    // if (!doesTournamentTableExist(_sql_database))
    // {
    //     if (!addTournamentTableToDB(_sql_database))
    //     {
    //         std::cerr << "Failed to add Tournaments Table to DB." << std::endl;
    //         sqlite3_close(_sql_database);
    //         return false;
    //     }
    // }
    return true;
}

bool PRDatabase::closeDB()
{
    if (_sql_database != NULL)
    {
        sqlite3_close(_sql_database);
        _sql_database = NULL;
    }
    return true;
}