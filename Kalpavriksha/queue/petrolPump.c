/*
    Q:  Given information about N petrol pumps (say arr[]) that are present in a circular path. 
        The information consists of the distance of the next petrol pump from the current one 
        (in arr[i][1]) and the amount of petrol stored in that petrol pump (in arr[i][0]). 
        Consider a truck with infinite capacity that consumes 1 unit of petrol to travel 1 unit distance.
        The task is to find the index of the first starting point such that the truck can visit
        all the petrol pumps and come back to that starting point.
        Return -1 if no such tour exists.
*/

#include <stdio.h>

typedef struct {
    int petrol;
    int distance;
}petrolPump;

int printTour(petrolPump p[], int n){
    int start = 0;
    int end = 1;
    int currPetrol = p[start].petrol - p[start].distance;
    while(end != start || currPetrol < 0){
        while(currPetrol < 0 && start != end){
            currPetrol -= p[start].petrol - p[start].distance;
            start = (start + 1) % n;
            if(start == n){
                return -1;
            }
        }
        currPetrol += p[end].petrol - p[end].distance;
        end = (end + 1) % n;
    }
    return start;
}

int main(int argc, char const *argv[])
{
    petrolPump p[] = {{6, 4}, {3, 6}, {7, 3}};
    int len = sizeof(p) / sizeof(p[0]);
    int start = printTour(p, len);
    if(start == -1){
        printf("No Solution");
    }else{
        printf("Start = %d\n", start);
    }
    return 0;
}
