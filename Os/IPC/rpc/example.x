/* rpc_example.x */
program ARITH_PROG {
    version ARITH_VERS {
        int ADD(intpair) = 1;
        int SUB(intpair) = 2;
    } = 1;
} = 0x20000001;

/*
rpcgen -C rpc_example.x // server side stubs
rpcgen -C rpc_example.x // client side stubs
gcc -o rpc_server rpc_server.c rpc_example_svc.c rpc_example_xdr.c -lnsl
gcc -o rpc_client rpc_client.c rpc_example_clnt.c rpc_example_xdr.c -lnsl

// 1 terminal
./rpc_server


// 2 terminal
./rpc_client localhost 1 10 5   # Add 10 + 5
./rpc_client localhost 2 15 7   # Subtract 15 - 7


*/
