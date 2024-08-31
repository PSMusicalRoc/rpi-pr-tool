#pragma once

#include "NonClosableTab.hpp"

class PlayerViewTab: public NonClosableTab
{
public:
    PlayerViewTab(const std::string& tab_name);
    void displayContents() override;
};