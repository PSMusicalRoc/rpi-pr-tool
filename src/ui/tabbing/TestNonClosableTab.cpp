#include "ui/tabbing/TestNonClosableTab.hpp"

#include <imgui.h>

TestNonClosableTab::TestNonClosableTab(const std::string& tab_name)
    :NonClosableTab(tab_name) {}

void TestNonClosableTab::displayContents()
{
    if (ImGui::BeginChild((std::string("tabchild##") + std::to_string(_unique_id)).c_str(),
        ImVec2(500, 500)))
    {
        ImGui::TextColored(ImVec4(255, 0, 0, 255), "HELLO THERE CHILD");
        ImGui::EndChild();
    }
}