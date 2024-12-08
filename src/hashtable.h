#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "book.h"
#include <vector>
#include <string>

class HashTable {
private:
    struct Entry {
        std::string key;
        Book book;
        bool inUse;
        Entry();
    };

    std::vector<Entry> table;
    size_t capacity;
    size_t count;

    size_t hashFunc(const std::string &key) const;

public:
    HashTable(size_t cap = 101);

    void insert(const std::string &isbn, const Book &book);
    Book* get(const std::string &isbn);
    void remove(const std::string &isbn);
};

#endif // HASHTABLE_H