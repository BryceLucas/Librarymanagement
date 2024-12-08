#include "book.h"

Book::Book() = default;

Book::Book(int id, const std::string &title, const std::string &author,
        const std::string &isbn, const std::string &availability,
        const std::vector<std::string> &waitlist, const std::string &image)
    : id(id), title(title), author(author), isbn(isbn), availability(availability),
    waiting_list(waitlist), image(image) {}

int Book::getId() const { return id; }
const std::string &Book::getTitle() const { return title; }
const std::string &Book::getAuthor() const { return author; }
const std::string &Book::getISBN() const { return isbn; }
const std::string &Book::getAvailability() const { return availability; }
const std::vector<std::string> &Book::getWaitlist() const { return waiting_list; }
const std::string &Book::getImage() const { return image; }

void Book::setAvailability(const std::string &status) { availability = status; }
void Book::addWaitlistUser(const std::string &user) { waiting_list.push_back(user); }
void Book::removeFirstWaitlistUser() {
    if (!waiting_list.empty()) waiting_list.erase(waiting_list.begin());
}