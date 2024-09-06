#include "ui/windowing/WindowState.hpp"



ActiveWindow WindowState::_window_state = USER_WINDOW;

std::function<bool(const std::string&)> WindowState::_open_file_callback = nullptr;
std::function<bool(const std::string&)> WindowState::_save_file_callback = nullptr;

ActiveWindow WindowState::getWindowState() { return _window_state; }

void WindowState::activateUserWindow()
{
    _window_state = USER_WINDOW;
}

void WindowState::activateFileMenuOpenFile()
{
    _window_state = FILE_MENU;
}

void WindowState::activateFileMenuSaveFile()
{
    _window_state = FILE_MENU;
}

bool WindowState::callOpenFileCallback(const std::string& filename)
{
    if (_open_file_callback != nullptr)
    {
        return _open_file_callback(filename);
    }
    return false;
}

bool WindowState::callSaveFileCallback(const std::string& filename)
{
    if (_save_file_callback != nullptr)
    {
        return _save_file_callback(filename);
    }
    return false;
}
