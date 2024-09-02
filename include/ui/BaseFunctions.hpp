#pragma once

#include <string>

namespace ImCustom {

    /**
     * Puts text centered in a window.
     * 
     * @param text The text to be centered
     * @param center_x If true, centers the text
     * on the x axis
     * @param center_y If true, centers the text
     * on the y axis
     * 
     * @return See the return value of ImGui::Text()
     */
    void CenteredText(const std::string& text, bool center_x = false, bool center_y = false);

}