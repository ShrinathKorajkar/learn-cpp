/*
    Pointers :- store memory address of variable. indirectly access memory
    memory size :- 8 bytes.
    smart pointers :- deallocate memory by themselves. memory header
    RAII (Resource Acquisition Is Initialization)
*/
#include <iostream>
#include <memory>

void arrays()
{
    // 1 D array
    int *ptr = new int[5];
    for (int i = 0; i < 5; i++)
    {
        *(ptr + i) = i;
    }
    for (int i = 0; i < 5; i++)
    {
        std::cout << *(ptr + i) << " ";
    }
    std::cout << std::endl;

    // 2 D array
    int **mat = new int *[2];
    for (int i = 0; i < 2; i++)
    {
        *(mat + i) = new int[2];
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            *(*(mat + i) + j) = i + j;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            std::cout << *(*(mat + i) + j) << " ";
        }
        std::cout << std::endl;
    }

    // deleting dynamic memory
    for (int i = 0; i < 2; i++)
    {
        delete[] *(mat + i);
    }
    delete[] mat;
    delete[] ptr;
}

void closeFile(FILE *file)
{
    if (file)
    {
        fclose(file);
        std::cout << "File closed." << std::endl;
    }
}

void smartPointers()
{
    // Unique
    std::unique_ptr<int> ptr = std::make_unique<int>();
    std::unique_ptr<int> ptr2(new int(42));
    std::unique_ptr<int[]> arrayPtr(new int[10]);
    std::unique_ptr<FILE, decltype(&closeFile)> filePtr(fopen("file.txt", "w"), &closeFile);

    std::unique_ptr<int[]> transferredPtr = std::move(arrayPtr);

    *ptr = 43;
    std::cout << "Unique Ptr : " << *ptr << std::endl;

    ptr.swap(ptr2);

    int *rawPtr = ptr.get();
    int *rawPtr2 = ptr2.release();
    std::cout << "Raw Ptr using get : " << *rawPtr << std::endl;
    std::cout << "Raw Ptr using release : " << *rawPtr2 << std::endl;

    ptr.reset();
    ptr2.reset(new int(19)); // resetting  with new obj
    std::cout << std::endl;

    //
    //
    // Shared
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(500);
    std::shared_ptr<int> sharedPtr2 = sharedPtr;

    std::cout << "Shared 1 : " << *sharedPtr << std::endl;
    std::cout << "Shared 2 : " << *sharedPtr2 << std::endl;
    std::cout << "Use Count : " << sharedPtr.use_count() << std::endl;

    sharedPtr.reset();

    std::cout << "Is Unique : " << sharedPtr2.unique() << std::endl;
    std::cout << std::endl;

    //
    //
    // Weak Pointer

    std::weak_ptr<int> weakPtr = sharedPtr;

    // Creating shared_ptr from weak_ptr temporarily
    if (auto sharedFromWeak = weakPtr.lock())
    {
        std::cout << "Shared from weak: " << *sharedFromWeak << std::endl;
    }
    else
    {
        std::cout << "Shared pointer expired." << std::endl;
    }
    if (weakPtr.expired())
    {
        std::cout << "Weak pointer expired." << std::endl;
    }
}

int main()
{
    int a = 10;
    int *p = nullptr; //  NULL can also be used
    p = &a;
    std::cout << *p << std::endl;

    smartPointers();

    return 0;
}