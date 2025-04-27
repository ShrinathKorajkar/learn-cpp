/*
    Q: Majority Element :- element that appears more than n/2 times.
        find the majority element
    input: arr[] = {2, 3, 3}
    output: 3
*/

#include <stdio.h>

int majorityElement(int *nums, int numSize){
    int elem = nums[0];
    int count = 1;
    for(int i = 1; i < numSize; i++){
        if(nums[i] == elem){
            count++;
        }else{
            count--;
        }
        if(count == 0){
            elem = nums[i];
            count++;
        }
    }
    count = 0;
    for(int i = 0; i < numSize; i++){
        if(nums[i] == elem){
            count++;
        }
    }
    if(count > numSize/2){
        return elem;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int nums[] = {2, 2, 1, 1, 1, 2, 2};
    int result = majorityElement(nums, 7);
    if(result == -1){
        printf("Majority Element not found");
    }else{
        printf("Majority Elem : %d", result);
    }
    return 0;
}

