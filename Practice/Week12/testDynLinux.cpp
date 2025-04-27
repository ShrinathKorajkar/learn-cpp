#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <iomanip>
#include <malloc.h>
#include <cctype>

/*
if char -> second array metadata starts from 24th byte (0 based)
if int -> 40th byte, then 56, 72, 88 byte
after metadata, 8 bytes are empty then memory for next array starts
Allocations are rounded up to the nearest multiple of 16.
metadata - 0x21, 0x31, 0x41 ... (0010 0001, 0011 0001, 0100 0001 ...)
*/

void printMemoryDump(uint8_t *start, uint8_t *end)
{
    intptr_t totalBytes = end - start;
    std::cout << "\n--- Memory Dump (" << totalBytes << " bytes) ---\n";

    for (intptr_t i = 0; i < totalBytes; ++i)
    {
        uint8_t byte = *(start + i);
        std::cout << "Byte " << std::setw(3) << i
                  << " | Addr: " << static_cast<void *>(start + i)
                  << " | Hex: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte)
                  << " | Char: " << std::dec << (std::isprint(byte) ? static_cast<char>(byte) : '.') << "\n";
    }
}

int main()
{
    int *intArray = static_cast<int *>(malloc(5 * sizeof(int)));
    char *charArray = static_cast<char *>(malloc(10 * sizeof(char)));

    for (int i = 0; i < 5; ++i)
        intArray[i] = i;
    for (int i = 0; i < 10; ++i)
        charArray[i] = 'A' + i;

    size_t sizeIntArray = malloc_usable_size(intArray);
    size_t sizeCharArray = malloc_usable_size(charArray);

    std::cout << "intArray  Address : " << static_cast<void *>(intArray) << "\n";
    std::cout << "charArray Address : " << static_cast<void *>(charArray) << "\n";
    std::cout << "intArray  Usable  : " << sizeIntArray << " bytes\n";
    std::cout << "charArray Usable  : " << sizeCharArray << " bytes\n";

    intptr_t addrDiff = reinterpret_cast<uint8_t *>(charArray) - reinterpret_cast<uint8_t *>(intArray);
    std::cout << "Address Difference: " << addrDiff << " bytes\n";

    uint8_t *start = reinterpret_cast<uint8_t *>(intArray) - 30;
    uint8_t *end = reinterpret_cast<uint8_t *>(charArray) + sizeCharArray + 30;

    printMemoryDump(start, end);

    free(intArray);
    free(charArray);

    return 0;
}
