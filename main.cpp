#include <iostream>
#include <iomanip>
#include <limits>
#include "../include/Library.h"

// ---------- input helpers ----------

static void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInputBuffer();
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
        clearInputBuffer();
    }
}

static std::string readLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// ---------- display helpers ----------

static void printBookRow(const Book& b) {
    std::cout << std::left
               << std::setw(5) << b.getId()
               << std::setw(30) << b.getTitle()
               << std::setw(20) << b.getAuthor()
               << std::setw(15) << b.getIsbn()
               << std::setw(10) << b.getAvailableCopies()
               << std::setw(8) << b.getTotalCopies()
               << "\n";
}

static void printBookTableHeader() {
    std::cout << std::left
               << std::setw(5) << "ID"
               << std::setw(30) << "Title"
               << std::setw(20) << "Author"
               << std::setw(15) << "ISBN"
               << std::setw(10) << "Avail"
               << std::setw(8) << "Total"
               << "\n";
    std::cout << std::string(88, '-') << "\n";
}

static void printMemberRow(const Member& m) {
    std::cout << std::left
               << std::setw(5) << m.getId()
               << std::setw(25) << m.getName()
               << std::setw(30) << m.getEmail()
               << std::setw(10) << m.borrowedCount()
               << "\n";
}

// ---------- menu actions ----------

static void addBookFlow(Library& lib) {
    std::string title = readLine("Title: ");
    std::string author = readLine("Author: ");
    std::string isbn = readLine("ISBN: ");
    int copies = readInt("Number of copies: ");
    int id = lib.addBook(title, author, isbn, copies);
    std::cout << "Book added with ID " << id << ".\n";
}

static void removeBookFlow(Library& lib) {
    int id = readInt("Book ID to remove: ");
    if (lib.removeBook(id)) {
        std::cout << "Book removed.\n";
    } else {
        std::cout << "Could not remove book (not found, or copies still on loan).\n";
    }
}

static void listBooksFlow(Library& lib) {
    printBookTableHeader();
    for (const auto& b : lib.getAllBooks()) printBookRow(b);
}

static void searchBooksFlow(Library& lib) {
    std::cout << "Search by: 1) Title  2) Author  3) ISBN\n";
    int choice = readInt("Choice: ");
    if (choice == 1) {
        std::string q = readLine("Title contains: ");
        auto results = lib.searchByTitle(q);
        printBookTableHeader();
        for (const auto& b : results) printBookRow(b);
    } else if (choice == 2) {
        std::string q = readLine("Author contains: ");
        auto results = lib.searchByAuthor(q);
        printBookTableHeader();
        for (const auto& b : results) printBookRow(b);
    } else if (choice == 3) {
        std::string q = readLine("Exact ISBN: ");
        auto result = lib.searchByIsbn(q);
        if (result) {
            printBookTableHeader();
            printBookRow(*result);
        } else {
            std::cout << "No book found with that ISBN.\n";
        }
    } else {
        std::cout << "Invalid choice.\n";
    }
}

static void addMemberFlow(Library& lib) {
    std::string name = readLine("Name: ");
    std::string email = readLine("Email: ");
    int id = lib.addMember(name, email);
    std::cout << "Member registered with ID " << id << ".\n";
}

static void removeMemberFlow(Library& lib) {
    int id = readInt("Member ID to remove: ");
    if (lib.removeMember(id)) {
        std::cout << "Member removed.\n";
    } else {
        std::cout << "Could not remove member (not found, or has outstanding books).\n";
    }
}

static void listMembersFlow(Library& lib) {
    std::cout << std::left
               << std::setw(5) << "ID"
               << std::setw(25) << "Name"
               << std::setw(30) << "Email"
               << std::setw(10) << "Borrowed"
               << "\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto& m : lib.getAllMembers()) printMemberRow(m);
}

static void issueBookFlow(Library& lib) {
    int bookId = readInt("Book ID: ");
    int memberId = readInt("Member ID: ");
    std::string err;
    if (lib.issueBook(bookId, memberId, err)) {
        std::cout << "Book issued successfully. Due in 14 days.\n";
    } else {
        std::cout << "Failed to issue book: " << err << "\n";
    }
}

static void returnBookFlow(Library& lib) {
    int bookId = readInt("Book ID: ");
    int memberId = readInt("Member ID: ");
    std::string err;
    double fine = 0.0;
    if (lib.returnBook(bookId, memberId, fine, err)) {
        std::cout << "Book returned successfully.\n";
        if (fine > 0) {
            std::cout << "Overdue fine charged: Rs. " << std::fixed
                       << std::setprecision(2) << fine << "\n";
        } else {
            std::cout << "Returned on time. No fine.\n";
        }
    } else {
        std::cout << "Failed to return book: " << err << "\n";
    }
}

static void memberHistoryFlow(Library& lib) {
    int memberId = readInt("Member ID: ");
    auto active = lib.getActiveTransactionsForMember(memberId);
    if (active.empty()) {
        std::cout << "No active loans for this member.\n";
        return;
    }
    std::cout << std::left
               << std::setw(10) << "TxnID"
               << std::setw(10) << "BookID"
               << std::setw(12) << "IssueDay"
               << std::setw(12) << "DueDay"
               << "\n";
    for (const auto& t : active) {
        std::cout << std::left
                   << std::setw(10) << t.getTransactionId()
                   << std::setw(10) << t.getBookId()
                   << std::setw(12) << t.getIssueDay()
                   << std::setw(12) << t.getDueDay()
                   << "\n";
    }
}

static void overdueReportFlow(Library& lib) {
    auto overdue = lib.getOverdueTransactions();
    if (overdue.empty()) {
        std::cout << "No overdue books. Nice!\n";
        return;
    }
    std::cout << std::left
               << std::setw(10) << "TxnID"
               << std::setw(10) << "BookID"
               << std::setw(10) << "MemberID"
               << std::setw(12) << "DueDay"
               << "\n";
    for (const auto& t : overdue) {
        std::cout << std::left
                   << std::setw(10) << t.getTransactionId()
                   << std::setw(10) << t.getBookId()
                   << std::setw(10) << t.getMemberId()
                   << std::setw(12) << t.getDueDay()
                   << "\n";
    }
}

static void printMenu() {
    std::cout << "\n===== Library Management System =====\n"
               << " 1. Add Book\n"
               << " 2. Remove Book\n"
               << " 3. List All Books\n"
               << " 4. Search Books\n"
               << " 5. Register Member\n"
               << " 6. Remove Member\n"
               << " 7. List All Members\n"
               << " 8. Issue Book\n"
               << " 9. Return Book\n"
               << "10. View Member's Active Loans\n"
               << "11. Overdue Report\n"
               << " 0. Exit\n"
               << "=======================================\n";
}

int main() {
    Library lib;

    std::cout << "Welcome to the Library Management System\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt("Select an option: ");

        switch (choice) {
            case 1: addBookFlow(lib); break;
            case 2: removeBookFlow(lib); break;
            case 3: listBooksFlow(lib); break;
            case 4: searchBooksFlow(lib); break;
            case 5: addMemberFlow(lib); break;
            case 6: removeMemberFlow(lib); break;
            case 7: listMembersFlow(lib); break;
            case 8: issueBookFlow(lib); break;
            case 9: returnBookFlow(lib); break;
            case 10: memberHistoryFlow(lib); break;
            case 11: overdueReportFlow(lib); break;
            case 0:
                running = false;
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option, try again.\n";
        }
    }

    return 0;
}
