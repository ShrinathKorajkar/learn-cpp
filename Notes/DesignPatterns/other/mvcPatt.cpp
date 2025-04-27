/*
    MVC (Model-View-Controller) Pattern:  ->  Separates an application into three interconnected components the Model
    (data and business logic), View (user interface), and Controller (handles user input and updates the Model and View).
*/

#include <iostream>
#include <string>
#include <vector>

// Model
class StudentModel
{
public:
    StudentModel(const std::string &name, int age) : name_(name), age_(age) {}

    const std::string &getName() const
    {
        return name_;
    }

    int getAge() const
    {
        return age_;
    }

    std::string name_;
    int age_;
};

// View
class StudentView
{
public:
    void printStudentDetails(const std::string &name, int age)
    {
        std::cout << "Student: ";
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

// Controller
class StudentController
{
public:
    StudentController(StudentModel *model, StudentView *view) : model_(model), view_(view) {}

    void updateView()
    {
        view_->printStudentDetails(model_->getName(), model_->getAge());
    }

    void setStudentName(const std::string &name)
    {
        model_->name_ = name;
    }

    void setStudentAge(int age)
    {
        model_->age_ = age;
    }

private:
    StudentModel *model_;
    StudentView *view_;
};

int main()
{
    // Create Model, View, and Controller
    StudentModel model("John", 20);
    StudentView view;
    StudentController controller(&model, &view);

    // Initial view
    controller.updateView();

    // Update Model data through the Controller
    controller.setStudentName("Alice");
    controller.setStudentAge(22);

    // Updated view
    controller.updateView();

    return 0;
}
