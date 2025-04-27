template <typename T>
class MyClass;

template <typename T>
class MyClass
{
private:
    T data;

public:
    MyClass(T value) : data(value) {}
    template <typename U>
    friend void modifyData(MyClass<U> &obj, U value);
};

template <typename U>
void modifyData(MyClass<U> &obj, U value)
{
    obj.data = value;
}

int main()
{
    MyClass<int> myObject(42);
    modifyData(myObject, 99);
    return 0;
}
