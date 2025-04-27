#include <iostream>
#include <cstdlib>
#include <cstdint>

#include <malloc.h>

int main()
{
    // Allocate two arrays of different sizes
    int *arr1 = (int *)malloc(10 * sizeof(int)); // 40 bytes
    int *arr2 = (int *)malloc(20 * sizeof(int)); // 80 bytes

    // Print pointer addresses
    std::cout << "Address of arr1: " << static_cast<void *>(arr1) << "\n";
    std::cout << "Address of arr2: " << static_cast<void *>(arr2) << "\n";

    // Print the difference in addresses (in bytes)
    intptr_t diff = reinterpret_cast<uint8_t *>(arr1) - reinterpret_cast<uint8_t *>(arr2);
    std::cout << "Difference between arr2 and arr1 (bytes): " << diff << "\n";

    // size_t size = malloc_usable_size(arr1); // on linux

    size_t size = _msize(arr1); // on windows
    std::cout << "Usable size of arr1: " << size << "\n";

    // Cleanup
    free(arr1);
    free(arr2);

    return 0;
}
