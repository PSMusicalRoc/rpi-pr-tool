#pragma once

#include "NonClosableTab.hpp"

class TestNonClosableTab: public NonClosableTab
{
public:
    TestNonClosableTab(const std::string& tab_name);
    void displayContents() override;
};