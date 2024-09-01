#include "sqlite/PRDatabase.hpp"

#include <iostream>

#include "sqlite/PlayerTable.hpp"

PRDatabase* PRDatabase::_db_reference = NULL;

PRDatabase::PRDatabase()
    :_sql_database(NULL) {}

void PRDatabase::cachePlayerTable()
{
    _player_table_cache.clear();
    sqlite3_stmt* statement;
    std::string message = "SELECT * FROM " +
        std::string(PLAYER_TABLE_NAME) + " ORDER BY " +
        std::string(PLAYER_TABLE_ROW_PNAME) + " COLLATE NOCASE ASC";
    int ret = sqlite3_prepare_v2(PRDatabase::get()->_sql_database, message.c_str(), message.size(), &statement, NULL);
    if ( ret != SQLITE_OK)
    {
        std::cerr << "sqlite3 error: " << sqlite3_errmsg(PRDatabase::get()->_sql_database) << std::endl;
        sqlite3_close(PRDatabase::get()->_sql_database);
        return;
    }

    while ( (ret = sqlite3_step(statement)) == SQLITE_ROW )
    {
        const unsigned char* pname = sqlite3_column_text(statement, PLAYER_TABLE_ROW_PNAME_IDX);
        _player_table_cache.emplace_back((const char*)pname);
    };

    if (ret != SQLITE_DONE)
    {
        std::cerr << "sqlite3_step error: " << sqlite3_errmsg(PRDatabase::get()->_sql_database) << std::endl;
    }
    sqlite3_finalize(statement);
}

void PRDatabase::cacheIfChanged()
{
    if (!_has_changed)
        return;
    
    // cache
    cachePlayerTable();

    _has_changed = false;
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
    if (!doesPlayerTableExist(_sql_database))
    {
        if (!addPlayerTableToDB(_sql_database))
        {
            std::cerr << "Failed to add Players Table to DB." << std::endl;
            closeDB();
            return false;
        }
    }
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
        _has_changed = true;
    }
    return true;
}

// ===   GETTERS   ===

const std::vector<PlayerTableRow>& PRDatabase::getPlayerTable()
{
    if (isDBLoaded())
        cacheIfChanged();
    return _player_table_cache;
}
