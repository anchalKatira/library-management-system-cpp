#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <sstream>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    std::string isbn;
    int totalCopies;
    int availableCopies;

public:
    Book() : id(0), totalCopies(0), availableCopies(0) {}

    Book(int id, const std::string& title, const std::string& author,
         const std::string& isbn, int totalCopies, int availableCopies)
        : id(id), title(title), author(author), isbn(isbn),
          totalCopies(totalCopies), availableCopies(availableCopies) {}

    // Getters
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }

    // Setters
    void setTitle(const std::string& t) { title = t; }
    void setAuthor(const std::string& a) { author = a; }
    void setIsbn(const std::string& i) { isbn = i; }
    void setTotalCopies(int t) { totalCopies = t; }
    void setAvailableCopies(int a) { availableCopies = a; }

    bool isAvailable() const { return availableCopies > 0; }

    void incrementAvailable() { availableCopies++; }
    void decrementAvailable() { if (availableCopies > 0) availableCopies--; }

    // Serialization: id|title|author|isbn|totalCopies|availableCopies
    std::string serialize() const {
        std::ostringstream oss;
        oss << id << "|" << title << "|" << author << "|" << isbn << "|"
            << totalCopies << "|" << availableCopies;
        return oss.str();
    }

    static Book deserialize(const std::string& line);
};

#endif // BOOK_H
