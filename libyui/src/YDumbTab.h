/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:		YDumbTab.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YDumbTab_h
#define YDumbTab_h

#include "YSelectionWidget.h"

class YDumbTabPrivate;

/**
 * DumbTab: A very simple tab widget that can display and switch between a
 * number of tabs, but will only deliver the "user clicked on tab " event very
 * much like a PushButton does. Actually exchanging the content of the tab is
 * left to the application.
 *
 * DumbTab accepts a single child widget.
 **/
class YDumbTab : public YSelectionWidget
{
protected:
    /**
     * Constructor.
     **/
    YDumbTab( YWidget * parent );

public:
    /**
     * Destructor.
     **/
    virtual ~YDumbTab();
    
    /**
     * Returns a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * widgetClass() const { return "YDumbTab"; }

    /**
     * Add an item (a tab page).
     *
     * Reimplemented from YSelectionWidget.
     *
     * Derived classes can overwrite this function, but they should call this
     * base class function in the new implementation.
     **/
    virtual void addItem( YItem * item );

    /**
     * Set a property.
     * Reimplemented from YWidget.
     *
     * This method may throw exceptions, for example
     *   - if there is no property with that name
     *   - if the expected type and the type mismatch
     *   - if the value is out of range
     *
     * This function returns 'true' if the value was successfully set and
     * 'false' if that value requires special handling (not in error cases:
     * those are covered by exceptions).
     **/
    virtual bool setProperty( const string & propertyName,
			      const YPropertyValue & val );

    /**
     * Get a property.
     * Reimplemented from YWidget.
     *
     * This method may throw exceptions, for example
     *   - if there is no property with that name
     **/
    virtual YPropertyValue getProperty( const string & propertyName );

    /**
     * Return this class's property set.
     * This also initializes the property set upon the first call.
     *
     * Reimplemented from YWidget.
     **/
    virtual const YPropertySet & propertySet();

    /**
     * Get the string of this widget that holds the keyboard shortcut.
     *
     * Reimplemented from YSelectionWidget.
     **/
    virtual string shortcutString() { return ""; }

    /**
     * Set the string of this widget that holds the keyboard shortcut.
     *
     * Reimplemented from YSelectionWidget.
     **/
    virtual void setShortcutString( const string & str ) {}

    /**
     * Returns 'true' if this widget is stretchable in the specified dimension.
     * In this case, the stretchability of the single child is returned.
     *
     * Reimplemented from YWidget.
     **/
    virtual bool stretchable( YUIDimension dim ) const;

    /**
     * Descriptive label for debugging. Derived from this widget's only child
     * (if there is one). 
     **/
    virtual string debugLabel();
    
private:

    // Disable unwanted base class methods
    string label() const;
    virtual void setLabel( const string & newLabel ) {};
    

    ImplPtr<YDumbTabPrivate> priv;
};


#endif // YDumbTab_h
