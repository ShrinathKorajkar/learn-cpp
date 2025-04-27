#include <stdio.h>
#include <alloca.h> // not part of C standard

int main()
{
    int n = 10;         // Size determined at runtime
    int stack_array[n]; // Allocate memory on the stack

    for (int i = 0; i < n; i++)
    {
        stack_array[i] = i;
        printf("%d ", stack_array[i]);
    }
    printf("\n");

    //
    int n2 = 10;                                         // Size determined at runtime
    int *stack_array2 = (int *)alloca(n2 * sizeof(int)); // Allocate memory on the stack

    for (int i = 0; i < n2; i++)
    {
        stack_array2[i] = i;
        printf("%d ", stack_array2[i]);
    }
    printf("\n");

    return 0;
}
