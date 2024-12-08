#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "book.h"

struct Node {
    Book book;
    Node* next;
    Node(const Book &b);
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void add(const Book &book);
    void remove(const std::string &isbn);
    void display() const;

    Book* findByTitle(const std::string &title);
    Book* findByAuthor(const std::string &author);
};

#endif // LINKEDLIST_H