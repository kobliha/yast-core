/*---------------------------------------------------------------------\
|                                                                      |
|                      __   __    ____ _____ ____                      |
|                      \ \ / /_ _/ ___|_   _|___ \                     |
|                       \ V / _` \___ \ | |   __) |                    |
|                        | | (_| |___) || |  / __/                     |
|                        |_|\__,_|____/ |_| |_____|                    |
|                                                                      |
|                               core system                            |
|                                                        (C) SuSE GmbH |
\----------------------------------------------------------------------/

   File:       YCPDebugger.h

   Author:     Arvin Schnell <arvin@suse.de>
   Maintainer: Arvin Schnell <arvin@suse.de>

/-*/
// -*- c++ -*-

/*
 * Debugger for YCP
 */

#ifndef YCPDebugger_h
#define YCPDebugger_h

#include <string>
#include <vector>

#include "ycp/y2log.h"
#include "ycp/YCPElement.h"

class YCPDebugger
{
public:
    
    /**
     * Constructor for debugger. The parameter determines whether to
     * block (in the first debug call) until the frontend connects
     * or not.
     */
    YCPDebugger (bool);
    
    /**
     * Destructor for debugger.
     */
    ~YCPDebugger ();
    
    /**
     * Enum of entrypoints for the function debug.
     */
    enum EntryPoint { Interpreter, Block };
    
    /**
     * Main debug function. It is called in YCode::evaluate
     * and YBlock::evaluate.
     */
    void debug (EntryPoint, const YCPElement &);
    
private:
    
    /**
     * The command received last.
     */
    string last_command;
    
    /**
     * Block (in the first debug call) until the frontend connects.
     */
    bool wait_for_frontend;
    
private:
    
    /**
     * Data structure for a position in the source code.
     */
    struct Position
    {
	string file;
	int line;
	
	void setpos (const string &, int);
    };
    
    /**
     * Data structure for a breakpoint.
     */
    struct Breakpoint : public Position
    {
	bool tmpinactive;
    };
    
    /**
     * List of breakpoints.
     */
    vector <Breakpoint> breakpoints;
    
    /**
     * Adds a breakpoint to the list of breakpoints.
     */
    void add_breakpoint (const string &, int);
    
    /**
     * Deletes a breakpoint from the list of breakpoints. Return false if
     * no matching breakpoint was found.
     */
    bool delete_breakpoint (const string &, int);
    
    /**
     * Checks if the given position does matches a breakpoint and returns
     * true if so.
     */
    bool check_breakpoints (const string &, int);
    
    /**
     * Prints a list of all breakpoints.
     */
    void list_breakpoints ();
    
    /**
     * Prints the current source file.
     */
    void list_source (const char *);
    
    /**
     * Creates the socket we are listening on.
     */
    void create_socket ();
    
    /**
     * Checks if data arrived on our socket. The parameter determines whether
     * to block until data arrives or not.
     */
    void check_socket (bool);
    
    /**
     * The socket we are listening on.
     */
    int sock;
    
    /**
     * The file descriptor we are communication on. Note: We only
     * allow one debugger to be connected.
     */
    int fd;
    
    /**
     * Reads a line from the file descriptor. The parameter determines
     * whether to block or not.
     */
    string read_line (bool) const;
    
    /**
     * Writes a line to the file descriptor.
     */
    void write_line (const char *, ...) const
	__attribute__ ((format (printf, 2, 3)));
    
    /**
     * Writes the prompt to the file descriptor.
     */
    void write_prompt () const;
    
    /**
     * Handles a command from the frontend. The return value specifies whether
     * the execution should continue or not.
     */
    bool handle_command (const string &, const YCPElement &elem);
    
    /**
     * Stop execution at the next possible point.
     */
    bool single_mode;
    
    /**
     * Stop execution if the level is smaller than or equal to the hold_level.
     */
    int hold_level;
    
    /**
     * Stop execution if execution leaves this position.
     */
    Position leave_position;
    
    /**
     * The frontend wants to detach from the debugger.
     */
    bool close_request;
    
    /**
     * Structure to hold some user settings that control the behavior
     * of the debugger.
     */
    struct Settings
    {
	Settings () { reset (); }
	void reset ();
	
	bool ignorescr;
	bool printtoken;
    };
    
    /**
     * The user settings.
     */
    Settings settings;
    
    /**
     * Prints a single variable.
     */
    bool print_variable (const string &);
    
    /**
     * Prints the entire variable scope.
     */
    void print_scope ();

    /**
     * Used to ignore the calls to "_fullname", which the user does not
     * want to debug and most important the filename is wrong during
     * these calls.
     */
    bool ignore (EntryPoint, const YCPElement &);
};

#endif // YCPDebugger_h
