#include "ui/tabbing/PlayerViewTab.hpp"

#include "ui/BaseFunctions.hpp"
#include "sqlite/tabledef.hpp"
#include "sqlite/PRDatabase.hpp"
#include "globals.hpp"
#include <imgui.h>
#include <iostream>

PlayerViewTab::PlayerViewTab(const std::string& tab_name)
    :NonClosableTab(tab_name) {}

void PlayerViewTab::displayContents()
{
    if (PRDatabase::get()->isDBLoaded())
    {
        for (const PlayerTableRow& row : PRDatabase::get()->getPlayerTable())
        {
            ImCustom::CenteredText("Player: " + row.getPlayerName(), true, false);
        }
    } else {
        ImGui::PushFont(title_font);
        ImCustom::CenteredText("No Database is loaded!", true, true);
        ImGui::PopFont();
    }
}