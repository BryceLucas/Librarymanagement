#include "linkedlist.h"
#include <iostream>

Node::Node(const Book &b) : book(b), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
}

void LinkedList::add(const Book &book) {
    Node* newNode = new Node(book);
    newNode->next = head;
    head = newNode;
}

void LinkedList::remove(const std::string &isbn) {
    Node* current = head;
    Node* prev = nullptr;
    while (current) {
        if (current->book.getISBN() == isbn) {
            if (prev) prev->next = current->next;
            else head = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void LinkedList::display() const {
    Node* current = head;
    while (current) {
        std::cout << current->book.getTitle() << " by " << current->book.getAuthor()
                << " [ISBN: " << current->book.getISBN() << "] Availability: "
                << current->book.getAvailability() << std::endl;
        current = current->next;
    }
}

Book* LinkedList::findByTitle(const std::string &title) {
    Node* current = head;
    while (current) {
        if (current->book.getTitle() == title) {
            return &current->book;
        }
        current = current->next;
    }
    return nullptr;
}

Book* LinkedList::findByAuthor(const std::string &author) {
    Node* current = head;
    while (current) {
        if (current->book.getAuthor() == author) {
            return &current->book;
        }
        current = current->next;
    }
    return nullptr;
}