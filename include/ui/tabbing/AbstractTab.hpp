#pragma once

#include <string>

/**
 * The base Tab interface, used for iterating
 * over a user-defined number of tabs.
 * 
 * @author Tim Bishop
 */
class ITab
{
public:
    /**
     * Renders the contents of a given tab. The
     * specific behavior is defined by the individual
     * subclass.
     */
    virtual void render() = 0;
};


/**
 * A subclass of the Tab interface, contains some
 * concrete implementations for things every tab
 * should be using (like a unique identifier!)
 */
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
