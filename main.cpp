#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <stdexcept>

// using namespace std

class Date {
private:
    int day, month, year;

public:
    Date();

    Date(int day, int month, int year);

    // Accessors and mutators for day, month, and year
    // Accessors
    [[nodiscard]] int getDay() const { return day; }
    [[nodiscard]] int getMonth() const { return month; }
    [[nodiscard]] int getYear() const { return year; }

    // Mutators
    void setDay(int day) { this->day = day; }
    void setMonth(int month) { this->month = month; }
    void setYear(int year) { this->year = year; }
};

Date::Date() : day(1), month(1), year(1900) {
}

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
}

class Book {
private:
    std::string title, author, genre, ISBN;
    Date publicationDate;
    int price, quantity;

public:
    Book();

    Book(const std::string &title, const std::string &author, const std::string &genre, const std::string &ISBN,
         const Date &publicationDate, int price, int quantity); // Parameterized constructor
    Book(const Book &other);

    // Accessors, mutators, and other methods
    // Accessors
    [[nodiscard]] std::string getTitle() const { return title; }
    [[nodiscard]] std::string getAuthor() const { return author; }
    [[nodiscard]] std::string getGenre() const { return genre; }
    [[nodiscard]] std::string getISBN() const { return ISBN; }
    [[nodiscard]] Date getPublicationDate() const { return publicationDate; }
    [[nodiscard]] int getPrice() const { return price; }
    [[nodiscard]] int getQuantity() const { return quantity; }

    // Mutators
    void setTitle(const std::string &title) { this->title = title; }
    void setAuthor(const std::string &author) { this->author = author; }
    void setGenre(const std::string &genre) { this->genre = genre; }
    void setISBN(const std::string &ISBN) { this->ISBN = ISBN; }
    void setPublicationDate(const Date &publicationDate) { this->publicationDate = publicationDate; }
    void setPrice(int price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity = quantity; }
};


Book::Book() : title(""), author(""), genre(""), ISBN(""), publicationDate(Date()), price(0), quantity(0) {
}

Book::Book(const std::string &title, const std::string &author, const std::string &genre, const std::string &ISBN,
           const Date &publicationDate, int price, int quantity)
    : title(title), author(author), genre(genre), ISBN(ISBN), publicationDate(publicationDate), price(price),
      quantity(quantity) {
}

Book::Book(const Book &other)
    : title(other.title), author(other.author), genre(other.genre), ISBN(other.ISBN),
      publicationDate(other.publicationDate),
      price(other.price), quantity(other.quantity) {
}


class Catalog {
private:
    std::list<Book> books;

public:
    Catalog(); // Constructor
    void addBook(const Book &book); // Add book to catalog
    void removeBook(const std::string &ISBN); // Remove book from catalog
    Book &searchBook(const std::string &ISBN); // Search book by ISBN
    // Other methods (sorting, min/max price, average price, etc.)
    // Accessors
    std::list<Book> getBooks() const { return books; }

    // Mutators
    void setBooks(const std::list<Book> &books) { this->books = books; }

    // Sorting, min/max price, average price, etc.
    void sortCatalogByTitle();

    void sortCatalogByAuthor();

    void sortCatalogByPrice();

    Book findMinPriceBook();

    Book findMaxPriceBook();

    double calculateAveragePrice();
};

Catalog::Catalog() : books() {
}

void Catalog::addBook(const Book &book) {
    books.push_back(book);
}

void Catalog::removeBook(const std::string &ISBN) {
    books.remove_if([&ISBN](const Book &book) { return book.getISBN() == ISBN; });
}

Book &Catalog::searchBook(const std::string &ISBN) {
    for (Book &book: books) {
        if (book.getISBN() == ISBN) {
            return book;
        }
    }
    throw std::runtime_error("Book not found");
}


class Transaction {
protected:
    std::string transactionID;
    Date transactionDate;

public:
    Transaction(); // Default constructor
    Transaction(const std::string &transactionID, const Date &transactionDate);

    // Accessors
    std::string getTransactionID() const { return transactionID; }
    Date getTransactionDate() const { return transactionDate; }

    // Mutators
    void setTransactionID(const std::string &transactionID) { this->transactionID = transactionID; }
    void setTransactionDate(const Date &transactionDate) { this->transactionDate = transactionDate; }

    //Pure Virtual Function
    virtual void process() = 0;
};


Transaction::Transaction() : transactionID(""), transactionDate(Date()) {
}

Transaction::Transaction(const std::string &transactionID, const Date &transactionDate)
    : transactionID(transactionID), transactionDate(transactionDate) {
}

class Order : public Transaction {
private:
    std::string customerID;
    Book orderedBook;
    int quantity;

public:
    // Constructors
    Order() : Transaction(), customerID(""), orderedBook(Book()), quantity(0) {
    }

    Order(const std::string &transactionID, const Date &transactionDate, const std::string &customerID,
          const Book &orderedBook, int quantity)
        : Transaction(transactionID, transactionDate), customerID(customerID), orderedBook(orderedBook),
          quantity(quantity) {
    }

    // Accessors
    std::string getCustomerID() const { return customerID; }
    Book getOrderedBook() const { return orderedBook; }
    int getQuantity() const { return quantity; }

    // Mutators
    void setCustomerID(const std::string &customerID) { this->customerID = customerID; }
    void setOrderedBook(const Book &orderedBook) { this->orderedBook = orderedBook; }
    void setQuantity(int quantity) { this->quantity = quantity; }

    void process() override {
        // Process the order
        if (orderedBook.getQuantity() >= quantity) {
            // Update the quantity of the book in the catalog
            orderedBook.setQuantity(orderedBook.getQuantity() - quantity);
            std::cout << "Order processed successfully." << std::endl;
        } else {
            // Handle the case when there is not enough stock
            std::cerr << "Insufficient stock for the ordered book." << std::endl;
        }
    }
};

class Sale : public Transaction {
private:
    std::string customerID;
    Book soldBook;
    int quantity;

public:
    // Constructors
    Sale() : Transaction() {
    }

    Sale(const std::string &transactionID, const Date &transactionDate, const std::string &customerID,
         const Book &soldBook, int quantity)
        : Transaction(transactionID, transactionDate), customerID(customerID), soldBook(soldBook), quantity(quantity) {
    }

    // Accessors
    std::string getCustomerID() const { return customerID; }
    Book getSoldBook() const { return soldBook; }
    int getQuantity() const { return quantity; }

    // Mutators
    void setCustomerID(const std::string &customerID) { this->customerID = customerID; }
    void setSoldBook(const Book &soldBook) { this->soldBook = soldBook; }
    void setQuantity(int quantity) { this->quantity = quantity; }

    // Other methods
    void process() override {
        // Process the sale
        if (soldBook.getQuantity() >= quantity) {
            // Update the quantity of the book in the catalog
            soldBook.setQuantity(soldBook.getQuantity() - quantity);
            std::cout << "Sale processed successfully." << std::endl;
        } else {
            // Handle the case when there is not enough stock
            std::cerr << "Insufficient stock for the sold book." << std::endl;
        }
    }
};


class Bookstore {
private:
    Catalog catalog;
    std::list<Transaction *> transactions;

public:
    // Constructor
    Bookstore();

    void manageCatalog() {
        for (const Book &book: catalog.getBooks()) {
            std::cout << "Title: " << book.getTitle() << std::endl;
            std::cout << "Author: " << book.getAuthor() << std::endl;
            std::cout << "Genre: " << book.getGenre() << std::endl;
            std::cout << "ISBN: " << book.getISBN() << std::endl;
            std::cout << "Publication Date: " << book.getPublicationDate().getDay() << "/"
                    << book.getPublicationDate().getMonth() << "/"
                    << book.getPublicationDate().getYear() << std::endl;
            std::cout << "Price: " << book.getPrice() << std::endl;
            std::cout << "Quantity: " << book.getQuantity() << std::endl;
            std::cout << std::endl;
        }
    }


    // Process transactions (order, sale, etc.)
    void processTransaction(Transaction *transaction) {
        // Example implementation: add the transaction to the list
        transactions.push_back(transaction);
    }

    Catalog &getCatalog() { return catalog; }

    std::list<Transaction *> &getTransactions();
};

Bookstore::Bookstore() : catalog(), transactions() {
}

std::list<Transaction *> &Bookstore::getTransactions() {
    return transactions;
}

void displayMenu() {
    std::cout << "Bookstore Management System\n"
            << "---------------------------\n"
            << "1. Add book\n"
            << "2. Display books\n"
            << "3. Record Order transaction\n"
            << "4. Record Sale transaction\n"
            << "5. Display transactions\n"
            << "6. Exit\n"
            << "Enter your choice: ";
}

int main() {
    Bookstore bookstore;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, author, genre, ISBN;
                int day, month, year, quantity;
                int price;

                std::cin.ignore();
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);

                std::cout << "Enter author: ";
                std::getline(std::cin, author);

                std::cout << "Enter genre: ";
                std::getline(std::cin, genre);

                std::cout << "Enter ISBN: ";
                std::getline(std::cin, ISBN);

                std::cout << "Enter published date (dd mm yyyy): ";
                std::cin >> day >> month >> year;

                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                std::cout << "Enter price: ";
                std::cin >> price;

                Date date(day, month, year);
                Book book(title, author, genre, ISBN, date, quantity, price);
                bookstore.getCatalog().addBook(book);
                std::cout << "Book added successfully!\n";
                break;
            }

            case 2: {
                // Display books
                bookstore.manageCatalog();
                break;
            }

            case 3: {
                // Record Order transaction
                // TODO: Implement this functionality based on your classes and methods
                // Record Order transaction
                std::string transactionID, customerID, ISBN;
                int day, month, year, quantity;

                std::cin.ignore();
                std::cout << "Enter transaction ID: ";
                std::getline(std::cin, transactionID);

                std::cout << "Enter customer ID: ";
                std::getline(std::cin, customerID);

                std::cout << "Enter ISBN: ";
                std::getline(std::cin, ISBN);

                std::cout << "Enter transaction date (dd mm yyyy): ";
                std::cin >> day >> month >> year;

                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                Date transactionDate(day, month, year);
                try {
                    Book &orderedBook = bookstore.getCatalog().searchBook(ISBN);
                    Order *order = new Order(transactionID, transactionDate, customerID, orderedBook, quantity);
                    bookstore.processTransaction(order);
                    order->process();
                } catch (const std::runtime_error &e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }
            case 4: {
                // Record Sale transaction
                std::string transactionID, customerID, ISBN;
                int day, month, year, quantity;

                std::cin.ignore();
                std::cout << "Enter transaction ID: ";
                std::getline(std::cin, transactionID);

                std::cout << "Enter customer ID: ";
                std::getline(std::cin, customerID);

                std::cout << "Enter ISBN: ";
                std::getline(std::cin, ISBN);

                std::cout << "Enter transaction date (dd mm yyyy): ";
                std::cin >> day >> month >> year;

                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                Date transactionDate(day, month, year);
                try {
                    Book &soldBook = bookstore.getCatalog().searchBook(ISBN);
                    Sale *sale = new Sale(transactionID, transactionDate, customerID, soldBook, quantity);
                    bookstore.processTransaction(sale);
                    sale->process();
                } catch (const std::runtime_error &e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                // Display transactions
                for (Transaction *transaction: bookstore.getTransactions()) {
                    std::cout << "Transaction ID: " << transaction->getTransactionID() << std::endl;
                    std::cout << "Transaction Date: " << transaction->getTransactionDate().getDay() << "/"
                            << transaction->getTransactionDate().getMonth() << "/"
                            << transaction->getTransactionDate().getYear() << std::endl;
                    std::cout << std::endl;
                }
                break;
            }
            case 6:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
