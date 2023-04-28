#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include "Book.h"

// CWE-480: Proper usage of operators can be observed throughout the code, including arithmetic and logical operators.
// CWE-457: The books vector is initialized to a default value before it is used
// CWE-482: Proper use of comparing vs assigning
std::vector<Book> availableBooks = {
    Book("The Great Gatsby", "F. Scott Fitzgerald", 3),
    Book("To Kill a Mockingbird", "Harper Lee", 2),
    Book("1984", "George Orwell", 2),
    Book("Fahrenheit 451", "Ray Bradbury", 1)
};

std::vector<Book> checkedOutBooks = {};

void displayBooks()
{
    for (auto& book : availableBooks)
    {
        // CWE-595: Proper comparing of object values instead of references
        std::cout << "\"" << book.getTitle() << "\" by " << book.getAuthor() << " (" << book.getQuantity() << " available)" << std::endl;
    }
}

void checkOutBook(std::string title)
{
    // CWE-480: Proper usage of operators can be observed throughout the code, particularly arithmetic and logical operators.
    // CWE-483: Proper block delimitation can also be observed throughout the code, particularly with if statements.
    for (auto& book : availableBooks)
    {   
        // CWE-482: Proper use of comparing vs assigning
        // CWE-595: Proper comparing of object values instead of references
        if (book.getTitle() == title)
        {
            if (book.getQuantity() > 0)
            {
                book.setQuantity(book.getQuantity() - 1);
                // Add book to checkedOutBooks
                checkedOutBooks.push_back(Book(book.getTitle(), book.getAuthor(), 1));
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
    for (auto& book : availableBooks)
    {   
        // CWE-482: Proper use of comparing vs assigning
        // CWE-595: Proper comparing of object values instead of references
        if (book.getTitle() == title)
        {
            // CWE-120: Check to make sure the value provided in setQuantity is within the size of its (integer) buffer.
            // CWE-125: Checking within the size of a buffer doubles as checking within the bounds of it.
            // CWE-482: Proper use of comparing vs assigning
            // CWE-595: Proper comparing of object values instead of references
            if (book.getQuantity() - INT32_MAX != 0)
            {
                // CWE-595: Proper comparing of object values instead of references
                book.setQuantity(book.getQuantity() + 1);
            }
            // CWE-482: Proper use of comparing vs assigning
            bool flag = false;
            // CWE-595: Proper comparing of object values instead of references
            for (int i = 0; i < ((int) checkedOutBooks.size()); i++) {
                // CWE-482: Proper use of comparing vs assigning
                if (checkedOutBooks[i].getTitle().compare(title) == 0) {
                    checkedOutBooks.erase(checkedOutBooks.begin() + i);
                    // CWE-482: Proper use of comparing vs assigning
                    flag = true;
                }
            }
            if (flag) {
                book.setQuantity(book.getQuantity() + 1);
                std::cout << "You have returned \"" << book.getTitle() << "\". Thank you!" << std::endl;
            } else {
                std::cout << "Sorry, you don't have \"" << title << "\" checked out." << std::endl;
            }
            return;
        }
    }
    std::cout << "Book not found." << std::endl;
}

void printReceipt()
{
    // CWE-482: Proper use of comparing vs assigning
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::tm returnDate = *now;
    returnDate.tm_mday += 14;
    std::mktime(&returnDate);

    // Open output file stream
    std::ofstream outFile("receipt.txt");

    // CWE-397: Throws a specific error (not just exception)
    // CWE-595: Proper comparing of object values instead of references
    if (!(outFile.is_open())) {
        std::runtime_error("Could not open file");
    }

    // Write receipt header
    outFile << "RECEIPT:\n\n";

    // Write book titles and return date
    for (auto& book : checkedOutBooks) {
        // CWE-595: Proper comparing of object values instead of references
        outFile << book.getTitle() << "\nRETURN BY: "
                << returnDate.tm_year + 1900 << "/"
                << returnDate.tm_mon + 1 << "/"
                << returnDate.tm_mday << "\n\n";
    }

    // Close output file stream
    // CWE-910: Proper use of expired file descriptor
    outFile.close();
}


int main()
{
    // CWE-482: Proper use of comparing vs assigning
    int choice = 0;
    bool usingLibrary = true;
    std::string input;

    std::cout << "Hello! Welcome to our library. We hope you enjoy your visit!\n";

    while (usingLibrary)
    {
        std::cout << "What would you like to do?\n\t[1] Display available books\n\t[2] Check out a book\n\t[3] Return a book\n\t[4] Print receipt\n\t[5] Quit\nChoice:  ";
        std::cin >> input;
        try
        {
            // CWE-482: Proper use of comparing vs assigning
            // CWE-704: Proper use of converting or casting
            choice = stoi(input);
        }
        // CWE-210: If an error occurs, there are no specifics given on why an error occurred other than "invalid choice" at the end of the switch.
        catch(const std::exception& e)
        {
            // CWE-482: Proper use of comparing vs assigning
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
                // CWE-248: Catches potential exception
                try {  
                    printReceipt();
                    std::cout << "Your receipt has been successfully printed!\n";
                }
                // CWE-396: Uses specific error (not just exception) 
                // CWE-460: Program is in a safe state once exception is caught
                catch (const std::runtime_error& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            case 5:
                // CWE-482: Proper use of comparing vs assigning
                usingLibrary = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}
