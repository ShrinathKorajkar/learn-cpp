#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "queue.h"

bool searchString(const char *haystack, const char *needle);
void substring(char *dest, char *source, int beg, int end);
int differenceInTime(char *stopTime, char *startTime);
void fillLogQ(FILE *ptr, Queue *logQ);
int parseLogs(Queue *logQ, Queue *errQ);

#endif // PARSER_H
