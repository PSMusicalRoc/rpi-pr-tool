#include "ui/tabbing/PlayerViewTab.hpp"

#include "ui/BaseFunctions.hpp"
#include "sqlite/tabledef.hpp"
#include "sqlite/PRDatabase.hpp"
#include "globals.hpp"
#include "IconsFontAwesome6.h"
#include <imgui.h>
#include <imgui_stdlib.h>
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

        ImVec2 area = ImGui::GetContentRegionAvail();
        ImGui::SetCursorPosX((area.x - 200)/2);
        if (ImGui::Button(ICON_FA_USER_PLUS "  Add Player", ImVec2(200, 40)))
        {
            ImGui::OpenPopup("Add Player");
        }

        ImGui::BeginTable((std::string("PlayerTable##")+std::to_string(_unique_id)).c_str(), 2,
            ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_ScrollY);
        for (const PlayerTableRow& row : PRDatabase::get()->getPlayerTable())
        {
            ImGui::TableNextColumn();
            ImGui::Button(("Player: " + row.getPlayerName()).c_str(), ImVec2(ImGui::GetContentRegionAvail().x-45, 40));
            ImGui::SameLine();
            // ImGui::PushFont(icon_font);
            if (ImGui::Button((ICON_FA_TRASH"##" + row.getPlayerName()).c_str(), ImVec2(40, 40)))
            {
                ImGui::OpenPopup(("Delete " + row.getPlayerName()).c_str());
            }
            // ImGui::PopFont();

            if (ImGui::BeginPopupModal(("Delete " + row.getPlayerName()).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Are you sure you want to delete player %s?", row.getPlayerName().c_str());
                if (ImGui::Button("Yes"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        ImGui::EndTable();

        if (ImGui::BeginPopupModal("Add Player", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::InputText("Player Name", &_player_add_txt);
            if (ImGui::Button("Add Player"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }


    } else {
        ImGui::PushFont(title_font);
        ImCustom::CenteredText("No Database is loaded!", true, true);
        ImGui::PopFont();
    }
}