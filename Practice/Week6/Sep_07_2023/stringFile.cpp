#include <iostream>
#include <fstream>
#include <cstring>

class Info
{
    std::string name;
    int age;

public:
    Info() : name(""), age(0) {}
    Info(const char *name, int age) : name(name), age(age) {}

    void serialize(std::fstream &ofs) const
    {
        int nameSize = name.size();
        ofs.write(reinterpret_cast<const char *>(&nameSize), sizeof(int));
        ofs.write(name.c_str(), nameSize);
        ofs.write(reinterpret_cast<const char *>(&age), sizeof(int));
    }

    void deserialize(std::fstream &ifs)
    {
        int nameSize;
        ifs.read(reinterpret_cast<char *>(&nameSize), sizeof(int));
        char buffer[nameSize];
        ifs.read(buffer, nameSize);
        name = std::string(buffer, nameSize);
        ifs.read(reinterpret_cast<char *>(&age), sizeof(int));
    }

    friend std::fstream &operator<<(std::fstream &ofs, const Info &obj)
    {
        obj.serialize(ofs);
        return ofs;
    }

    friend std::fstream &operator>>(std::fstream &ifs, Info &obj)
    {
        obj.deserialize(ifs);
        return ifs;
    }

    friend std::ostream &operator<<(std::ostream &ost, const Info &info)
    {
        ost << info.name << " : " << info.age << std::endl;
        return ost;
    }
};

// bool isValidName(std::string_view name)
// {
//     return std::ranges::all_of(name, [](char ch)
//                                { return (std::isalpha(ch) || std::isspace(ch)); });
// }

int main()
{
    std::fstream file("../files/binary.bin", std::ios::binary | std::ios::in | std::ios::out);
    if (file.is_open())
    {
        Info info1("Shri", 22);
        Info info2("Ram", 22);

        file << info1;
        file << info2;

        file.seekg(0, std::ios::beg);
        Info infoRead;
        while (file >> infoRead) // while(!file.eof())  |  while(file) -> with ifstream
        {
            std::cout << infoRead;
        }
        file.close(); // if not closed automatically destruct called
    }

    return 0;
}
