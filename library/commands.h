// commands.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <pqxx/pqxx>

#include "db_context.h"
#include "types.h"

using namespace std;
using namespace pqxx;
using namespace DBContext;

namespace Command
{
    enum class CommandType
    {
        NotFound = 0,
        List,
        Get,
        Help,
        New,
        Update,
        Delete
    };

    void ListLibraryBooks();
    void ListBooks();
    void ListPatrons();
    void ListLoans();
    void GetBookByBarcode(char *barcode);
    void NewBook(char *barcode, char *title, char *author, char *description);
    void NewLibraryBook(char *library_barcode, char *book_barcode);
    void Update(Types::DBTable table, long barcode, string column, string value);
    void Delete(Types::DBTable table, long barcode);
}