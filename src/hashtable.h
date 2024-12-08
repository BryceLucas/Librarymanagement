#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "book.h" // Include the Book class definition
#include <vector> // Include vector for dynamic array functionality
#include <string> // Include string for key handling

// HashTable class definition
class HashTable {
private:
    // Structure for a hash table entry
    struct Entry {
        std::string key;  // Key used for hashing (in this case, the ISBN)
        Book book;        // The book object stored in this entry
        bool inUse;       // Indicates if the entry is currently in use

        // Default constructor for Entry, initializes inUse to false
        Entry();
    };

    std::vector<Entry> table; // Vector to store hash table entries
    size_t capacity;          // Maximum number of slots in the hash table
    size_t count;             // Number of currently used slots

    // Hash function to calculate an index for a given key
    size_t hashFunc(const std::string &key) const;

public:
    // Constructor to initialize the hash table with a given capacity (default is 101)
    HashTable(size_t cap = 101);

    // Inserts a book into the hash table using its ISBN as the key
    void insert(const std::string &isbn, const Book &book);

    // Retrieves a book from the hash table by its ISBN
    Book* get(const std::string &isbn);

    // Removes a book from the hash table using its ISBN as the key
    void remove(const std::string &isbn);
};

#endif // HASHTABLE_H