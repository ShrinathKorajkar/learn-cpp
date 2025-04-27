/*
    string is a class in sting headerfile
    cin = read word and leave \n in input buffer
    getline = read line and discard the \n from input buffer

*/
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name; // empty string
    cout << "enter name : ";
    cin >> name;
    cout << name << "\n";

    string add = "hello " + name;
    cout << add << endl;

    cout << "enter line : ";
    getline(cin, name);
    cout << name << endl;

    char arr[] = "hello world";
    string array(arr);
    cout << arr << endl;

    string copy(10, 'a');
    cout << copy << endl;

    //
    // # METHODS
    string hello = "hello shri";

    cout << "Size() : " << hello.size();
    cout << "\nLength() : " << hello.length();

    if (hello.empty())
    {
        cout << "\nString is empty";
    }
    else
    {
        cout << "\nString is not empty";
    }
    cout << "\nMaxSize() : " << hello.max_size();

    hello.clear();
    cout << "\nclear() : " << hello;
    hello = "hello Again";

    //
    // erase(position, noOfChar)
    hello.erase(4);
    cout << "\nerase(x) : " << hello;
    hello = "hello Again";
    hello.erase(4, 3);
    cout << "\nerase(x, y) : " << hello;

    hello.push_back('l');
    cout << "\nPushBack('x') : " << hello;

    hello.pop_back();
    cout << "\nPopBack()" << hello;

    hello.append(" Once Again");
    cout << "\nAppend("
            ") : "
         << hello;

    hello.insert(0, "Shri ");
    cout << "\ninsert(x, "
            ") : "
         << hello;

    hello.replace(hello.find("Shri"), 4, "Ram");
    cout << "\nreplace(x, y, "
            ") : "
         << hello;

    hello.resize(15, '*');

    //
    // #  SEARCHING AND MANIP
    string search = "Shri in ITT";
    const char *charArray = search.c_str();
    cout << "\ncStr() : " << charArray;

    const char *dataPtr = search.data();
    cout << "\ndata() : " << dataPtr;

    string subString = search.substr(8);
    cout << "\nsubstr(x) : " << subString;

    subString = search.substr(0, 4);
    cout << "\nsubstr(x, y) : " << subString;

    int result = search.compare(subString);
    if (result == 0)
    {
        cout << "\nStrings equal";
    }
    else if (result < 0)
    {
        cout << "\nStr1 is smaller than 2";
    }
    else
    {
        cout << "\nStr1 is smaller than 2";
    }

    //
    // FIND - find, rfind, find_first_of, find_last_of, find_first_not_of, find_last_not_of
    string mainStr = "Shri rocks. Shri always rocks";

    size_t found = mainStr.find("rocks"); // finds first occ
    if (string::npos != found)
    {
        cout << "\nFound at : " << found;
    }

    found = mainStr.find_first_of("hadf"); // find first occ of any letter in hadf
    cout << "\nfindFirstOf() : " << found;

    found = mainStr.rfind("rocks"); // last position of string
    cout << "\nrfind() : " << found;

    found = mainStr.find_first_not_of("Shi"); // find any letter not in shi
    cout << "\nfindFirstNotOf : " << found;

    //
    // STRING CONVERSION
    string number = "123";

    int value = stoi(number);
    long long llvalue = stoi(number);
    long lvalue = stol(number);
    cout << "\nvalue : " << value << "\nlvalue : " << lvalue << "\nllvalue : " << llvalue;

    // stof, stod, stold

    value = 4321;
    string conv = to_string(value);
    cout << "\ntoString() : " << conv;

    string lower = "abcd";
    string upper = lower;
    for (char &c : upper)
    {
        c = toupper(c);
    }
    cout << "\nlower : " << lower << "\nUpper : " << upper;

    for (auto it = lower.begin(); it != lower.end(); ++it)
    {
        std::cout << *it << " ";
    }

    std::cin >> std::ws; // Skip leading whitespaces

    cout << endl;
    return 0;
}