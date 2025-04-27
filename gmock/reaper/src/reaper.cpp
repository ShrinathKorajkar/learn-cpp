#include "reaper.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string getItem(size_t index)
{
    if (index > 3) {
        throw out_of_range("Index " + to_string(index) + " is out of range. Some important words.");
    }
    return "Hello world!";
}

void doStuff(vector<uint8_t>* input)
{
    if (!input) {
        //cerr << "something gneric may or may not have once been null. Blowing up." << endl;
        cerr << "input is null. Blowing up." << endl;
        abort();
    }
}

void parseCommand(const string& /*command*/)
{
    cerr << "Line one" << endl;
    cerr << "Time to die" << endl;
    cerr << "last line" << endl;
    exit(4);
}

void stop()
{
    exit(0);
}
