#include <iostream>

class Complex
{
    double real, imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex &other) // binary, without param it will be unary
    {
        return Complex(this->real + other.real, this->imag + other.imag);
    }
    Complex operator++(int) // post-inc
    {
        Complex temp = *this;
        this->real++;
        this->imag++;
        return temp;
    }
    Complex operator++() // pre-inc
    {
        this->real++;
        this->imag++;
        return *this;
    }

    void operator()()
    {
        std::cout << real << " + " << imag << "i" << std::endl;
    }

    void display()
    {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

int main()
{
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);
    Complex sum = c1 + c2;
    sum++;
    ++sum;
    sum.display();
    c1.display();
    c2.display();

    sum();
    return 0;
}
