#pragma once

#include "NonClosableTab.hpp"
#include <string>

class PlayerViewTab: public NonClosableTab
{
private:
    std::string _player_add_txt;
    std::string _player_filter_txt;

public:
    PlayerViewTab(const std::string& tab_name);
    void displayContents() override;
};