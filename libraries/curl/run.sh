g++ -Iinclude main.cpp ./src/*.cpp -Llib -ljsonlib -lcurl -o ./output/main -Wl,-rpath,lib
./output/main