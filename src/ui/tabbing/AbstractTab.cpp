#include "ui/tabbing/AbstractTab.hpp"

unsigned int AbstractTab::NEXT_ID = 0;

AbstractTab::AbstractTab(const std::string& tab_name)
    :_tab_name(tab_name), _unique_id(AbstractTab::NEXT_ID)
{
    AbstractTab::NEXT_ID++;
}

std::string AbstractTab::generateImGUITag()
{
    return _tab_name + "##" + std::to_string(_unique_id);
}
