#pragma once

#include "AbstractTab.hpp"

/**
 * Base class for a Non-closable tab. This overrides
 * the render() method to account for creating a
 * tab that doesn't close, but gives the user the
 * virtual displayContents() method to define the
 * actual contents of the tab.
 * 
 * @author Tim Bishop
 */
class NonClosableTab: public AbstractTab
{
protected:
    /**
     * Constructor for NonClosableTab - really just
     * here for polymorphism purposes
     * 
     * @param tab_name The name to display on the
     * tab's title bar.
     */
    NonClosableTab(const std::string& tab_name);

public:
    void render() override;

    /**
     * User-defined contents for subclasses of NonClosableTab.
     * This is where all contents of the actual tab page will
     * be defined.
     */
    virtual void displayContents() = 0;
};
