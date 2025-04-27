#include <iostream>
#include <string>

// Subject interface that both the RealSubject and Proxy classes implement
class Image
{
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// RealSubject class that represents the real object (the actual image)
class RealImage : public Image
{
public:
    RealImage(const std::string &filename) : filename_(filename)
    {
        loadFromDisk();
    }

    void display() override
    {
        std::cout << "Displaying " << filename_ << std::endl;
    }

private:
    void loadFromDisk()
    {
        std::cout << "Loading " << filename_ << " from disk" << std::endl;
    }

    std::string filename_;
};

// Proxy class that provides a surrogate for RealImage
class ImageProxy : public Image
{
public:
    ImageProxy(const std::string &filename) : filename_(filename), realImage_(nullptr) {}

    void display() override
    {
        if (realImage_ == nullptr)
        {
            realImage_ = new RealImage(filename_);
        }
        realImage_->display();
    }

    ~ImageProxy()
    {
        if (realImage_ != nullptr)
        {
            delete realImage_;
        }
    }

private:
    std::string filename_;
    RealImage *realImage_;
};

int main()
{
    Image *realImage = new RealImage("sample.jpg");
    realImage->display();
    delete realImage;

    Image *imageProxy = new ImageProxy("sample.jpg");
    imageProxy->display();
    delete imageProxy;

    return 0;
}
