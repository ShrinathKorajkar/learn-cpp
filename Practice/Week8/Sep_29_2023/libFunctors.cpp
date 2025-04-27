#include <iostream>
#include <functional>
#include <vector>
#include <set>

int main()
{
    // plus, minus, divides, multiplies, modulus, negate
    std::plus<int> add_functor;
    std::negate<int> negate_functor;
    std::cout << "add : " << add_functor(5, 3) << std::endl;
    std::cout << "neg : " << negate_functor(5) << std::endl;

    //
    // equal_to, not_equal_to, greater, less, greater_equal, less_equal   ->   return bool
    std::equal_to<int> equal_functor;
    std::cout << "Equal : " << equal_functor(5, 5) << std::endl;

    //
    // logical_and, or, not
    std::logical_and<bool> logicalFunctor;
    std::cout << "Logical : " << logicalFunctor(true, true) << std::endl;

    //
    // bit_and, or, not, xor
    std::bit_and<bool> bitFunctor;
    std::cout << "Bit : " << bitFunctor(5, 3) << std::endl;

    //
    // pointers
    int x = 5, y = 10;
    int *px = &x, *py = &y;

    std::less<void> less_functor;
    std::greater<void> greater_functor;

    std::cout << "less : " << less_functor(px, py) << std::endl;
    std::cout << "greater : " << greater_functor(px, py) << std::endl;

    //

    std::vector<int> numbers = {3, 1, 4, 1, 5, 9};
    std::sort(numbers.begin(), numbers.end(), std::less<int>()); // Ascending order
    std::set<int, std::greater<int>> descendingSet;              // Descending order

    return 0;
}
