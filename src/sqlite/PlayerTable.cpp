#include "sqlite/PlayerTable.hpp"

#include <iostream>

bool doesPlayerTableExist(sqlite3* db_handle)
{
    sqlite3_stmt* statement;
    std::string msg = "SELECT EXISTS (SELECT * FROM sqlite_master WHERE type='table' AND name='"+ std::string(PLAYER_TABLE_NAME) + "');";
    int retval = sqlite3_prepare_v2(db_handle, msg.c_str(), msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "doesPlayerTableExist error: " << sqlite3_errmsg(db_handle) << std::endl;
        return false;
    }

    sqlite3_step(statement);
    retval = sqlite3_column_int(statement, 0);
    
    sqlite3_finalize(statement);

    return retval == 1;
}

bool addPlayerTableToDB(sqlite3* db_handle)
{
    sqlite3_stmt* statement;
    std::string msg = "CREATE TABLE " + std::string(PLAYER_TABLE_NAME) +
        " (" + std::string(PLAYER_TABLE_ROW_PNAME) + " text, " +
        std::string(PLAYER_TABLE_ROW_PIDX) + " INTEGER PRIMARY KEY AUTOINCREMENT)";
    
    int retval;
    retval = sqlite3_prepare_v2(db_handle, msg.c_str(), msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "addPlayerTableToDB error: " << sqlite3_errmsg(db_handle) << std::endl;
        return false;
    }

    retval = sqlite3_step(statement);
    if (retval == SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        return true;
    }
    else
    {
        sqlite3_finalize(statement);
        return false;
    }
}

bool insertPlayerIntoPlayerTable(sqlite3* db_handle, const std::string& playername)
{
    sqlite3_stmt* statement;
    std::string check_player_msg = "SELECT EXISTS(SELECT * FROM " +
        std::string(PLAYER_TABLE_NAME) + " WHERE " +
        std::string(PLAYER_TABLE_ROW_PNAME) + "='" +
        playername + "')";
    std::string msg = "INSERT INTO " + std::string(PLAYER_TABLE_NAME) +
        " (" + std::string(PLAYER_TABLE_ROW_PNAME) +
        ") VALUES ('" + playername + "')";
    int retval;

    // check if name exists
    retval = sqlite3_prepare_v2(db_handle, check_player_msg.c_str(), check_player_msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "insertPlayerIntoPlayerTable error: " << sqlite3_errmsg(db_handle) << std::endl;
        return false;
    }

    sqlite3_step(statement);
    int exists = sqlite3_column_int(statement, 0);
    sqlite3_finalize(statement);

    if (exists == 1)
    {
        // player already exists, return true
        return true;
    }

    // insert player
    retval = sqlite3_prepare_v2(db_handle, msg.c_str(), msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "insertPlayerIntoPlayerTable error: " << sqlite3_errmsg(db_handle) << std::endl;
        return false;
    }

    retval = sqlite3_step(statement);
    if (retval == SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        return true;
    }
    else
    {
        sqlite3_finalize(statement);
        return false;
    }
}

bool removePlayerFromPlayerTable(sqlite3* db_handle, const std::string& playername)
{
    sqlite3_stmt* statement;
    std::string check_player_msg = "SELECT EXISTS(SELECT * FROM " +
        std::string(PLAYER_TABLE_NAME) + " WHERE " +
        std::string(PLAYER_TABLE_ROW_PNAME) + "='" +
        playername + "')";
    std::string msg = "DELETE FROM " + std::string(PLAYER_TABLE_NAME) +
        " WHERE " + std::string(PLAYER_TABLE_ROW_PNAME) + "='" +
        playername + "'";
    int retval;

    // check if name exists
    retval = sqlite3_prepare_v2(db_handle, check_player_msg.c_str(), check_player_msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "removePlayerFromPlayerTable error: " << sqlite3_errmsg(db_handle) << std::endl;
        return false;
    }

    sqlite3_step(statement);
    int exists = sqlite3_column_int(statement, 0);
    sqlite3_finalize(statement);

    if (exists == 0)
    {
        // player does not exist, return true
        return true;
    }

    // delete player
    retval = sqlite3_prepare_v2(db_handle, msg.c_str(), msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "removePlayerFromPlayerTable error: " << sqlite3_errmsg(db_handle) << std::endl;
        return false;
    }

    retval = sqlite3_step(statement);
    if (retval == SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        return true;
    }
    else
    {
        sqlite3_finalize(statement);
        return false;
    }
}


// ===   STRUCT METHODS   ===

PlayerTableRow::PlayerTableRow(const std::string& player_name)
    :_player_name(player_name) {}
