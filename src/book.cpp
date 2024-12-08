#ifndef BOOK_H
#define BOOK_H

#include <string>  // Include string for title, author, ISBN, availability, and image URL
#include <vector>  // Include vector to maintain the waiting list of users

// Class representing a book in the library system
class Book {
private:
    int id;                      // Unique identifier for the book
    std::string title;           // Title of the book
    std::string author;          // Author of the book
    std::string isbn;            // ISBN identifier for the book
    std::string availability;    // Availability status ("Available" or "Borrowed")
    std::vector<std::string> waiting_list; // List of users waiting for the book
    std::string image;           // URL or file path to the image of the book cover

public:
    // Default constructor
    Book();

    // Parameterized constructor to initialize all member variables
    Book(int id, const std::string &title, const std::string &author,
        const std::string &isbn, const std::string &availability,
        const std::vector<std::string> &waitlist = {}, 
        const std::string &image = "");

    // Getters (accessor methods) to access private members
    int getId() const;                         // Get the ID of the book
    const std::string &getTitle() const;      // Get the title of the book
    const std::string &getAuthor() const;     // Get the author's name
    const std::string &getISBN() const;       // Get the ISBN of the book
    const std::string &getAvailability() const; // Get the availability status of the book
    const std::vector<std::string> &getWaitlist() const; // Get the list of users waiting for the book
    const std::string &getImage() const;      // Get the URL or file path of the book cover image

    // Setters (mutator methods) to modify private members
    void setAvailability(const std::string &status); // Set the availability status of the book
    
    // Add a user to the waitlist (if not already present)
    void addWaitlistUser(const std::string &user);
    
    // Remove the first user from the waitlist
    void removeFirstWaitlistUser();
};

#endif // BOOK_H