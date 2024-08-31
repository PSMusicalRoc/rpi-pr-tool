#include "ui/tabbing/NonClosableTab.hpp"

#include <imgui.h>

NonClosableTab::NonClosableTab(const std::string& tab_name)
    :AbstractTab(tab_name) {}

void NonClosableTab::render()
{
    if (ImGui::BeginTabItem(generateImGUITag().c_str(), NULL))
    {
        ImGui::Text("Wow! This is a tab! %d", _unique_id);
        displayContents();
        ImGui::EndTabItem();
    }
}
