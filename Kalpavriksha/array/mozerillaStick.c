#include <stdio.h>
/*
    Q: For each extra mozzarella stick you eat, you earn 30 rupees. given minimum sticks, sticks per plate,
       rupees you earned. calculate the maximum plates of sticks you ate
    input:  4               =>    testcases
            7 5 30          =>    X Y R (for all test cases in new line)
            16 5 0
            15 9 120
            23 1 2130
    output: 2
            4
            3
            94

*/
int main() {
    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        int X, Y, R;
        scanf("%d %d %d\n", &X, &Y, &R);

        int extra = R / 30;
        int total = X + extra;
        int noOfPlates = total / Y;

        if (total % Y != 0) {
            noOfPlates++;
        }

        printf("%d\n", noOfPlates);
    }

    return 0;
}
