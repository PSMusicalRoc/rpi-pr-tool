#include "ui/BaseFunctions.hpp"

#include <imgui.h>

void ImCustom::CenteredText(const std::string& text, bool center_x, bool center_y)
{
    ImVec2 window_size = ImGui::GetWindowContentRegionMax();
    ImVec2 text_size = ImGui::CalcTextSize(text.c_str());

    if (center_x)
    {
        ImGui::SetCursorPosX((window_size.x - text_size.x)/2);
    }
    if (center_y)
    {
        ImGui::SetCursorPosY((window_size.y - text_size.y)/2);
    }
    ImGui::Text(text.c_str());
}