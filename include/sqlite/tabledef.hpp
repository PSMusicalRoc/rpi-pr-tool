#pragma once

#include "PlacementTable.hpp"
#include "PlayerTable.hpp"
#include "TournamentTable.hpp"
#include <string>

bool load_sqlite_db(sqlite3** db_ptr, const std::string& filename);
