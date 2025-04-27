#include <iostream>
#include <vector>
#include <list>

template <typename T, template <typename> class Container>
class MyTemplate
{
public:
    Container<T> data;

    MyTemplate()
    {
        if (std::is_same<T, int>::value)
        {
            std::cout << "MyTemplate" << std::endl;
        }
    }
};

int main()
{
    MyTemplate<int, std::vector> myVecTemplate;

    MyTemplate<double, std::list> myListTemplate;

    return 0;
}
