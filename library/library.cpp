// library.cpp : Defines the entry point for the application.
//

#include "library.h"

map<string, Command::CommandType> commandMapping = {
	{"l", Command::CommandType::List},
	{"list", Command::CommandType::List},

	{"g", Command::CommandType::Get},
	{"get", Command::CommandType::Get},

	{"h", Command::CommandType::Help},
	{"help", Command::CommandType::Help}};

int main(int argc, char *argv[])
{
	cout << "Hello CMake." << endl;
	cout << argc << " args" << endl;

	if (argc > 1 && argv[1] != nullptr)
	{
		switch (commandMapping[argv[1]])
		{
		case Command::CommandType::List:
			Command::ListBooks();
			break;

		case Command::CommandType::Get:
			cout << "GET" << endl;
			break;

		default:
			cout << "Command " << argv[1] << " not found!" << endl;
			// no break to continue to provide help info

		case Command::CommandType::Help:
			cout << "usage: LibraryConsole <command>" << endl;
			cout << "list             List books in library" << endl;
			cout << "get              Get book from library" << endl;
			cout << "help <command>   Get help for a particular command" << endl;
			break;
		}
	}

	return 0;
}
