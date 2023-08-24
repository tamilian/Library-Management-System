#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

struct Book {
    string title;
    string author;
    string publicationYear;
    string ISBN;
    bool availability;
};

vector<Book> library;

void menu() {
    string menuText = R"(
    Enter a number from 1 - 6
    1. Add a Book
    2. Search a book
    3. Display book details
    4. Borrow a book
    5. Return a book
    6. Exit
    )";

    cout << menuText << endl;
}

void addBook() {
    Book newBook;
    cout << "Enter book details: " << endl;

    cout << "Enter the Title of the book: ";
    cin.ignore();
    getline(cin, newBook.title);

    cout << "Enter the Author of the Book: ";
    getline(cin, newBook.author);

    cout << "Enter the Publication year of the Book: ";
    getline(cin, newBook.publicationYear);

    cout << "Enter the ISBN of the Book (w/ no spaces): ";
    getline(cin, newBook.ISBN);

    newBook.availability = true;
    library.push_back(newBook);

    cout << "Book added successfully!" << endl;
}

void searchBookByTitle() {
    string bookTitle;
    cout << "Enter the title of the book: ";
    cin.ignore();
    getline(cin, bookTitle);

    bool found = false;

    for (const Book& book : library) {
        if (toLowerCase(book.title) == toLowerCase(bookTitle) || toLowerCase(book.ISBN) == toLowerCase(bookTitle)) {
            cout << book.title << " is available!" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << bookTitle << " is not available!" << endl;
    }
}

void displayBook() {
    string bookDetails;
    cout << "Enter the ISBN or title of the book: ";
    cin.ignore();
    getline(cin, bookDetails);

    bool found = false;

    for (const Book& book : library) {
        if (toLowerCase(book.title) == toLowerCase(bookDetails) || toLowerCase(book.ISBN) == toLowerCase(bookDetails)) {
            cout << "Book Details: " << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Publication Year: " << book.publicationYear << endl;
            cout << "ISBN: " << book.ISBN << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book details not found." << endl;
    }
}

void borrowBook() {
    string bookTitle;
    cout << "Enter the ISBN or title of the book you would like to borrow: ";
    cin.ignore();
    getline(cin, bookTitle);

    bool found = false;

    for (Book& book : library) {
        if (toLowerCase(book.title) == toLowerCase(bookTitle) || toLowerCase(book.ISBN) == toLowerCase(bookTitle)) {
            if (book.availability) {
                cout << "You have successfully borrowed " << book.title << "." << endl;
                book.availability = false;
                found = true;
                break;
            } else {
                cout << "The book " << book.title << " is currently not available to be borrowed." << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "This book is not available in this library." << endl;
    }
}

void returnBook() {
    string bookTitle;
    cout << "Enter the ISBN or title of book you would like to return: ";
    cin.ignore();
    getline(cin, bookTitle);

    bool found = false;

    for (Book& book : library) {
        if (toLowerCase(book.title) == toLowerCase(bookTitle) || toLowerCase(book.ISBN) == toLowerCase(bookTitle)) {
            if (!book.availability) {
                cout << "You have successfully returned " << book.title << "." << endl;
                book.availability = true;
                found = true;
                break;
            } else {
                cout << "The book " << book.title << " is currently available for checkout." << endl;
                cout << "Please take this book to a librarian for this situation to be resolved." << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "This book is not found in the library." << endl;
    }
}

int main() {
    int choice;
    while (true) {
        menu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBookByTitle();
                break;
            case 3:
                displayBook();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                cout << "Thank you for visiting the library today. Goodbye." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose again." << endl;
        }
    }

    return 0;
}

