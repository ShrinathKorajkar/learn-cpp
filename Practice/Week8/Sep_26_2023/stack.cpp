#include <iostream>
#include <stack>

int main()
{
    std::stack<int> myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    std::cout << "Top element: " << myStack.top() << std::endl;

    myStack.pop();

    std::cout << "After pop, top element: " << myStack.top() << std::endl;
    std::cout << "Stack size: " << myStack.size() << std::endl;
    return 0;
}
