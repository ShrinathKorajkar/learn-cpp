#include <iostream>
using namespace std;
/*
    preprocessor  =>  g++ -E source.cpp -o preprocessed_code.i
    compiler      =>  g++ -S preprocessed_code.i -o assembly_code.s
    assembler     =>  g++ -c assembly_code.s -o object_file.o
    linker        =>  g++ object_file.o -o executable
*/

int main()
{
    std::cout << "hello World" << std::endl;
    return 0;
}