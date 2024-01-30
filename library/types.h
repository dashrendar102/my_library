// types.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <chrono>
#include <cstdio>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
using namespace std::chrono;

typedef pair<string, string> strPair;

namespace Types
{
    enum class DBTable
    {
        NotFound = 0,
        Book,
        LibraryBook,
        Patrons,
        Loans
    };

    class Patrons
    {
    public:
        string Name;
        long Barcode;

        string ToString();
    };

    class Books
    {
    public:
        int Barcode;
        string Title;
        string Author;
        string Description;

        string ToString();
    };

    class LibraryBooks
    {
    public:
        long LibraryBarcode;
        int BookBarcode;

        string ToString();
    };

    class Loans
    {
    public:
        int Id;
        int LibraryBookId;
        int PatronId;
        time_point<system_clock, duration<int>> StartDate;
        time_point<system_clock, duration<int>> EndDate;
        time_point<system_clock, duration<int>> DueDate;

        string ToString();
    };
}