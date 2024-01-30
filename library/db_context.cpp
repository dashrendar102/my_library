// db_context.cpp : executes code specific to each command line command
//

#include "db_context.h"
#include <iostream>

namespace DBContext
{
    unique_ptr<LibraryDB> LibraryDB::dbSingleton = nullptr;

    LibraryDB::LibraryDB(char *connStr)
    {
        dbConnection = make_unique<connection>(connStr);
    }

    LibraryDB *LibraryDB::GetLibraryDB()
    {
        if (dbSingleton)
        {
            return dbSingleton.get();
        }

        try
        {
            char *connStr = getenv("DATABASE_URL");

            if (connStr == nullptr)
            {
                cerr << "No connection string in ENV. Cannot connect." << endl;
                return nullptr;
            }

            dbSingleton = make_unique<LibraryDB>(connStr);

            return dbSingleton.get();
        }
        catch (exception const &e)
        {
            cerr << "Issue connecting to DB: " << e.what() << endl;
            dbSingleton = nullptr;
            return nullptr;
        }
    }

    map<Types::DBTable, string> TableNames = {
        {Types::DBTable::Book, "books"},
        {Types::DBTable::LibraryBook, "library_books"},
        {Types::DBTable::Patrons, "patrons"},
        {Types::DBTable::Loans, "loans"}};

    map<Types::DBTable, string> TableKeys = {
        {Types::DBTable::Book, "barcode"},
        {Types::DBTable::LibraryBook, "library_barcode"},
        {Types::DBTable::Patrons, "barcode"},
        {Types::DBTable::Loans, "id"}};

    void LibraryDB::queryHelper(string query, string headers)
    {
        work transaction(*dbConnection.get());
        result dbResult = transaction.exec(query);
        transaction.commit();

        cout << headers << endl;

        for (auto const row : dbResult)
        {
            bool hasRunOnce = false;

            for (auto const field : row)
            {
                if (hasRunOnce)
                {
                    cout << ", ";
                }
                else
                {
                    hasRunOnce = true;
                }

                cout << field.c_str();
            }
            cout << endl;
        }
    }

    void LibraryDB::ListAllLibraryBooks()
    {
        string query =
            "SELECT lb.library_barcode, b.title, b.author, b.barcode \
             FROM library_books AS lb \
             INNER JOIN books as b \
             ON b.barcode = lb.book_barcode;";

        string headers = "Library Barcode, Title, Author, Publisher Barcode";

        queryHelper(query, headers);
    }

    void LibraryDB::ListAllBooks()
    {
        string query =
            "SELECT title, author, barcode \
             FROM books;";

        string headers = "Title, Author, Barcode";

        queryHelper(query, headers);
    }

    void LibraryDB::ListAllPatrons()
    {
        string query =
            "SELECT name, barcode \
             FROM patrons;";

        string headers = "Name, Barcode";

        queryHelper(query, headers);
    }

    void LibraryDB::ListAllLoans()
    {
        string query =
            "SELECT p.name, b.title, b.author, lb.library_barcode \
             FROM loans AS l \
             INNER JOIN patrons AS p ON l.patron_barcode = p.barcode \
             INNER JOIN library_books AS lb ON lb.library_barcode = l.library_book_barcode \
             INNER JOIN books AS b ON b.barcode = lb.book_barcode;";

        string headers = "Name, Title, Author, Library Barcode";

        queryHelper(query, headers);
    }

    void LibraryDB::GetBookByBarcode(long barcode)
    {
        string query =
            "SELECT lb.library_barcode, b.title, b.author, b.barcode, b.description \
             FROM library_books AS lb \
             INNER JOIN books as b \
             ON b.barcode = lb.book_barcode \
             WHERE lb.library_barcode = " +
            to_string(barcode);

        string headers = "Library Barcode, Title, Author, Publisher Barcode, Description";

        queryHelper(query, headers);
    }

    void LibraryDB::CreateBook(long barcode, string title, string author, string description)
    {
        try
        {
            dbConnection.get()->prepare(
                "insert_book",
                "INSERT INTO books (barcode, title, author, description) \
                 VALUES ($1, $2, $3, $4)");

            work transaction(*dbConnection.get());
            result result = transaction.exec_prepared0("insert_book", barcode, title, author, description);
            transaction.commit();

            if (result.affected_rows() != 1)
            {
                cerr << "Unable to create book " << barcode << endl;
            }
            else
            {
                cout << "Successfully created book " << barcode << endl;
            }
        }
        catch (exception const &e)
        {
            cerr << "Issue inserting book into DB: " << e.what() << endl;
        }
    }

    void LibraryDB::CreateLibraryBook(long library_barcode, long book_barcode)
    {
        try
        {
            dbConnection.get()->prepare(
                "insert_library_book",
                "INSERT INTO library_books (library_barcode, book_barcode) \
                 VALUES ($1, $2)");

            work transaction(*dbConnection.get());
            result result = transaction.exec_prepared0("insert_library_book", library_barcode, book_barcode);
            transaction.commit();

            if (result.affected_rows() != 1)
            {
                cerr << "Unable to create library_book " << library_barcode << endl;
            }
            else
            {
                cout << "Successfully created library_book " << library_barcode << endl;
            }
        }
        catch (exception const &e)
        {
            cerr << "Issue inserting library_book into DB: " << e.what() << endl;
        }
    }

    void LibraryDB::Update(Types::DBTable table, long barcode, string column, string value)
    {
        try
        {
            work transaction(*dbConnection.get());
            dbConnection.get()->prepare(
                "update",
                "UPDATE " + TableNames[table] + " SET " + column + " = $1 WHERE " + TableKeys[table] + " = $2");

            result result = transaction.exec_prepared0("update", value, barcode);
            transaction.commit();

            if (result.affected_rows() != 1)
            {
                cerr << "Barcode " << barcode << " was not found" << endl;
            }
            else
            {
                cout << "Successfully updated resource " << barcode << endl;
            }
        }
        catch (exception const &e)
        {
            cerr << "Issue updating " << TableNames[table] << ": " << e.what() << endl;
        }
    }

    void LibraryDB::Delete(Types::DBTable table, long barcode)
    {
        try
        {
            work transaction(*dbConnection.get());
            dbConnection.get()->prepare(
                "delete",
                "DELETE FROM " + TableNames[table] + " WHERE " + TableKeys[table] + " = $1");

            result result = transaction.exec_prepared0("delete", barcode);
            transaction.commit();

            if (result.affected_rows() != 1)
            {
                cerr << "Barcode " << barcode << " was not found" << endl;
            }
            else
            {
                cout << "Successfully deleted resource " << barcode << endl;
            }
        }
        catch (exception const &e)
        {
            cerr << "Issue deleting in " << TableNames[table] << ": " << e.what() << endl;
        }
    }
}
