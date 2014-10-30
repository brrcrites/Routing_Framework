#include "../Headers/claim.h"
#include <stdlib.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::pair;

string Utilities::bool_to_string(bool to_convert) {
    if (to_convert) {
        return "true";
    }
    return "false";
}

//returns the string to_quote surrounded by quotes, unless the string is "null" 
string Utilities::quote_string(string to_quote) {
    if (to_quote == "null") {
        return to_quote;
    }
    return "\""+to_quote+"\"";
}

void Utilities::wait_claim(string message,int tabs) {
    if(DEBUG) {
        char proceed;
        for (int i = 0;i < tabs;i++) { cerr << '\t'; }
        cerr << message << endl;
        std::cin >> proceed;
        if (proceed == 'n') {
            exit(1);
        }
    }
}

void Utilities::claim(string message,Severity level,int tabs) {
    string severity_level = severity_string(level);
    switch(level) {
        case kWarning:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message << endl;
            break;
        case kError:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message << endl;
            exit(1);
        case kDebug:
            if(DEBUG) {
                for(int i = 0; i < tabs; i++) { cout << '\t'; }
                cout << severity_level << message << endl;
            }
            break;
        case kNote:
        default:
            for (int i = 0;i < tabs;i++) { cout << '\t'; }
            cout << severity_level << message << endl;
    }
}

void Utilities::claim(const char* message,Severity level,int tabs) {
    string severity_level = severity_string(level);
    switch(level) {
        case kWarning:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message << endl;
            break;
        case kError:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message << endl;
            exit(1);
        case kDebug:
            if(DEBUG) {
                for(int i = 0; i < tabs; i++) { cout << '\t'; }
                cout << severity_level << message << endl;
            }
            break;
        case kNote:
        default:
            for (int i = 0;i < tabs;i++) { cout << '\t'; }
            cout << severity_level << message << endl;
    }
}

void Utilities::claim(char* message,Severity level,int tabs) {
    string severity_level = severity_string(level);
    switch(level) {
        case kWarning:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message << endl;
            break;
        case kError:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message << endl;
            exit(1);
        case kDebug:
            if(DEBUG) {
                for(int i = 0; i < tabs; i++) { cout << '\t'; }
                cout << severity_level << message << endl;
            }
            break;
        case kNote:
        default:
            for (int i = 0;i < tabs;i++) { cout << '\t'; }
            cout << severity_level << message << endl;
    }
}

void Utilities::claim(stringstream* message,Severity level,int tabs) {
    string severity_level = severity_string(level);
    switch(level) {
        case kWarning:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message->str() << endl;
            break;
        case kError:
            for (int i = 0;i < tabs;i++) { cerr << '\t'; }
            cerr << severity_level << message->str() << endl;
            exit(1);
        case kDebug:
            if(DEBUG) {
                for(int i = 0; i < tabs; i++) { cout << '\t'; }
                cout << severity_level << message << endl;
            }
            break;
        case kNote:
        default:
            for (int i = 0;i < tabs;i++) { cout << '\t'; }
            cout << severity_level << message->str() << endl;
    }
}

string Utilities::severity_string(Severity level) {
    switch(level) {
        case kWarning:
            return "Warning: ";
        case kError:
            return "Error: ";
        case kDebug:
            return "Debug: ";
        case kNote:
        default:
            return "Note: ";
    }
}

void Utilities::to_lower(string& to_convert) {
    for (unsigned i = 0;i < to_convert.size();i++) {
        if (isupper(to_convert.at(i))) {
            tolower(to_convert.at(i));
        }
    }
}