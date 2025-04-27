#include <iostream>

class MyContainer
{
private:
    int data[5] = {1, 2, 3, 4, 5};

public:
    class Iterator
    {
    private:
        int *ptr;

    public:
        using value_type = int;
        using pointer = int *;
        using reference = int &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator(int *p) : ptr(p) {}

        reference operator*() const
        {
            return *ptr;
        }

        Iterator &operator++()
        {
            ++ptr;
            return *this;
        }

        bool operator==(const Iterator &other) const
        {
            return ptr == other.ptr;
        }

        bool operator!=(const Iterator &other) const
        {
            return ptr != other.ptr;
        }
    };

    Iterator begin()
    {
        return Iterator(data);
    }

    Iterator end()
    {
        return Iterator(data + 5);
    }
};

int main()
{
    MyContainer myContainer;

    for (auto it = myContainer.begin(); it != myContainer.end(); ++it)
    {
        std::cout << *it << " ";
    }

    return 0;
}
