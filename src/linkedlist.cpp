#include "linkedlist.h" // Include the header file for the LinkedList class
#include <iostream>     // For input/output operations

// Node Constructor
Node::Node(const Book &b) : book(b), next(nullptr) {}

// LinkedList Constructor: Initializes an empty list
LinkedList::LinkedList() : head(nullptr) {}

// LinkedList Destructor: Cleans up dynamically allocated memory
LinkedList::~LinkedList() {
    Node* current = head; // Start at the head of the list
    while (current) {     // Traverse the list
        Node* temp = current->next; // Save the next node
        delete current;             // Free memory for the current node
        current = temp;             // Move to the next node
    }
}

// Add a book to the beginning of the list
void LinkedList::add(const Book &book) {
    Node* newNode = new Node(book); // Create a new node for the book
    newNode->next = head;           // Point the new node to the current head
    head = newNode;                 // Update the head to the new node
}

// Remove a book from the list by its ISBN
void LinkedList::remove(const std::string &isbn) {
    Node* current = head;  // Start at the head of the list
    Node* prev = nullptr;  // Keep track of the previous node
    while (current) {      // Traverse the list
        if (current->book.getISBN() == isbn) { // Check if the ISBN matches
            if (prev) {
                prev->next = current->next; // Update the previous node's pointer
            } else {
                head = current->next;       // Update the head if the first node is removed
            }
            delete current; // Free memory for the removed node
            return;
        }
        prev = current;       // Move to the next node
        current = current->next;
    }
}

// Display all books in the linked list
void LinkedList::display() const {
    Node* current = head; // Start at the head of the list
    while (current) {     // Traverse the list
        std::cout << current->book.getTitle() << " by " << current->book.getAuthor()
                << " [ISBN: " << current->book.getISBN() << "] Availability: "
                << current->book.getAvailability() << std::endl;
        current = current->next; // Move to the next node
    }
}

// Find a book in the list by its title
Book* LinkedList::findByTitle(const std::string &title) {
    Node* current = head; // Start at the head of the list
    while (current) {     // Traverse the list
        if (current->book.getTitle() == title) { // Check if the title matches
            return &current->book; // Return a pointer to the book if found
        }
        current = current->next; // Move to the next node
    }
    return nullptr; // Return null if no book with the given title is found
}

// Find the first book in the list by an author
Book* LinkedList::findByAuthor(const std::string &author) {
    Node* current = head; // Start at the head of the list
    while (current) {     // Traverse the list
        if (current->book.getAuthor() == author) { // Check if the author matches
            return &current->book; // Return a pointer to the book if found
        }
        current = current->next; // Move to the next node
    }
    return nullptr; // Return null if no book by the given author is found
}