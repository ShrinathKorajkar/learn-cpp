/*
    Q: A System records every swipe, capturing the firest swipe of an Id as in,
       second as out, third as in etc.. Given an array of N ids denoting N swipes
       throughout the day. find the maximum no of people in the office at any time.
    input: arr[] = {1, 2, 2, 1}
    output: 2
*/
#include <stdio.h>

#define MAX_N 1000

int main() {
    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        int n;
        scanf("%d", &n);

        int arr[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        int set[MAX_N] = {0};
        int maxPeople = 0;

        int count = 0;
        for (int i = 0; i < n; i++) {
            if (set[arr[i]] == 1) {
                set[arr[i]] = 0;
                count--;
            } else {
                set[arr[i]] = 1;
                count++;
                maxPeople = (count > maxPeople) ? count : maxPeople;
            }
        }

        printf("%d\n", maxPeople);
    }

    return 0;
}
