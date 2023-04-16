#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
    private:
        std::string title;
        std::string author;
        int quantity;
        std::string type;

    public:
        Book(std::string title, std::string author, int quantity);
        std::string getTitle();
        std::string getAuthor();
        int getQuantity();
        void setQuantity(int quantity);
};

#endif