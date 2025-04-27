#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct linked_list
{
    int data;
    struct linked_list *next;
} list;

list *insertNode(list *inputList, int indata)
{
    list *temp = malloc(sizeof(list));
    temp->data = indata;
    temp->next = NULL;

    if (inputList == NULL)
    {
        inputList = temp;
        return inputList;
    }

    list *currNode = inputList;
    while (currNode->next != NULL)
    {
        currNode = currNode->next;
    }
    currNode->next = temp;
    return inputList;
}

list *takeInput(list *inputList, char *input)
{
    int i = 0;
    int len = strlen(input);
    for (i = 0; i < len; i++)
    {
        char number[10];
        int j = 0;
        if (isdigit(input[i]))
        {
            while (isdigit(input[i]))
            {
                number[j] = input[i];
                j++;
                i++;
            }
            number[j] = '\0';
            int data = atoi(number);
            inputList = insertNode(inputList, data);
        }
    }
    return inputList;
}

void takeInput2()
{
    char inp1[100], inp2[100];
    scanf("{%[^}] %*c : {%[^}] %*c", inp1, inp2);
    // printf("\n%s %s", inp1, inp2);
    char *token = strtok(inp1, ",");
    while (token != NULL)
    {
        printf("%s ", token);
        token = strtok(NULL, ",");
    }
    token = strtok(inp2, ",");
    while (token != NULL)
    {
        printf("%s ", token);
        token = strtok(NULL, ",");
    }
}

list *merge(list *mergedList, list *firstList, list *secondList)
{
    list *temp = mergedList;

    while (firstList != NULL && secondList != NULL)
    {
        list *firstNext = firstList->next;
        list *secondNext = secondList->next;

        mergedList->next = firstList;
        mergedList->next->next = secondList;

        firstList = firstNext;
        secondList = secondNext;
        mergedList = mergedList->next->next;
    }

    if (firstList != NULL)
    {
        mergedList->next = firstList;
    }
    else if (secondList != NULL)
    {
        mergedList->next = secondList;
    }
    mergedList = temp->next;
    return mergedList;
}

int main()
{
    list *firstList = NULL;
    list *secondList = NULL;
    list *mergedList = malloc(sizeof(list));
    mergedList->data = -1;
    mergedList->next = NULL;

    char input1[100], input2[100];
    scanf("%s : %s", input1, input2);
    firstList = takeInput(firstList, input1);
    secondList = takeInput(secondList, input2);

    mergedList = merge(mergedList, firstList, secondList);
    printf("{");
    while (mergedList->next != NULL)
    {
        printf("%d,", mergedList->data);
        mergedList = mergedList->next;
    }
    printf("%d}", mergedList->data);

    // takeInput2();

    return 0;
}
