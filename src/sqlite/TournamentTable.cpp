#include "sqlite/TournamentTable.hpp"

#include <iostream>
#include <iomanip>


std::string getDateStringFromTime(time_t in_time)
{
    std::string fmt = "%Y-%m-%d";
    tm* mt = localtime(&in_time);
    char buffer[15];
    std::strftime(buffer, sizeof(buffer), fmt.c_str(), mt);

    return buffer;
}

time_t getTimeFromDateString(const std::string& in_time)
{
    tm time_struct = {};
    std::stringstream ss(in_time);
    std::string fmt = "%Y-%m-%d";
    ss >> std::get_time(&time_struct, fmt.c_str());
    return mktime(&time_struct);
}


bool doesTournamentTableExist(sqlite3* db_handle)
{
    sqlite3_stmt* statement;
    std::string msg = "SELECT EXISTS (SELECT * FROM sqlite_master WHERE type='table' AND name='"+
        std::string(TOURNAMENT_TABLE_NAME) + "');";
    int retval = sqlite3_prepare_v2(db_handle, msg.c_str(), msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "doesTournamentTableExist error: " << sqlite3_errmsg(db_handle) << std::endl;
        return false;
    }

    sqlite3_step(statement);
    retval = sqlite3_column_int(statement, 0);
    
    sqlite3_finalize(statement);

    return retval == 1;
}

bool addTournamentTableToDB(sqlite3* db_handle)
{
    sqlite3_stmt* statement;
    std::string msg = "CREATE TABLE " + std::string(TOURNAMENT_TABLE_NAME) +
        " (" + std::string(TOURNAMENT_TABLE_ROW_TNAME) + " text, " +
        std::string(TOURNAMENT_TABLE_ROW_NUMPARTICIPANTS) + " INTEGER, " +
        std::string(TOURNAMENT_TABLE_ROW_DATE) + " INTEGER)";
    
    int retval;
    retval = sqlite3_prepare_v2(db_handle, msg.c_str(), msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "addTournamentTableToDB error: " << sqlite3_errmsg(db_handle) << std::endl;
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

bool insertTournamentIntoTournamentTable(sqlite3* db_handle,
    const std::string& bracket_name, unsigned int num_entrants, time_t date)
{
    sqlite3_stmt* statement;
    std::string check_player_msg = "SELECT EXISTS(SELECT * FROM " +
        std::string(TOURNAMENT_TABLE_NAME) + " WHERE " +
        std::string(TOURNAMENT_TABLE_ROW_TNAME) + "='" +
        bracket_name + "' AND " + std::string(TOURNAMENT_TABLE_ROW_NUMPARTICIPANTS) +
        "=" + std::to_string(num_entrants) + " AND " +
        std::string(TOURNAMENT_TABLE_ROW_DATE) + "=" +
        std::to_string(date) + ")";
    
    std::string msg = "INSERT INTO " +
        std::string(TOURNAMENT_TABLE_NAME) + " (" +
        std::string(TOURNAMENT_TABLE_ROW_TNAME) + ", " +
        std::string(TOURNAMENT_TABLE_ROW_NUMPARTICIPANTS) + ", " +
        std::string(TOURNAMENT_TABLE_ROW_DATE) + ") VALUES ('" +
        bracket_name + "', " +
        std::to_string(num_entrants) + ", " +
        std::to_string(date) + ")";
    // std::string msg = "INSERT INTO " + std::string(PLAYER_TABLE_NAME) +
    //     " (" + std::string(PLAYER_TABLE_ROW_PNAME) +
    //     ") VALUES ('" + playername + "')";
    int retval;

    // check if name exists
    retval = sqlite3_prepare_v2(db_handle, check_player_msg.c_str(), check_player_msg.size(), &statement, NULL);
    if (retval != SQLITE_OK)
    {
        std::cerr << "insertTournamentIntoTournamentTable error: " << sqlite3_errmsg(db_handle) << std::endl;
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