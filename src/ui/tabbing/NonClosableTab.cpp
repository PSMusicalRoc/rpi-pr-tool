#include "ui/tabbing/NonClosableTab.hpp"

#include <imgui.h>

NonClosableTab::NonClosableTab(const std::string& tab_name)
    :AbstractTab(tab_name) {}

void NonClosableTab::render()
{
    if (ImGui::BeginTabItem(generateImGUITag().c_str(), NULL))
    {
        displayContents();
        ImGui::EndTabItem();
    }
}
