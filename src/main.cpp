#include "book.h"
#include "linkedlist.h"
#include "hashtable.h"
#include <iostream>
#include <limits>

int main() {
    LinkedList bookList;
    HashTable bookTable;

    // Create and insert some books
    Book book1(1, "Test Book", "John Doe", "123-ABC", "Available");
    Book book2(2, "Another Book", "Jane Smith", "456-DEF", "Available");

    bookList.add(book1);
    bookList.add(book2);

    bookTable.insert("123-ABC", book1);
    bookTable.insert("456-DEF", book2);

    std::string choice;
    std::cout << "Search by ISBN, Title, or Author? (isbn/title/author): ";
    std::cin >> choice;

    if (choice == "isbn") {
        std::string isbn;
        std::cout << "Enter ISBN: ";
        std::cin >> isbn;

        Book* result = bookTable.get(isbn);
        if (result) {
            std::cout << "Book found: " << result->getTitle() << " by " << result->getAuthor() << std::endl;
        } else {
            std::cout << "No book found with that ISBN.\n";
        }
    } else if (choice == "title") {
        std::string title;
        std::cout << "Enter Title: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, title);

        Book* result = bookList.findByTitle(title);
        if (result) {
            std::cout << "Book found: " << result->getTitle() << " by " << result->getAuthor() << std::endl;
        } else {
            std::cout << "No book found with that title.\n";
        }
    } else if (choice == "author") {
        std::string author;
        std::cout << "Enter Author: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, author);

        Book* result = bookList.findByAuthor(author);
        if (result) {
            std::cout << "Book by " << result->getAuthor() << ": " << result->getTitle() << std::endl;
        } else {
            std::cout << "No books found by that author.\n";
        }
    } else {
        std::cout << "Invalid search option.\n";
    }

    return 0;
}
