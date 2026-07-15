#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class Member {
private:
    int id;
    std::string name;
    std::string email;
    std::vector<int> borrowedBookIds;

public:
    Member() : id(0) {}

    Member(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    const std::vector<int>& getBorrowedBooks() const { return borrowedBookIds; }

    void setName(const std::string& n) { name = n; }
    void setEmail(const std::string& e) { email = e; }

    void borrowBook(int bookId) { borrowedBookIds.push_back(bookId); }

    void returnBook(int bookId) {
        borrowedBookIds.erase(
            std::remove(borrowedBookIds.begin(), borrowedBookIds.end(), bookId),
            borrowedBookIds.end());
    }

    bool hasBorrowed(int bookId) const {
        return std::find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId)
               != borrowedBookIds.end();
    }

    int borrowedCount() const { return static_cast<int>(borrowedBookIds.size()); }

    // Serialization: id|name|email|bookId1,bookId2,...
    std::string serialize() const {
        std::ostringstream oss;
        oss << id << "|" << name << "|" << email << "|";
        for (size_t i = 0; i < borrowedBookIds.size(); ++i) {
            oss << borrowedBookIds[i];
            if (i != borrowedBookIds.size() - 1) oss << ",";
        }
        return oss.str();
    }

    static Member deserialize(const std::string& line);
};

#endif // MEMBER_H
