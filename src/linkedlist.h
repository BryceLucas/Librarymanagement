#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "book.h" // Include the Book class definition

// Node structure for the linked list
struct Node {
    Book book;      // The book data stored in this node
    Node* next;     // Pointer to the next node in the linked list

    // Constructor to initialize a Node with a book object
    Node(const Book &b);
};

// LinkedList class definition
class LinkedList {
private:
    Node* head; // Pointer to the head (start) of the linked list

public:
    // Constructor to initialize an empty linked list
    LinkedList();

    // Destructor to clean up memory and prevent memory leaks
    ~LinkedList();

    // Adds a book to the beginning of the linked list
    void add(const Book &book);

    // Removes a book from the list by its ISBN
    void remove(const std::string &isbn);

    // Displays all books in the linked list (used for debugging or UI purposes)
    void display() const;

    // Finds a book in the linked list by its title
    Book* findByTitle(const std::string &title);

    // Finds the first book in the linked list by a specific author
    Book* findByAuthor(const std::string &author);
};

#endif // LINKEDLIST_H