// db_context.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <pqxx/pqxx>

#include "types.h"

using namespace std;
using namespace pqxx;

namespace DBContext
{
    class LibraryDB
    {
    private:
        static unique_ptr<LibraryDB> dbSingleton;
        unique_ptr<connection> dbConnection;
        void queryHelper(string query, string headers);

    public:
        static LibraryDB *GetLibraryDB();
        LibraryDB(char *connStr);

        void ListAllLibraryBooks();
        void ListAllBooks();
        void ListAllPatrons();
        void ListAllLoans();
        void GetBookByBarcode(long barcode);
        void CreateBook(long barcode, string title, string author, string description);
        void CreateLibraryBook(long library_barcode, long book_barcode);
        void Update(Types::DBTable table, long barcode, string column, string value);
        void Delete(Types::DBTable table, long barcode);
    };
}
