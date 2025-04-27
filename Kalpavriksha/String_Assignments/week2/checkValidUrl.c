#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/*
    Q : Given Url check if it is valid. The URL have the format "protocol://host:port/path?query".
        where format for protocol = [https, http], host = www.hostname.com, port = [443, 80], path = string,
        query = any.
    input: https://www.example.com:443/login?username=johndoe&password=password123
    output: valid Url
*/

void substring(char *dest, char *source, int beg, int end)
{
    for (int i = beg; i < end; i++)
    {
        *dest++ = *(source + i);
    }
    *dest = '\0';
}

int searchfor(char *input, int beg, int end, char find)
{
    int i;
    for (i = beg; i < end; i++)
    {
        if (input[i] == find)
        {
            break;
        }
    }
    return i;
}

bool checkProtocol(char *protocol)
{
    if (strlen(protocol) < 4)
    {
        return false;
    }
    return strcmp(protocol, "http") == 0 || strcmp(protocol, "https") == 0;
}

bool checkHost(char *host)
{
    int length = strlen(host);
    if (length < 10)
    {
        return false;
    }
    char start[5], end[5];
    substring(start, host, 0, 4);
    substring(end, host, length - 4, length);

    return strcmp(start, "www.") == 0 && strcmp(end, ".com") == 0;
}

bool checkPort(char *port)
{
    if (strlen(port) < 2)
    {
        return false;
    }
    return atoi(port) == 80 || atoi(port) == 443;
}

bool checkPath(char *path)
{
    if (strlen(path) < 1)
    {
        return false;
    }
    int len = strlen(path);
    for (int i = 0; i < len; i++)
    {
        if (isdigit(path[i]))
        {
            return false;
        }
    }
    return true;
}

bool checkQuery(char *query)
{
    if (strlen(query) < 1)
    {
        return false;
    }
    return true;
}

int checkUrl(char *input)
{
    int current = 0;
    int length = strlen(input);
    char protocol[6];
    char host[20];
    char port[5];
    char path[20];
    char query[50];

    int next = searchfor(input, 0, length, ':');
    substring(protocol, input, current, next);
    current = next + 3;

    next = searchfor(input, current, length, ':');
    substring(host, input, current, next);
    current = ++next;

    next = searchfor(input, current, length, '/');
    substring(port, input, current, next);
    current = ++next;

    next = searchfor(input, current, length, '?');
    substring(path, input, current, next);
    substring(query, input, next + 1, length);

    return checkProtocol(protocol) && checkHost(host) && checkPort(port) && checkPath(path) && checkQuery(query);
}

int main()
{
    char input[100];
    scanf("%s", input);
    bool flag = checkUrl(input);
    if (flag)
    {
        printf("Valid URL");
    }
    else
    {
        printf("Invalid URL");
    }
    return 0;
}