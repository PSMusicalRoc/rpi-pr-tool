#pragma once

#include "AbstractTab.hpp"

class NonClosableTab: public AbstractTab
{
protected:
    NonClosableTab(const std::string& tab_name);

public:
    void render() override;
    virtual void displayContents() = 0;
};
