g++ -Iinclude  ./test/*.cpp ./src/*.cpp -Llib -ljsonlib -lcurl -o ./output/test -lgtest -lgtest_main -lgmock -lgmock_main -Wl,-rpath,lib
./output/test 
