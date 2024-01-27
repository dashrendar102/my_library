// commands.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <map>
#include <string>
#include <iostream>

using namespace std;

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