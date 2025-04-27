#include <iostream>
#include <string>

/*
    Builder Pattern  ->  Separates the construction of a complex object from its representation,
    allowing the same construction process to create different representations. This is useful
    when an object has a large number of possible configurations.
*/

// Product class representing a computer
class Computer
{
    std::string cpu_;
    std::string ram_;
    std::string storage_;
    std::string graphicsCard_;

public:
    void setCPU(const std::string &cpu) { cpu_ = cpu; }
    void setRAM(const std::string &ram) { ram_ = ram; }
    void setStorage(const std::string &storage) { storage_ = storage; }
    void setGraphicsCard(const std::string &graphicsCard) { graphicsCard_ = graphicsCard; }
    void displayInfo() const
    {
        std::cout << "CPU: " << cpu_ << std::endl;
        std::cout << "RAM: " << ram_ << std::endl;
        std::cout << "Storage: " << storage_ << std::endl;
        std::cout << "Graphics Card: " << graphicsCard_ << std::endl;
    }
};

// Abstract Builder interface
class ComputerBuilder
{
public:
    virtual void buildCPU() = 0;
    virtual void buildRAM() = 0;
    virtual void buildStorage() = 0;
    virtual void buildGraphicsCard() = 0;
    virtual Computer getResult() const = 0;
};

// Concrete Builder for a high-end gaming computer
class HighEndGamingComputerBuilder : public ComputerBuilder
{
    Computer computer_;

public:
    void buildCPU() override { computer_.setCPU("Intel Core i9-10900K"); }
    void buildRAM() override { computer_.setRAM("32GB DDR4 3600MHz"); }
    void buildStorage() override { computer_.setStorage("1TB NVMe SSD + 2TB HDD"); }
    void buildGraphicsCard() override { computer_.setGraphicsCard("NVIDIA GeForce RTX 3090"); }
    Computer getResult() const override { return computer_; }
};

// Director class responsible for constructing a computer
class ComputerDirector
{
    ComputerBuilder *builder_;

public:
    void setBuilder(ComputerBuilder *builder) { builder_ = builder; }
    Computer constructComputer()
    {
        builder_->buildCPU();
        builder_->buildRAM();
        builder_->buildStorage();
        builder_->buildGraphicsCard();
        return builder_->getResult();
    }
};

int main()
{
    ComputerDirector director;
    HighEndGamingComputerBuilder gamingBuilder;

    director.setBuilder(&gamingBuilder);
    Computer gamingComputer = director.constructComputer();

    std::cout << "High-End Gaming Computer:" << std::endl;
    gamingComputer.displayInfo();

    return 0;
}
