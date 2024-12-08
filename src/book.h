#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    std::string isbn;
    std::string availability;
    std::vector<std::string> waiting_list;
    std::string image;

public:
    Book();
    Book(int id, const std::string &title, const std::string &author,
        const std::string &isbn, const std::string &availability,
        const std::vector<std::string> &waitlist = {}, const std::string &image = "");

    int getId() const;
    const std::string &getTitle() const;
    const std::string &getAuthor() const;
    const std::string &getISBN() const;
    const std::string &getAvailability() const;
    const std::vector<std::string> &getWaitlist() const;
    const std::string &getImage() const;

    void setAvailability(const std::string &status);
    void addWaitlistUser(const std::string &user);
    void removeFirstWaitlistUser();
};

#endif // BOOK_H