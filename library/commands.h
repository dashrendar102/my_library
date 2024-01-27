// commands.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <map>
#include <string>
#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

namespace Command
{
    enum class CommandType
    {
        NotFound = 0,
        List,
        Get,
        Help
    };

    void ListBooks();
}