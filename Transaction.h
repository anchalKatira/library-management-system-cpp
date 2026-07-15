#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <sstream>
#include <ctime>

// Simple day-based "date" model so the project has no external date deps.
// dayIssued / dayDue / dayReturned are stored as integer day counters
// (e.g. days since program epoch), which keeps fine calculation simple
// and deterministic for demo purposes.

class Transaction {
private:
    int transactionId;
    int bookId;
    int memberId;
    long issueDay;
    long dueDay;
    long returnDay; // -1 if not yet returned
    double fineAmount;

public:
    Transaction()
        : transactionId(0), bookId(0), memberId(0),
          issueDay(0), dueDay(0), returnDay(-1), fineAmount(0.0) {}

    Transaction(int transactionId, int bookId, int memberId,
                long issueDay, long dueDay)
        : transactionId(transactionId), bookId(bookId), memberId(memberId),
          issueDay(issueDay), dueDay(dueDay), returnDay(-1), fineAmount(0.0) {}

    int getTransactionId() const { return transactionId; }
    int getBookId() const { return bookId; }
    int getMemberId() const { return memberId; }
    long getIssueDay() const { return issueDay; }
    long getDueDay() const { return dueDay; }
    long getReturnDay() const { return returnDay; }
    double getFineAmount() const { return fineAmount; }
    bool isReturned() const { return returnDay != -1; }

    void markReturned(long day, double fine) {
        returnDay = day;
        fineAmount = fine;
    }

    // Serialization: id|bookId|memberId|issueDay|dueDay|returnDay|fine
    std::string serialize() const {
        std::ostringstream oss;
        oss << transactionId << "|" << bookId << "|" << memberId << "|"
            << issueDay << "|" << dueDay << "|" << returnDay << "|" << fineAmount;
        return oss.str();
    }

    static Transaction deserialize(const std::string& line);
};

#endif // TRANSACTION_H
