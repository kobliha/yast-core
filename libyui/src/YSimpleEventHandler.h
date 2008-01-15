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

  File:		YSimpleEventHandler.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YSimpleEventHandler_h
#define YSimpleEventHandler_h


class YEvent;
class YWidget;


/**
 * @short Simple event handler suitable for most UIs.
 * This event handler keeps track of one single event that gets overwritten
 * when a new one arrives.
 **/
class YSimpleEventHandler
{
public:

    /**
     * Constructor.
     **/
    YSimpleEventHandler();

    /**
     * Destructor.
     *
     * If there is a pending event, it is deleted here.
     **/
    virtual ~YSimpleEventHandler();

    /**
     * Widget event handlers call this when an event occured that
     * should be the answer to a UserInput() / PollInput() (etc.) call.
     *
     * The UI assumes ownership of the event object that 'event' points to, so
     * the event MUST be created with new(). The UI is to take care to delete
     * the event after it has been processed. 
     *
     * If events are blocked (see blockEvents() ), the event sent with this
     * function will be ignored (but safely deleted - no memory leak).
     *
     * It is an error to pass 0 for 'event'.
     **/
    void sendEvent( YEvent * event );

    /**
     * Returns 'true' if there is any event pending for the specified widget.
     **/
    bool eventPendingFor( YWidget * widget ) const;

    /**
     * Returns the last event that isn't processed yet or 0 if there is none.
     *
     * This event handler keeps track of only one single (the last one) event.
     **/
    YEvent * pendingEvent() const { return _pending_event; }

    /**
     * Consumes the pending event. Sets the internal pending event to 0.
     * Does NOT delete the internal consuming event.
     *
     * The caller assumes ownership of the object this pending event points
     * to. In particular, he has to take care to delete that object when he is
     * done processing it.
     *
     * Returns the pending event or 0 if there is none.
     **/
    YEvent * consumePendingEvent();

    /**
     * Clears any pending event (deletes the corresponding object).
     **/
    void clear();

    /**
     * Block (or unblock) events. If events are blocked, any event sent with
     * sendEvent() from now on is ignored (and will get lost) until events are
     * unblocked again.
     **/
    void blockEvents( bool block = true );

    /**
     * Unblock events previously blocked. This is just an alias for
     * blockEvents( false) for better readability.
     **/
    void unblockEvents() { blockEvents( false ); }

    /**
     * Returns 'true' if events are currently blocked.
     **/
    bool eventsBlocked() const { return _events_blocked; }


protected:

    // Data members

    YEvent * 	_pending_event;
    bool	_events_blocked;
};




#endif // YSimpleEventHandler_h