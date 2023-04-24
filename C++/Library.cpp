#include <iostream>
#include <vector>
#include <string>
#include "Book.h"

// CWE-480: Proper usage of operators can be observed throughout the code, including arithmetic and logical operators.
//CWE-457: The books vector is initialized to a default value before it is used
std::vector<Book> books = {
    Book("The Great Gatsby", "F. Scott Fitzgerald", 3),
    Book("To Kill a Mockingbird", "Harper Lee", 2),
    Book("1984", "George Orwell", 2),
    Book("Fahrenheit 451", "Ray Bradbury", 1)
};

void displayBooks()
{
    for (auto& book : books)
    {
        std::cout << "\"" << book.getTitle() << "\" by " << book.getAuthor() << " (" << book.getQuantity() << " available)" << std::endl;
    }
}

void checkOutBook(std::string title)
{
    // CWE-480: Proper usage of operators can be observed throughout the code, particularly arithmetic and logical operators.
    // CWE-483: Proper block delimitation can also be observed throughout the code, particularly with if statements.
    for (auto& book : books)
    {
        if (book.getTitle() == title)
        {
            if (book.getQuantity() > 0)
            {
                book.setQuantity(book.getQuantity() - 1);
                std::cout << "You have checked out \"" << book.getTitle() << "\" by " << book.getAuthor() << "." << std::endl;
            }
            else
            {
                std::cout << "Sorry, there are no copies of \"" << book.getTitle() << "\" available." << std::endl;
            }
            return;
        }
    }
    std::cout << "Sorry, we do not have \"" + title + "\" in our library." << std::endl;
}

void returnBook(std::string title)
{
    for (auto& book : books)
    {
        if (book.getTitle() == title)
        {
            // CWE-120: Check to make sure the value provided in setQuantity is within the size of its (integer) buffer.
            // CWE-125: Checking within the size of a buffer doubles as checking within the bounds of it.
            if (book.getQuantity() - INT32_MAX != 0)
            {
                book.setQuantity(book.getQuantity() + 1);
            }
            std::cout << "You have returned \"" << book.getTitle() << "\". Thank you!" << std::endl;
            return;
        }
    }
    std::cout << "Book not found." << std::endl;
}

int main()
{
    int choice = 0;
    bool usingLibrary = true;
    std::string input;

    std::cout << "Hello! Welcome to our library. We hope you enjoy your visit!\n";

    while (usingLibrary)
    {
        std::cout << "What would you like to do?\n\t[1] Display available books\n\t[2] Check out a book\n\t[3] Return a book\n\t[4] Quit\nChoice:  ";
        std::cin >> input;
        try
        {
            choice = stoi(input);
        }
        // CWE-210: If an error occurs, there are no specifics given on why an error occurred other than "invalid choice" at the end of the switch.
        catch(const std::exception& e)
        {
            choice = 0;
        }

        switch (choice)
        {
            case 1:
                displayBooks();
                break;
            case 2:
                std::cout << "Enter the title of the book: ";
                std::cin.ignore();
                getline(std::cin, input);
                checkOutBook(input);
                break;

            case 3:
                std::cout << "Enter the title of the book: ";
                std::cin.ignore();
                getline(std::cin, input);
                returnBook(input);
                break;
        
            case 4:
                usingLibrary = false;
                break;
        
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}