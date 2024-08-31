#pragma once

#include <string>

class ITab
{
public:
    virtual void render() = 0;
};


class AbstractTab: public ITab
{
private:
    /** The next unique ID in the sequence */
    static unsigned int NEXT_ID;

protected:
    /** The name of the tab (ie. What is displayed) */
    std::string _tab_name;

    /** The unique ID of this tab */
    unsigned int _unique_id;

    /** Constructor for subclasses */
    AbstractTab(const std::string& tab_name);

    /** virtual destructor */
    virtual ~AbstractTab() {}

    /** A helper function to generate the ImGUI ID */
    std::string generateImGUITag();
};
