/* 
    Q: Program to fund all the prime numbers in array
    input  :-  arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    output :-  2, 3, 5, 7
*/
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

int *getAllPrimeUpto(int max){
    int *primes = malloc((max + 1) * sizeof(int));
    for(int i = 0; i <= max; i++){
        primes[i] = 1;
    }
    primes[0] = 0;
    primes[1] = 0;
    for(int i = 2; i * i <= max; i++){
        if(primes[i] == 1){
            for(int j = i * 2; j <= max; j += i){
                primes[j] = 0;
            }
        }
    }
    return primes;
}

bool isPrime(int num, int *allPrimes){
    return allPrimes[num] == 1;
}

void printPrimeNumbers(int *arr, int len){
    int max = arr[0];
    for(int i = 1; i < len; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    int *allPrime = getAllPrimeUpto(max);
    printf("Prime Numbers : ");
    for(int i = 0; i < len; i++){
        if(isPrime(arr[i], allPrime)){
            printf("%d  ", arr[i]);
        }
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(arr)/sizeof(arr[0]);
    printPrimeNumbers(arr, len);
    return 0;
}
