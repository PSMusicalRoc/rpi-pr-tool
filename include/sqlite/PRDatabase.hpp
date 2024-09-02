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

/**
 * The singleton class representing the physical
 * database, as well as including functionality
 * for altering said database.
 * 
 * @author Tim Bishop
 */
class PRDatabase
{
protected:
    /** Singleton reference pointer */
    static PRDatabase* _db_reference;

    /** Default constructor - does not load any file */
    PRDatabase();

private:
    /**
     * A flag variable that represents if the cache has changed since
     * the last frame
     */
    bool _has_changed = true;

    /** The database handle - NULL if no file loaded */
    sqlite3* _sql_database;

    /**
     * The list of players currently cached - should be
     * the same as the what's stored in the db file.
     */
    std::vector<PlayerTableRow> _player_table_cache;

// Caching methods
private:
    /**
     * Caches the player table into memory, such
     * that clients can access a constant version
     * of the data via getPlayerTable().
     */
    void cachePlayerTable();

    /**
     * Checks if _has_changed is true, and if so,
     * calls all relevant caching methods and sets
     * _has_changed to false.
     */
    void cacheIfChanged();

public:
    /**
     * Gets (or initializes) the singleton reference
     * to the database.
     * 
     * @returns A pointer to the PRDatabase object
     */
    static PRDatabase* get();

    /**
     * Destroys the PRDatabase, closing the sqlite
     * handle and setting all values to their default
     * states.
     */
    static void destroy();


    /**
     * Loads a database file into the PRDatabase object.
     * If a database is already loaded, this function closes
     * the previous handle, then opens the new one.
     * 
     * @param filename A path to a filename, either absolute
     * or relative to the cwd.
     * 
     * @returns True if the database was successfully loaded,
     * false if there were any errors.s
     */
    bool loadDB(const std::string& filename);

    /**
     * Closes the current sqlite database handle. Even if one
     * is not open, calling this function will not cause an
     * error, it will simply just return true.
     * 
     * @return True if the database is successfully closed (or
     * if the database was already closed), false for any errors.
     */
    bool closeDB();

    /**
     * Checks if there is a sqlite database currently
     * loaded.
     * 
     * @return True if there is a DB loaded, false if
     * the handle == NULL (not loaded).
     */
    bool isDBLoaded() const { return this->_sql_database != NULL; }

    /**
     * Checks if the underlying database has changed since
     * the last cache.
     * 
     * @return True if the database has changed, false if
     * not.
     */
    bool hasChanged() const { return this->_has_changed; }

    // getters for players, tournaments, etc

    /**
     * Returns a reference to the cached players, recaching
     * if hasChanged() == true.
     * 
     * @return A constant reference to the player table's
     * data (or at least the cached version of it.)
     */
    const std::vector<PlayerTableRow>& getPlayerTable();

    // DB Operations that can be done by the user

    /**
     * Adds a player to the currently loaded database.
     * 
     * @todo Add check in implementation that there is
     * a currently loaded database.
     * 
     * @todo Ensure this method adds data to PlacementTable
     * as well.
     * 
     * @param player_name The name of the player to add
     * to the database
     * 
     * @returns True if the player was added successfully
     * (or the player already existed), false if any errors
     * occurred or (TODO!) there is no database loaded.
     */
    bool addPlayerToDB(const std::string& player_name);

    /**
     * Removes a player from the currently loaded database.
     * 
     * @todo Add check in implementation that there is
     * a currently loaded database.
     * 
     * @todo Ensure this method removes data from PlacementTable
     * (and tournament table?) as well.
     * 
     * @param player_name The name of the player to remove
     * from the database
     * 
     * @returns True if the player was removed successfully
     * (or the player did not exist), false if any errors
     * occurred or (TODO!) there is no database loaded.
     */
    bool removePlayerFromDB(const std::string& player_name);
};
