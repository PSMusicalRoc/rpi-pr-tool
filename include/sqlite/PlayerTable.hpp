/**
 * @file PlayerTable.hpp
 * 
 * This file details operations to be done
 * on a given database in reference to a players
 * table. The table will consist of:
 * - Player name
 * - A unique integer ID (ascending)
 * 
 * @author Tim Bishop
 */


#pragma once

#include <sqlite3.h>
#include <string>

/*/
 * --------------------------------------------
 * |                 PLAYERS                  |
 * |------------------------------------------|
 * | player_name(str)   | player_idx(INTEGER) |
 * --------------------------------------------
 */

#define PLAYER_TABLE_NAME "players"
#define PLAYER_TABLE_ROW_PNAME "player_name"
#define PLAYER_TABLE_ROW_PNAME_IDX 0
#define PLAYER_TABLE_ROW_PIDX "player_idx"
#define PLAYER_TABLE_ROW_PIDX_IDX 1


/**
 * Checks the database to see if the player
 * table (as per the above defines) exists
 * within already.
 * 
 * @param db_handle The `sqlite3` database pointer
 * representing the current database.
 * 
 * @returns `true` if the table exists, `false`
 * if not
 */
bool doesPlayerTableExist(sqlite3* db_handle);

/**
 * Creates the player table into the provided
 * database, whether or not it exists. See
 * doesPlayerTableExist() to check if the table
 * already exists.
 * 
 * @param db_handle The `sqlite3` database pointer
 * representing the current database.
 * 
 * @returns `true` if the table is correctly added
 * to the database, `false` if any error occurred.
 */
bool addPlayerTableToDB(sqlite3* db_handle);

/**
 * Inserts a player into the player table. Requires
 * that the table already be created within the
 * provided database.
 * 
 * @param db_handle The `sqlite3` databasepointer
 * representing the current database.
 * @param playername The name of the player to be
 * inserted into the table.
 * 
 * @returns `true` if the player is correctly added
 * to the table (or if the player was already in the
 * table), `false` if any error occurred.
 */
bool insertPlayerIntoPlayerTable(sqlite3* db_handle, const std::string& playername);

bool removePlayerFromPlayerTable(sqlite3* db_handle, const std::string& playername);


/**
 * Structure used for caching a Player Table Row
 * in PRDatabase.
 */
class PlayerTableRow
{
private:
    std::string _player_name;

public:
    PlayerTableRow(const std::string& player_name = "");

    const std::string& getPlayerName() const { return _player_name; }
};