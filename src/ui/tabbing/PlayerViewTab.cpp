#include "ui/tabbing/PlayerViewTab.hpp"

#include "ui/BaseFunctions.hpp"
#include <imgui.h>

PlayerViewTab::PlayerViewTab(const std::string& tab_name)
    :NonClosableTab(tab_name) {}

void PlayerViewTab::displayContents()
{
    ImCustom::CenteredText("X_notY", true, false);
    ImCustom::CenteredText("Y_notX", false, true);
    ImCustom::CenteredText("Both", true, true);
}