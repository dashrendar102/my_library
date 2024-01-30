// library.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <map>

#include "commands.h"
#include "types.h"

using namespace std;

map<string, Command::CommandType> commandMapping = {
    {"l", Command::CommandType::List},
    {"list", Command::CommandType::List},

    {"g", Command::CommandType::Get},
    {"get", Command::CommandType::Get},

    {"h", Command::CommandType::Help},
    {"help", Command::CommandType::Help},

    {"n", Command::CommandType::New},
    {"new", Command::CommandType::New},

    {"u", Command::CommandType::Update},
    {"update", Command::CommandType::Update},

    {"d", Command::CommandType::Delete},
    {"delete", Command::CommandType::Delete}};

map<string, Types::DBTable> dbTableMapping = {
    {"b", Types::DBTable::Book},
    {"book", Types::DBTable::Book},
    {"books", Types::DBTable::Book},

    {"lb", Types::DBTable::LibraryBook},
    {"library_book", Types::DBTable::LibraryBook},
    {"library_books", Types::DBTable::LibraryBook},

    {"p", Types::DBTable::Patrons},
    {"patron", Types::DBTable::Patrons},
    {"patrons", Types::DBTable::Patrons},

    {"l", Types::DBTable::Loans},
    {"loan", Types::DBTable::Loans},
    {"loans", Types::DBTable::Loans}};