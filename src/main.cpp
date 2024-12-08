#include "book.h"          // Header file for the Book class
#include "linkedlist.h"    // Header file for the LinkedList class
#include "hashtable.h"     // Header file for the HashTable class
#include <iostream>        // For input and output
#include <limits>          // For handling input stream limits

int main() {
    // Initialize a linked list to store books
    LinkedList bookList;

    // Initialize a hash table for fast lookups by ISBN
    HashTable bookTable;

    // Create and add books to the system
    Book book1(1, "Test Book", "John Doe", "123-ABC", "Available");
    Book book2(2, "Another Book", "Jane Smith", "456-DEF", "Available");

    // Add books to the linked list
    bookList.add(book1);
    bookList.add(book2);

    // Insert books into the hash table using their ISBN as the key
    bookTable.insert("123-ABC", book1);
    bookTable.insert("456-DEF", book2);

    // Prompt the user to choose a search method
    std::string choice;
    std::cout << "Search by ISBN, Title, or Author? (isbn/title/author): ";
    std::cin >> choice;

    // Handle search by ISBN
    if (choice == "isbn") {
        std::string isbn;
        std::cout << "Enter ISBN: ";
        std::cin >> isbn;

        // Use the hash table for a quick lookup by ISBN
        Book* result = bookTable.get(isbn);
        if (result) {
            // Book found
            std::cout << "Book found: " << result->getTitle() 
                    << " by " << result->getAuthor() << std::endl;
        } else {
            // No book found with the given ISBN
            std::cout << "No book found with that ISBN.\n";
        }

    // Handle search by Title
    } else if (choice == "title") {
        std::string title;
        std::cout << "Enter Title: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::getline(std::cin, title); // Allow multi-word input for the title

        // Use the linked list to find the book by title
        Book* result = bookList.findByTitle(title);
        if (result) {
            // Book found
            std::cout << "Book found: " << result->getTitle() 
                    << " by " << result->getAuthor() << std::endl;
        } else {
            // No book found with the given title
            std::cout << "No book found with that title.\n";
        }

    // Handle search by Author
    } else if (choice == "author") {
        std::string author;
        std::cout << "Enter Author: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::getline(std::cin, author); // Allow multi-word input for the author

        // Use the linked list to find books by the author
        Book* result = bookList.findByAuthor(author);
        if (result) {
            // Book(s) found by the author
            std::cout << "Book by " << result->getAuthor() << ": " 
                      << result->getTitle() << std::endl;
        } else {
            // No books found by the given author
            std::cout << "No books found by that author.\n";
        }

    // Handle invalid search option
    } else {
        std::cout << "Invalid search option.\n";
    }

    return 0; // Exit the program
}
