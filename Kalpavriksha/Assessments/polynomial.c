#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
/*
    Q2: Add two polynomials
    input: 2y^6 + 5y^4
            4y^4 + 2y^2
    output: 2y^6 + 8y^4 + 5y^2
*/

typedef struct Polynomial
{
    int coefficient;
    char variable;
    int power;
    struct Polynomial *next;
} Polynomial;

typedef struct LinkedList
{
    Polynomial *head;
    Polynomial *tail;
} LinkedList;

void init(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

Polynomial *createNode(int coefficient, char variable, int power)
{
    Polynomial *newPolynomial = malloc(sizeof(Polynomial));
    newPolynomial->variable = variable;
    newPolynomial->coefficient = coefficient;
    newPolynomial->power = power;
    newPolynomial->next = NULL;
    return newPolynomial;
}

bool isEmpty(LinkedList *list)
{
    return list->head == NULL;
}

void insertNode(LinkedList *list, int coefficient, char variable, int power)
{
    Polynomial *newNode = createNode(coefficient, variable, power);
    if (isEmpty(list))
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    list->tail->next = newNode;
    list->tail = list->tail->next;
}

void createList(char *input, LinkedList *list)
{
    char *token = strtok(input, "+");
    while (token)
    {
        int coefficient = 1, power = 1;
        char variable = 'n';
        if (strlen(token) == 1)
        {
            if (isdigit(token[0]))
            {
                coefficient = token[0] - '0';
            }
            else
            {
                variable = token[0];
            }
        }
        else if (strlen(token) == 2)
        {
            coefficient = token[0] - '0';
            variable = token[1];
        }
        else if (strlen(token) == 3)
        {
            variable = token[0];
            power = token[2] - '0';
        }
        else
        {
            coefficient = token[0] - '0';
            variable = token[1];
            power = token[3] - '0';
        }
        // printf("%d %c %d ", coefficient, variable, power);
        insertNode(list, coefficient, variable, power);
        token = strtok(NULL, "+");
    }
}

void printList(LinkedList *list)
{
    Polynomial *current = list->head;
    while (current)
    {
        if (current->variable == 'n')
        {

            printf("%d", current->coefficient);
        }
        else
        {
            printf("%d%c^%d+", current->coefficient, current->variable, current->power);
        }
        current = current->next;
    }
    printf("\n");
}

void addList(LinkedList *result, LinkedList *list1, LinkedList *list2)
{
    Polynomial *list1Poly = list1->head;
    Polynomial *list2Poly = list2->head;
    while (list1Poly && list2Poly)
    {
        int coefficient = 1;
        if (list1Poly->power == list2Poly->power && list1Poly->variable == list2Poly->variable)
        {
            coefficient = list1Poly->coefficient + list2Poly->coefficient;
            insertNode(result, coefficient, list1Poly->variable, list1Poly->power);
            list1Poly = list1Poly->next;
            list2Poly = list2Poly->next;
        }
        else if (list1Poly->power > list2Poly->power)
        {
            insertNode(result, list1Poly->coefficient, list1Poly->variable, list1Poly->power);
            list1Poly = list1Poly->next;
        }
        else
        {
            insertNode(result, list2Poly->coefficient, list2Poly->variable, list2Poly->power);
            list2Poly = list2Poly->next;
        }
    }
    while (list1Poly)
    {
        insertNode(result, list1Poly->coefficient, list1Poly->variable, list1Poly->power);
    }
    while (list2Poly)
    {
        insertNode(result, list2Poly->coefficient, list2Poly->variable, list2Poly->power);
    }
}

void destroyList(LinkedList *list)
{
    Polynomial *current = list->head;
    while (current)
    {
        Polynomial *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main()
{
    LinkedList *list1 = malloc(sizeof(LinkedList));
    LinkedList *list2 = malloc(sizeof(LinkedList));
    LinkedList *list3 = malloc(sizeof(LinkedList));
    init(list1);
    init(list2);
    init(list3);

    char inp1[100];
    printf("Enter the 1 equation : ");
    scanf("%s", inp1);

    createList(inp1, list1);

    char inp2[100];
    printf("\nEnter the 2 equation : ");
    scanf("%s", inp2);

    createList(inp2, list2);

    addList(list3, list1, list2);
    printList(list3);

    destroyList(list1);
    destroyList(list2);
    destroyList(list3);
    return 0;
}
