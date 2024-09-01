/**
 * @file PRDatabase.hpp
 * 
 * This file defines a C++ wrapper class
 * (a singleton, actually!) for the SQLite3
 * database struct. It contains caching
 * logic, as well as specialized functionality
 * for creating RPIPR conforming databases.
 * 
 * @author Tim Bishop
 */

#pragma once

#include <string>
#include <vector>

#include <sqlite3.h>
#include "PlayerTable.hpp"

class PRDatabase
{
protected:
    static PRDatabase* _db_reference;

    PRDatabase();

private:
    bool _has_changed = true;
    std::vector<PlayerTableRow> _player_table_cache;
    sqlite3* _sql_database;

// Caching methods
private:
    void cachePlayerTable();
    void cacheIfChanged();

public:
    static PRDatabase* get();
    static void destroy();

    bool loadDB(const std::string& filename);
    bool closeDB();
    bool isDBLoaded() const { return this->_sql_database != NULL; }
    bool hasChanged() const { return this->_has_changed; }

    // getters for players, tournaments, etc
    const std::vector<PlayerTableRow>& getPlayerTable();

    // DB Operations that can be done by the user

    bool addPlayerToDB(const std::string& player_name);
    bool removePlayerFromDB(const std::string& player_name);
};
