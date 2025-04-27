#include <iostream>
#include <memory>
#include <vector>

class Bamboo
{
public:
    Bamboo() { std::cout << "Bamboo" << std::endl; }
    ~Bamboo() { std::cout << "~Bamboo" << std::endl; }
    void printBamboo() { std::cout << "print Bamboo" << std::endl; }
};
int main()
{
    std::unique_ptr<Bamboo> bamboo1(new Bamboo()); // explicit call no implicit
    std::unique_ptr<Bamboo> bamboo2 = std::make_unique<Bamboo>();
    bamboo1->printBamboo();
    bamboo2->printBamboo();
    std::unique_ptr<Bamboo> movedBamboo = std::move(bamboo1);

    //
    {
        std::shared_ptr<Bamboo> shared;
        {
            std::shared_ptr<Bamboo> boo1 = std::make_shared<Bamboo>();
            shared = boo1;
        }
        std::cout << "Boo1 died" << std::endl;
    }
    std::cout << "Shared died" << std::endl;

    //
    {
        std::weak_ptr<Bamboo> weak;
        {
            std::shared_ptr<Bamboo> boo2 = std::make_shared<Bamboo>();
            weak = boo2;
        }
        std::cout << "Boo2 died" << std::endl;
    }
    std::cout << "weak died" << std::endl;

    //
    std::shared_ptr<Bamboo> boo3 = std::move(bamboo2);
    std::weak_ptr<Bamboo> boo4 = boo3;

    std::cout << "use count : " << boo3.use_count() << std::endl;

    boo3.reset();
    if (boo3)
    {
        std::cout << "boo3 is valid" << std::endl;
    }
    else
    {
        std::cout << "boo3 is invalid" << std::endl;
    }

    if (boo4.expired())
    {
        std::cout << "boo4 is expired" << std::endl;
    }
    else
    {
        std::cout << "boo4 is not expired" << std::endl;
    }

    if (auto sharedFromWeak = boo4.lock())
    {
        sharedFromWeak->printBamboo();
    }
    else
    {
        std::cout << "boo4 is expired" << std::endl;
    }

    bamboo1.swap(movedBamboo);
    if (bamboo1)
    {
        std::cout << "bamboo1 is alive" << std::endl;
    }

    auto *rawptr = boo3.get();
    Bamboo *released = bamboo1.release();

    auto lambda = [](Bamboo *boo)
    { std::cout << "custom deleter" << std::endl;
    delete boo; };
    std::unique_ptr<Bamboo, decltype(lambda)> boo5(new Bamboo(), lambda);

    delete released;
    delete rawptr;

    return 0;
}