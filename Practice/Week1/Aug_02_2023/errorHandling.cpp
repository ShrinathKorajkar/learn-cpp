#include <iostream>
#include <fstream>
using namespace std;

void customLog(string message)
{
    cout << "Custom log : " << message << endl;
}

int main()
{
    cerr << "Error: Cannot divide by zero" << endl;
    clog << "This is a log message" << endl;

    ofstream logFile("logfile.txt");
    logFile << "This is a log message." << endl;
    logFile.close();

    customLog("This is a custom log message.");
    return 0;
}