#include <iostream>
#include <stdio.h>

void my_init() __attribute__((constructor));
void my_init()
{
    printf("Before main\n");
    exit(0);
}

int main()
{
    printf("Inside main\n");
    return 0;
}
