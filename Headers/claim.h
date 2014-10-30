/*
            ===== A Short Summary of the Claims System =====

In this system, claims are used for printing debug and note information.
This is done so that we can esily turn this information on and off throughout
the entire code base without having to manually comment outputs or look
through multiple files.

Claims are a simple call that requires two parameters, a message and a level

    + string message : The message that you want output to the user, this should

    + Severity level: The severity of the message, which will determine what happens
        after the claim has been printed

    + int tabs (default = 0) : This is an optional parameter which will add a number of
        tabs before the message is output, to make reading debug outputs from
        differeing function levels easier

Currently, there are four different severity levels:

    + kDebug : This level should be used when printing debug text for development, 
        this level can be turned off by changing DEBUG to true in this file

    + kNote : This is informative text and should be used to inform the user of things
        like program progression and echoing inputs

    + kWarning : This level should be used when the system encounters a problem that
        it will not cause a program crash, but should be noted by the user. This
        text writes to standard error but will not terminate the program

    + kError : This level should be used when the program encounters an error that it
        cannot tolerate, it will print to standard error and make a call to exit()

There is one other feature known as a wait claim, a call to wait_claim(...) requires a
message, but does not have a severity level. This claim will pause the running of your
program, output your message, and then resume the program only after prompted by user
input.
*/

#ifndef _CLAIM_H_
#define _CLAIM_H_

#include <string>
#include <sstream>

#define DEBUG true

using std::string;
using std::stringstream;

namespace Utilities {
    enum Severity{kDebug, kNote, kWarning, kError};

    /* Useful string functions */
    void to_lower(string& to_convert);

    /* JSON conversion functions */
    string bool_to_string(bool to_convert);
    string quote_string(string to_quote);

    /* Debugging */
    void wait_claim(string message, int tabs = 0);

    /* Message Helpers */
    string severity_string(Severity);

    /* Error reporting */
    void claim(string message, Severity level, int tabs = 0);
    void claim(char* message, Severity level, int tabs = 0);
    void claim(const char* message, Severity level, int tabs = 0);
    void claim(stringstream* message, Severity level, int tabs = 0);
}

#endif  //_CLAIM_H_
