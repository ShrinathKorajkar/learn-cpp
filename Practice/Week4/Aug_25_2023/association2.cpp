#include <iostream>
#include <string>
#include <vector>

// Forward declaration of the Book class
class Book;

// Author class
class Author
{
private:
    std::string name;
    std::vector<Book *> books; // Association with Book class

public:
    Author(const std::string &name) : name(name) {}

    void addBook(Book *book)
    {
        books.push_back(book);
    }

    void displayBooks()
    {
        std::cout << "Books by " << name << ":\n";
        for (Book *book : books)
        {
            std::cout << "- " << book->getTitle() << std::endl;
        }
    }
};

// Book class
class Book
{
private:
    std::string title;
    Author *author; // Association with Author class

public:
    Book(const std::string &title, Author *author) : title(title), author(author)
    {
        author->addBook(this); // Register this book with the author
    }

    std::string getTitle() const
    {
        return title;
    }
};

int main()
{
    // Create author and books
    Author author("John Doe");
    Book book1("Book 1", &author);
    Book book2("Book 2", &author);

    // Display books by the author
    author.displayBooks();

    return 0;
}
