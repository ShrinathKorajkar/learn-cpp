#include <iostream>
#include "bankDatabase.h"

void filldb(BankDatabase &database)
{
    database.connect();
    database.addAccount(Account(1001, "Shri", 1000.0, 123456, 15, 12, 2024, 1234));
    database.addAccount(Account(1002, "Ram", 2000.0, 123457, 15, 12, 2024, 4123));
    database.addAccount(Account(1003, "Sham", 3000.0, 123458, 15, 12, 2024, 4312));
    database.addAccount(Account(1004, "Radha", 4000.0, 123459, 15, 12, 2024, 4321));
    database.addAccount(Account(1005, "Rani", 5000.0, 123450, 15, 12, 2024, 1324));
    database.addAccount(Account(1006, "Ramu", 6000.0, 123451, 15, 12, 2024, 1342));
    database.addAccount(Account(1007, "Balram", 7000.0, 123452, 15, 12, 2024, 1243));
    database.addAccount(Account(1008, "Ravan", 8000.0, 123453, 15, 12, 2024, 1423));
    database.addAccount(Account(1009, "Krishna", 9000.0, 123454, 15, 12, 2024, 1432));
}

int main()
{
    BankDatabase database;

    filldb(database);
    return 0;
}