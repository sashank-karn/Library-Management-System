#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MediaItem {
protected:
    string title;
    string author;
    int year;
    int itemID;

public:
    MediaItem(string t, string a, int y, int id) : title(t), author(a), year(y), itemID(id) {}

    virtual void displayDetails() {
        cout << "\nTitle: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
        cout << "Item ID: " << itemID << endl;
    }

    virtual void borrowItem() {
        cout << "Borrowing item..." << endl;
    }

    int getItemID() { return itemID; }

    virtual ~MediaItem() {}
};

class Book : public MediaItem {
private:
    int pages;
    bool isHardcover;
    int stock;

public:
    Book(string t, string a, int y, int id, int p, bool hc)
        : MediaItem(t, a, y, id), pages(p), isHardcover(hc), stock(5) {}

    void displayDetails() override {
        MediaItem::displayDetails();
        cout << "Pages: " << pages << endl;
        cout << "Hardcover: " << (isHardcover ? "Yes" : "No") << endl;
        cout << "Stock: " << stock << endl;
    }

    void borrowItem() override {
        if (stock > 0) {
            stock--;
            cout << "You have borrowed the book. Stock remaining: " << stock << endl;
        } else {
            cout << "Sorry, this book is out of stock!" << endl;
        }
    }
};

class eBook : public MediaItem {
private:
    double fileSizeMB;
    string format;

public:
    eBook(string t, string a, int y, int id, double size, string f)
        : MediaItem(t, a, y, id), fileSizeMB(size), format(f) {}

    void displayDetails() override {
        MediaItem::displayDetails();
        cout << "File Size: " << fileSizeMB << " MB" << endl;
        cout << "Format: " << format << endl;
    }

    void borrowItem() override {
        cout << "You have downloaded the eBook in " << format << " format." << endl;
    }
};

class Audiobook : public MediaItem {
private:
    int durationMinutes;
    string narrator;

public:
    Audiobook(string t, string a, int y, int id, int duration, string n)
        : MediaItem(t, a, y, id), durationMinutes(duration), narrator(n) {}

    void displayDetails() override {
        MediaItem::displayDetails();
        cout << "Duration: " << durationMinutes << " minutes" << endl;
        cout << "Narrator: " << narrator << endl;
    }

    void borrowItem() override {
        cout << "You have borrowed the audiobook narrated by " << narrator << "." << endl;
    }
};

class Library {
private:
    vector<MediaItem*> items;

public:
    void addItem(MediaItem* item) {
        items.push_back(item);
    }

    void displayAllItems() {
        if (items.empty()) {
            cout << "\nNo items in the library.\n";
            return;
        }

        for (size_t i = 0; i < items.size(); i++) {
            cout << "\nItem " << (i + 1) << ":" << endl;
            items[i]->displayDetails();
        }
    }

    void borrowByID(int id) {
        for (MediaItem* item : items) {
            if (item->getItemID() == id) {
                item->borrowItem();
                return;
            }
        }
        cout << "Item with ID " << id << " not found!" << endl;
    }

    ~Library() {
        for (auto item : items) {
            delete item;
        }
    }
};

int main() {
    Library myLibrary;
    int choice;

    while (true) {
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Add a new book\n";
        cout << "2. Add a new eBook\n";
        cout << "3. Add a new audiobook\n";
        cout << "4. Display all items\n";
        cout << "5. Borrow an item\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        }

        string title, author, format, narrator;
        int year, itemID, pages, duration;
        double fileSize;
        bool isHardcover;

        switch (choice) {
            case 1:
                cout << "\nEnter book details:\n";
                cout << "Title: "; cin.ignore(); getline(cin, title);
                cout << "Author: "; getline(cin, author);
                cout << "Year: "; cin >> year;
                cout << "Item ID: "; cin >> itemID;
                cout << "Number of pages: "; cin >> pages;
                cout << "Is it hardcover (1 for yes, 0 for no)? "; cin >> isHardcover;
                myLibrary.addItem(new Book(title, author, year, itemID, pages, isHardcover));
                cout << "Book added successfully!\n";
                break;

            case 2:
                cout << "\nEnter eBook details:\n";
                cout << "Title: "; cin.ignore(); getline(cin, title);
                cout << "Author: "; getline(cin, author);
                cout << "Year: "; cin >> year;
                cout << "Item ID: "; cin >> itemID;
                cout << "File Size (MB): "; cin >> fileSize;
                cout << "Format (e.g., PDF, EPUB): "; cin >> format;
                myLibrary.addItem(new eBook(title, author, year, itemID, fileSize, format));
                cout << "eBook added successfully!\n";
                break;

            case 3:
                cout << "\nEnter audiobook details:\n";
                cout << "Title: "; cin.ignore(); getline(cin, title);
                cout << "Author: "; getline(cin, author);
                cout << "Year: "; cin >> year;
                cout << "Item ID: "; cin >> itemID;
                cout << "Duration (minutes): "; cin >> duration;
                cout << "Narrator: "; cin.ignore(); getline(cin, narrator);
                myLibrary.addItem(new Audiobook(title, author, year, itemID, duration, narrator));
                cout << "Audiobook added successfully!\n";
                break;

            case 4:
                myLibrary.displayAllItems();
                break;

            case 5:
                cout << "\nEnter the item ID to borrow: ";
                cin >> itemID;
                myLibrary.borrowByID(itemID);
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
