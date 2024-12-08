#include "hashtable.h" // Include the header file for the HashTable class

// Default constructor for Entry struct
// Initializes the 'inUse' flag to false, indicating the slot is empty
HashTable::Entry::Entry() : inUse(false) {}

// Constructor for the HashTable class
// Initializes the hash table with the given capacity and resizes the table
HashTable::HashTable(size_t cap) : capacity(cap), count(0) {
    table.resize(capacity); // Resize the vector to match the capacity
}

// Hash function to compute an index for the given key (ISBN) 
// Uses std::hash to convert the string key into a hash and returns its position in the table
size_t HashTable::hashFunc(const std::string &key) const {
    std::hash<std::string> hasher;  // Create a hash function object for strings
    return hasher(key) % capacity;  // Get an index within the range [0, capacity-1]
}

// Insert a book into the hash table using the ISBN as the key
void HashTable::insert(const std::string &isbn, const Book &book) {
    size_t idx = hashFunc(isbn); // Compute the starting index using the hash function
    
    // Handle collisions using linear probing
    while (table[idx].inUse && table[idx].key != isbn) {
        idx = (idx + 1) % capacity; // Move to the next slot (circular)
    }

    // Insert the book into the slot
    table[idx].key = isbn;       // Store the key (ISBN)
    table[idx].book = book;      // Store the book object
    table[idx].inUse = true;     // Mark the slot as in use
    count++;                     // Increase the count of occupied slots
}

// Retrieve a book from the hash table using its ISBN
// Returns a pointer to the book if found, otherwise returns nullptr
Book* HashTable::get(const std::string &isbn) {
    size_t idx = hashFunc(isbn); // Compute the starting index using the hash function
    size_t start = idx; // Save the start index to detect a full loop

    // Search the table using linear probing
    while (table[idx].inUse) {
        if (table[idx].key == isbn) { // Check if the current slot matches the ISBN
            return &table[idx].book;  // Return a pointer to the book if found
        }
        idx = (idx + 1) % capacity; // Move to the next slot (circular)
        if (idx == start) break;    // If we've looped back to the start, stop the search
    }
    return nullptr; // Return nullptr if no matching book was found
}

// Remove a book from the hash table using its ISBN
void HashTable::remove(const std::string &isbn) {
    size_t idx = hashFunc(isbn); // Compute the starting index using the hash function
    size_t start = idx; // Save the start index to detect a full loop

    // Search for the book to remove using linear probing
    while (table[idx].inUse) {
        if (table[idx].key == isbn) { // Check if the current slot matches the ISBN
            table[idx].inUse = false; // Mark the slot as no longer in use
            count--;                  // Decrease the count of occupied slots
            return;                   // Exit the method after removing the book
        }
        idx = (idx + 1) % capacity; // Move to the next slot (circular)
        if (idx == start) break;    // If we've looped back to the start, stop the search
    }
}