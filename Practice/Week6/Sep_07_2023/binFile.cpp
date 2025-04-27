#include <iostream>
#include <fstream>

class Info
{
    char name;
    int age;

public:
    Info() : name('s'), age(0) {}
    Info(const char name, int age) : name(name), age(age) {}

    void serialize(std::fstream &ofs) const
    {
        ofs.write(reinterpret_cast<const char *>(this), sizeof(*this));
    }

    void deserialize(std::fstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(*this));
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

int main()
{
    std::fstream file("../files/binary.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        Info info1('s', 22);
        Info info2('r', 22);

        file << info1 << info2;

        std::streampos writePos = file.tellp();

        file.seekg(0, std::ios::beg);
        while (file >> info1)
        {
            std::cout << info1;
        }
        file.close();
    }

    return 0;
}