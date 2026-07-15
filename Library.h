#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <optional>
#include "Book.h"
#include "Member.h"
#include "Transaction.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Transaction> transactions;

    int nextBookId;
    int nextMemberId;
    int nextTransactionId;

    static constexpr int LOAN_PERIOD_DAYS = 14;
    static constexpr double FINE_PER_DAY = 5.0; // currency units per overdue day

    const std::string booksFile = "data/books.txt";
    const std::string membersFile = "data/members.txt";
    const std::string transactionsFile = "data/transactions.txt";

    Book* findBookById(int id);
    Member* findMemberById(int id);
    long currentDay() const; // days since a fixed epoch, used to simulate "today"

public:
    Library();

    // Persistence
    void loadAll();
    void saveAll();

    // Book operations
    int addBook(const std::string& title, const std::string& author,
                const std::string& isbn, int copies);
    bool removeBook(int bookId);
    std::vector<Book> searchByTitle(const std::string& query) const;
    std::vector<Book> searchByAuthor(const std::string& query) const;
    std::optional<Book> searchByIsbn(const std::string& isbn) const;
    const std::vector<Book>& getAllBooks() const { return books; }

    // Member operations
    int addMember(const std::string& name, const std::string& email);
    bool removeMember(int memberId);
    const std::vector<Member>& getAllMembers() const { return members; }
    Member* getMember(int id) { return findMemberById(id); }

    // Circulation
    bool issueBook(int bookId, int memberId, std::string& errorMsg);
    bool returnBook(int bookId, int memberId, double& fineCharged, std::string& errorMsg);

    // Reports
    std::vector<Transaction> getActiveTransactionsForMember(int memberId) const;
    std::vector<Transaction> getOverdueTransactions() const;
    const std::vector<Transaction>& getAllTransactions() const { return transactions; }
};

#endif // LIBRARY_H
