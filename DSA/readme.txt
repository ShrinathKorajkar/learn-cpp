compile using g++.exe build
run using .\filename

TODO:
1. Solid Principles
2. Design Patterns
3. DSA
4. QT

Approach:
    1. Bit manipulation
        - a ^ a = 0
        - 0 ^ a = a
    2. If array size = n, then total subarrays can be formed = n(n+1)/2
    3. Two or more pointers
    4. Use constant space to store

Notes
    - O(n!) will be in getting all permutations, travelling salesman prob, backtrack to all possible options, Nqueens brute force
    - O(n^2) : n + n-1 + n-2 ... 1 = (n * (n + 1)) / 2 = n^2 + n 
    - O(logN) : n/2^0 + n/2^1 .... n/2^x, where n/2^x = 1 => n = 2^x => x = log n
    - O(nlogN) : Gredy alogs, sorting
    - O(2^n) : recursion - 2^0 + 2^1 + 2^2 ... 2^n-1 => a(r^n - 1)/r-1 => 2^n
    - recurrence relation, total rec calls * total work in each call
    - Space in recursion : depth of call stack or recursion tree *+ auxiliary space in each call
    - fibonaci actual = O(1.618^n)
    - 1sec = 10^8 operations in competetive code
    - n > 10^8, 2^26 -> O(logN), O(1)
    - n <= 10^8, 2^26 -> O(n)
    - n <= 10^6, 2^19 -> O(nlogN)
    - n <= 10^4, 2^13 -> O(n^2)
    - n <= 500 -> O(n^3)
    - n <= 25 -> O(2^n)
    - n <= 12 -> O(n!)
    - Any number n in decimal has logN + 1 numbers in its binary representation
    - Binary search - start + (end - start)/2 (will not give mem overflow)

std::to_string(int val)
std::reverse(a.begin(), a.end())
std::to_lower(char)
std::isalnum(char)
std::swap(char, char)
std::sort(begin(), end())
s.resize()
s.find*()
s.substr(start, end)
s.erase(start, length)

Modulo Arithmetics
    1. (x + y) % m = (x % m) + (y % m)
    2. (x - y) % m = (x % m) - (y % m) 
    3. (x * y) % m = (x % m) * (y % m)
