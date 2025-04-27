#include <iostream>
#include <sys/stat.h>

int main()
{
    const char *filename = "../files/example.txt";
    struct stat fileStat;

    if (stat(filename, &fileStat) == 0)
    {
        std::cout << "File Size: " << fileStat.st_size << " bytes" << std::endl;
        std::cout << "File Permissions: " << (fileStat.st_mode & 0777) << std::endl;
        std::cout << "Last Access Time: " << ctime(&fileStat.st_atime);
        std::cout << "Last Modification Time: " << ctime(&fileStat.st_mtime);
    }

    return 0;
}
