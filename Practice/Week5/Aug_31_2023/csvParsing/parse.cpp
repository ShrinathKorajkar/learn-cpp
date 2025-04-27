#include <iostream>
#include <fstream>
#include "csv.h"

int main()
{
    io::CSVReader<2> in("./file.csv");
    in.read_header(io::ignore_extra_column, "EMPID", "NAME");
    int id;
    std::string name;
    while (in.read_row(id, name))
    {
        std::cout << id << ": " << name << std::endl;
    }

    std::ofstream fout("./file.csv", std::ios::out | std::ios::app);
    if (fout.is_open())
    {
        fout << 1337 << ", Shri 2, 22, 2023" << std::endl;
        fout.close();
    }
}