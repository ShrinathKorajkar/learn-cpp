#include "example.h"
#include <stdio.h>

int *add_1_svc(intpair *argp, struct svc_req *rqstp) {
    static int result;
    result = argp->a + argp->b;
    return &result;
}

int *sub_1_svc(intpair *argp, struct svc_req *rqstp) {
    static int result;
    result = argp->a - argp->b;
    return &result;
}

int main(int argc, char *argv[]) {
    registerrpc(ARITH_PROG, ARITH_VERS, ADD, add_1_svc, xdr_intpair, xdr_int);
    registerrpc(ARITH_PROG, ARITH_VERS, SUB, sub_1_svc, xdr_intpair, xdr_int);
    svc_run();
    return 0;
}
