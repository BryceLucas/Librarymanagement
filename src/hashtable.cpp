#include "hashtable.h"

HashTable::Entry::Entry() : inUse(false) {}

HashTable::HashTable(size_t cap) : capacity(cap), count(0) {
    table.resize(capacity);
}

size_t HashTable::hashFunc(const std::string &key) const {
    std::hash<std::string> hasher;
    return hasher(key) % capacity;
}

void HashTable::insert(const std::string &isbn, const Book &book) {
    size_t idx = hashFunc(isbn);
    while (table[idx].inUse && table[idx].key != isbn) {
        idx = (idx + 1) % capacity;
    }
    table[idx].key = isbn;
    table[idx].book = book;
    table[idx].inUse = true;
    count++;
}

Book* HashTable::get(const std::string &isbn) {
    size_t idx = hashFunc(isbn);
    size_t start = idx;
    while (table[idx].inUse) {
        if (table[idx].key == isbn) {
            return &table[idx].book;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;
    }
    return nullptr;
}

void HashTable::remove(const std::string &isbn) {
    size_t idx = hashFunc(isbn);
    size_t start = idx;
    while (table[idx].inUse) {
        if (table[idx].key == isbn) {
            table[idx].inUse = false;
            count--;
            return;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;
    }
}
