#pragma once

#include <string>
#include <functional>

enum ActiveWindow {
    USER_WINDOW = 1,
    FILE_MENU
};

class WindowState
{
private:
    static ActiveWindow _window_state;
    
    static std::function<bool(const std::string&)> _open_file_callback;
    static std::function<bool(const std::string&)> _save_file_callback;

public:
    const std::string FILE_MENU_IMGUI_ID = "File Menu";
    
    /**
     * Returns the current window state (used
     * in main.cpp to render specific windows)
     */
    static ActiveWindow getWindowState();

    /**
     * Sets the current window state to show
     * the user window (where the user inputs
     * data and whatnot), handling closing the
     * FileMenu if necessary.
     */
    static void activateUserWindow();
    
    /**
     * Sets the current window state to show
     * the file menu, and configures it such
     * that the opened menu will have the logic
     * for opening a file.
     */
    static void activateFileMenuOpenFile();
    
    /**
     * Sets the current window state to show
     * the file menu, and configures it such
     * that the opened menu will have the logic
     * for saving a file;
     */
    static void activateFileMenuSaveFile();
    
    static bool callOpenFileCallback(const std::string& filename);
    static bool callSaveFileCallback(const std::string& filename);
};