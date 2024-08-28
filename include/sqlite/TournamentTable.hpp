/**
 * @file TournamentTable.hpp
 * 
 * This file details operations to be done
 * on a given database in reference to a tournaments
 * table. The table will consist of:
 * - Tournament name
 * - Number of participants
 * - Date performed
 * 
 * @author Tim Bishop
 */

#pragma once

#include <string>
#include <ctime>
#include <sqlite3.h>

#define TOURNAMENT_TABLE_NAME "brackets"
#define TOURNAMENT_TABLE_ROW_TNAME "bracket_name"
#define TOURNAMENT_TABLE_ROW_TNAME_IDX 0
#define TOURNAMENT_TABLE_ROW_NUMPARTICIPANTS "num_participants"
#define TOURNAMENT_TABLE_ROW_NUMPARTICIPANTS_IDX 1
#define TOURNAMENT_TABLE_ROW_DATE "bracket_date"
#define TOURNAMENT_TABLE_ROW_DATE_IDX 2


/**
 * Translates a `time_t` into a date string
 * formatted as "YYYY-MM-DD".
 * 
 * @param in_time The time_t to convert into a date
 * @return A std::string in the above format
 */
std::string getDateStringFromTime(time_t in_time);

/**
 * Translates a date string formatted as "YYYY-MM-DD"
 * into a `time_t`
 * 
 * @param in_time The string to convert into a `time_t`
 * @return A time_t representing the date
 */
time_t getTimeFromDateString(const std::string& in_time);


/**
 * Checks the database to see if the tournament
 * table (as per the above defines) exists
 * within the database already.
 * 
 * @param db_handle The `sqlite3` database pointer
 * representing the current database.
 * 
 * @returns `true` if the table exists, `false`
 * if not
 */
bool doesTournamentTableExist(sqlite3* db_handle);

/**
 * Creates the tournament table into the provided
 * database, whether or not it exists. See
 * doesTournamentTableExist() to check if the table
 * already exists.
 * 
 * @param db_handle The `sqlite3` database pointer
 * representing the current database.
 * 
 * @returns `true` if the table is correctly added
 * to the database, `false` if any error occurred.
 */
bool addTournamentTableToDB(sqlite3* db_handle);

/**
 * Inserts a bracket into the player table. Requires
 * that the table already be created within the
 * provided database.
 * 
 * @param db_handle The `sqlite3` databasepointer
 * representing the current database.
 * @param bracket_name The name of the bracket
 * to add
 * @param num_entrants The number of entrants to
 * apply to the newly added bracket
 * @param date The date the tournament took place
 * 
 * @returns `true` if the player is correctly added
 * to the table (or if the player was already in the
 * table), `false` if any error occurred.
 */
bool insertTournamentIntoTournamentTable(sqlite3* db_handle,
    const std::string& bracket_name, unsigned int num_entrants, time_t date);
