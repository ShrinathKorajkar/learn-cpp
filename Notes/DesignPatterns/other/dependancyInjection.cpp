/*
    Dependency Injection Pattern  ->  Provides a way to supply dependencies (objects or values) to a class
    instead of the class creating them itself. This improves testability and flexibility.
*/

#include <iostream>
#include <string>

// Dependency (Service)
class Logger
{
public:
    void log(const std::string &message)
    {
        std::cout << "Log: " << message << std::endl;
    }
};

// Class that depends on Logger through Dependency Injection
class ProductService
{
public:
    ProductService(Logger *logger) : logger_(logger) {}

    void createProduct(const std::string &name)
    {
        // Create product logic
        logger_->log("Product created: " + name);
    }

private:
    Logger *logger_;
};

int main()
{
    // Create Logger and ProductService instances
    Logger logger;
    ProductService productService(&logger);

    // Use ProductService with injected Logger
    productService.createProduct("New Product");

    return 0;
}
