#pragma once

#include "NonClosableTab.hpp"
#include <string>

/**
 * A tab that displays all players currently
 * in the database in a tabular format. From
 * here, the user can add/delete players, as
 * well as open player details tabs.
 */
class PlayerViewTab: public NonClosableTab
{
private:
    /** A buffer for the name of the player to add */
    std::string _player_add_txt;

    /** A buffer for the (inevitable) player search bar */
    std::string _player_filter_txt;

public:
    /** Constructor */
    PlayerViewTab(const std::string& tab_name);
    
    void displayContents() override;
};