// commands.cpp : executes code specific to each command line command
//

#include "commands.h"

namespace Command
{
    void ListLibraryBooks()
    {
        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->ListAllLibraryBooks();
    }

    void ListBooks()
    {
        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->ListAllBooks();
    }

    void ListLoans()
    {
        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->ListAllLoans();
    }

    void ListPatrons()
    {
        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->ListAllPatrons();
    }

    void GetBookByBarcode(char *barcode)
    {
        string param(barcode);

        if (all_of(param.begin(), param.end(), ::isdigit))
        {
            LibraryDB *dbContext = LibraryDB::GetLibraryDB();

            if (dbContext == nullptr)
            {
                cerr << "No valid connection to DB." << endl;
                return;
            }

            dbContext->GetBookByBarcode(atol(barcode));
        }
        else
        {
            cerr << "Barcode must be a number" << endl;
        }
    }

    void NewBook(char *barcode, char *title, char *author, char *description)
    {
        string param(barcode);

        if (!all_of(param.begin(), param.end(), ::isdigit))
        {
            cerr << "Barcode must be a number" << endl;
            return;
        }

        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->CreateBook(atol(barcode), title, author, description);
    }

    void NewLibraryBook(char *library_barcode, char *book_barcode)
    {
        string lbParam(library_barcode);
        string bbParam(book_barcode);

        if (!all_of(lbParam.begin(), lbParam.end(), ::isdigit))
        {
            cerr << "Library barcode must be a number" << endl;
            return;
        }

        if (!all_of(bbParam.begin(), bbParam.end(), ::isdigit))
        {
            cerr << "Book barcode must be a number" << endl;
            return;
        }

        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->CreateLibraryBook(atol(library_barcode), atol(book_barcode));
    }

    void NewPatron(char *barcode, char *name)
    {
        string bParam(barcode);

        if (!all_of(bParam.begin(), bParam.end(), ::isdigit))
        {
            cerr << "Patron barcode must be a number" << endl;
            return;
        }

        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->CreatePatron(atol(barcode), name);
    }

    void Update(Types::DBTable table, long barcode, string column, string value)
    {
        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->Update(table, barcode, column, value);
    }

    void Delete(Types::DBTable table, long barcode)
    {
        LibraryDB *dbContext = LibraryDB::GetLibraryDB();

        if (dbContext == nullptr)
        {
            cerr << "No valid connection to DB." << endl;
            return;
        }

        dbContext->Delete(table, barcode);
    }
}