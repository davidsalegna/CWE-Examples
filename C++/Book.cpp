#include "Book.h"

Book::Book(std::string title, std::string author, int quantity) {
    this->title = title;
    this->author = author;
    this->quantity = quantity;
    this->type = type;
}

std::string Book::getTitle() {
    return title;
}

std::string Book::getAuthor() {
    return author;
}

int Book::getQuantity() {
    return quantity;
}

void Book::setQuantity(int quantity) {
    this->quantity = quantity;
}