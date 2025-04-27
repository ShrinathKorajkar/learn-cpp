#include "example.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    CLIENT *cl;
    intpair arg;
    int *result;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <hostname> <operation> <operand1> <operand2>\n", argv[0]);
        exit(1);
    }

    arg.a = atoi(argv[3]);
    arg.b = atoi(argv[4]);

    cl = clnt_create(argv[1], ARITH_PROG, ARITH_VERS, "udp");
    if (cl == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    switch (atoi(argv[2])) {
        case 1:
            result = add_1(&arg, cl);
            break;
        case 2:
            result = sub_1(&arg, cl);
            break;
        default:
            fprintf(stderr, "Invalid operation.\n");
            clnt_destroy(cl);
            exit(1);
    }

    if (result == NULL) {
        clnt_perror(cl, "RPC call failed");
        exit(1);
    }

    printf("Result: %d\n", *result);
    clnt_destroy(cl);
    return 0;
}
