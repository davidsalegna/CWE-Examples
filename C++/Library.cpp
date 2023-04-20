#include <iostream>
#include <vector>
#include "Book.h"

//CWE-457: The books vector is initialized to a default value before it is used
std::vector<Book> books = {
    Book("The Great Gatsby", "F. Scott Fitzgerald", 2),
    Book("To Kill a Mockingbird", "Harper Lee", 3),
    Book("1984", "George Orwell", 4),
    Book("Pride and Prejudice", "Jane Austen", 1),
    Book("Wuthering Heights", "Emily Bronte", 2),
    Book("The Hobbit", "J.R.R. Tolkien", 3)
};

void checkOutBook(std::string title) {
    for (auto& book : books) {
        if (book.getTitle() == title) {
            if (book.getQuantity() > 0) {
                book.setQuantity(book.getQuantity() - 1);
                std::cout << "You have checked out \"" << book.getTitle() << "\" by " << book.getAuthor() << "." << std::endl;
            } else {
                std::cout << "Sorry, there are no more copies of \"" << book.getTitle() << "\" available." << std::endl;
            }
            return;
        }
    }
    std::cout << "Book not found." << std::endl;
}

void returnBook(std::string title) {
    for (auto& book : books) {
        if (book.getTitle() == title) {
            book.setQuantity(book.getQuantity() + 1);
            std::cout << "You have returned \"" << book.getTitle() << "\" by " << book.getAuthor() << "." << std::endl;
            return;
        }
    }
    std::cout << "Book not found." << std::endl;
}

int main() {
    std::string choice;
    std::string title;
    std::string type;

    std::cout << "Hello! Welcome to our library. We hope you enjoy your visit!\n";

    while (true) {
        std::cout << "What would you like to do?\n\t[1] Display available books\n\t[2] Check out a book\n\t[3] Return a book\n\t[4] Quit\nChoice:  ";
        std::cin >> choice;

        if (choice == "1") {
            std::cout << "Enter the title of the book: ";
            std::cin >> title;
            checkOutBook(title);
        } else if (choice == "2") {
            std::cout << "Enter the title of the book: ";
            std::cin >> title;
            returnBook(title);
        } else if (choice == "3") {
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}