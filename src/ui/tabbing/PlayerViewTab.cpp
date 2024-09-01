#include "ui/tabbing/PlayerViewTab.hpp"

#include "ui/BaseFunctions.hpp"
#include "sqlite/tabledef.hpp"
#include "sqlite/PRDatabase.hpp"
#include "globals.hpp"
#include "IconsFontAwesome6.h"
#include <imgui.h>
#include <iostream>

PlayerViewTab::PlayerViewTab(const std::string& tab_name)
    :NonClosableTab(tab_name) {}

void PlayerViewTab::displayContents()
{
    if (PRDatabase::get()->isDBLoaded())
    {
        ImGui::PushFont(title_font);
        ImCustom::CenteredText("Players", true, false);
        ImGui::PopFont();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
        ImGui::BeginTable((std::string("PlayerTable##")+std::to_string(_unique_id)).c_str(), 2,
            ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_ScrollY);
        for (const PlayerTableRow& row : PRDatabase::get()->getPlayerTable())
        {
            ImGui::TableNextColumn();
            ImGui::Button(("Player: " + row.getPlayerName()).c_str(), ImVec2(ImGui::GetContentRegionAvail().x-45, 40));
            ImGui::SameLine();
            ImGui::PushFont(icon_font);
            //"\xef\x97\x88"
            //"\xef\x87\xb8"
            ImGui::Button(ICON_FA_TRASH, ImVec2(40, 40));
            ImGui::PopFont();
        }
        ImGui::EndTable();
    } else {
        ImGui::PushFont(title_font);
        ImCustom::CenteredText("No Database is loaded!", true, true);
        ImGui::PopFont();
    }
}