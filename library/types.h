// types.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <chrono>
#include <cstdio>
#include <sstream>
#include <vector>

using namespace std;
using namespace std::chrono;

namespace Types
{
    class Patrons
    {
    public:
        int Id;
        string Name;
        int Barcode;

        string ToString();
    };

    class Books
    {
    public:
        int Id;
        int Barcode;
        string Title;
        string Author;
        string Description;

        string ToString();
    };

    class LibraryBooks
    {
    public:
        int Id;
        long LibraryBarcode;
        int BookId;

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