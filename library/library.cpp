// library.cpp : Defines the entry point for the application.
//

#include <algorithm>
#include "library.h"

const string LIST_HELP = "list                                                     List books in library";
const string GET_HELP = "get <barcode>                                            Get book from library by library barcode";
const string HELP_HELP = "help <command>                                           Get help for a particular command";
const string NEW_HELP = "new [book|library_book] <properties>                     Creates a new book or library book";
const string UPDATE_HELP = "update [book|library_book] <barcode> <property> <value>  Updates a book property";
const string DELETE_HELP = "delete [book|library_book] <barcode>                     Deletes a given resource by barcode";

void printUsage()
{
	cout << "usage: LibraryConsole <command>" << endl;
	cout << LIST_HELP << endl;
	cout << GET_HELP << endl;
	cout << HELP_HELP << endl;
	cout << NEW_HELP << endl;
	cout << UPDATE_HELP << endl;
	cout << DELETE_HELP << endl;
}

void handleHelp(int argc, char *argv[])
{
	if (argc < 3)
	{
		printUsage();
	}
	else
	{
		switch (commandMapping[argv[2]])
		{
		case Command::CommandType::List:
			cout << "Lists all books in the library by library barcode (not publisher barcode)" << endl;
			break;

		case Command::CommandType::Get:
			cout << GET_HELP << endl;
			cout << "Library barcode is different from publisher barcode" << endl;
			break;

		case Command::CommandType::New:
			cout << NEW_HELP << endl;
			cout << "For a new book you'll need to enter (in this order):" << endl;
			cout << " * Publisher barcode" << endl;
			cout << " * Title" << endl;
			cout << " * Author" << endl;
			cout << " * Description" << endl
				 << endl;
			cout << "Example:" << endl;
			cout << "./library new book 123454321 \"Libraries for Dummies\" \"Mike Hat\" \"A book about building a library\"" << endl
				 << endl;
			cout << "For a new library book (ie, with library-specific barcode) you'll need:" << endl;
			cout << " * Library barcode (specific to the library)" << endl;
			cout << " * Publisher barcode (same accross all copies of the same book)" << endl
				 << endl;
			cout << "Example:" << endl;
			cout << "./library new library_book 45677654 123454321" << endl;
			break;

		case Command::CommandType::Update:
			cout << UPDATE_HELP << endl;
			cout << "To update a book or library book you'll need to enter:" << endl;
			cout << "./library update [book|library_book] <barcode> <field> <value>" << endl;
			cout << "possible book fields are: title, author, description" << endl;
			cout << "possible library_book fields are: book_barcode" << endl
				 << endl;
			cout << "Example:" << endl;
			cout << "./library update book 123454321 title \"Libraries for Smarties\"" << endl;
			break;

		case Command::CommandType::Delete:
			cout << DELETE_HELP << endl;
			cout << "Deletes a given book or library_book by barcode" << endl;
			cout << "If a book is deleted, all respective library books will be deleted" << endl
				 << endl;
			cout << "Example:" << endl;
			cout << "./library delete library_book 45677654" << endl;
			break;

		default:
			cerr << "Unknown command " << argv[2] << endl;

		case Command::CommandType::Help:
			cout << HELP_HELP << endl;
			break;
		}
	}
}

void handleGet(int argc, char *argv[])
{
	if (argc < 3)
	{
		cerr << "You need to pass a barcode as well" << endl;
		cerr << GET_HELP << endl;
	}
	else
	{
		string param = string(argv[2]);
		if (all_of(param.begin(), param.end(), ::isdigit))
		{
			Command::GetBookByBarcode(argv[2]);
		}
		else
		{
			cerr << "Barcode must be a number" << endl;
			cerr << GET_HELP << endl;
		}
	}
}

void handleNewBook(int argc, char *argv[])
{
	if (argc < 7)
	{
		cerr << "Insufficient properties to create a new book" << endl;
		cerr << "See ./library help new" << endl;
	}
	else
	{
		Command::NewBook(argv[3], argv[4], argv[5], argv[6]);
	}
}

void handleNewLibraryBook(int argc, char *argv[])
{
	if (argc < 5)
	{
		cerr << "Insufficient properties to create a new library book" << endl;
		cerr << "See ./library help new" << endl;
	}
	else
	{
		Command::NewLibraryBook(argv[3], argv[4]);
	}
}

void handleNew(int argc, char *argv[])
{
	if (argc < 3)
	{
		cerr << "Needs a resource type (book or library_book) to create." << endl;
		cerr << "See ./library help new" << endl;
	}
	else
	{
		switch (dbTableMapping[argv[2]])
		{
		case Types::DBTable::Book:
			handleNewBook(argc, argv);
			break;

		case Types::DBTable::LibraryBook:
			handleNewLibraryBook(argc, argv);
			break;

		case Types::DBTable::NotFound:
			cerr << "Invalid resource type. Must be book or library_book." << endl;

		default:
			cerr << "See ./library help new" << endl;
		}
	}
}

bool isValidColumnChar(int c)
{
	return islower(c) || isdigit(c) || c == '_';
}

void handleUpdate(int argc, char *argv[])
{
	if (argc < 6)
	{
		cerr << "Needs a resource type (book or library_book) to update, the related barcode, a property, and a new value." << endl;
		cerr << "See ./library help update" << endl;
	}
	else
	{
		Types::DBTable table = dbTableMapping[argv[2]];

		if (table == Types::DBTable::NotFound)
		{
			cerr << "Invalid resource type. Must be book or library book." << endl;
			cerr << "See ./library help update" << endl;
		}
		else
		{
			string barcode = string(argv[3]);
			string column = string(argv[4]);

			if (all_of(barcode.begin(), barcode.end(), ::isdigit) &&
				all_of(column.begin(), column.end(), isValidColumnChar))
			{
				Command::Update(table, atol(argv[3]), argv[4], argv[5]);
			}
			else
			{
				cerr << "Barcode must be a valid number and column a valid column." << endl;
				cerr << "See ./library help update" << endl;
			}
		}
	}
}

void handleDelete(int argc, char *argv[])
{
	if (argc < 4)
	{
		cerr << "Needs a resource type (book or library_book) to update and the related barcode." << endl;
		cerr << "See ./library help delete" << endl;
	}
	else
	{
		Types::DBTable table = dbTableMapping[argv[2]];

		if (table == Types::DBTable::NotFound)
		{
			cerr << "Invalid resource type. Must be book or library book." << endl;
			cerr << "See ./library help delete" << endl;
		}
		else
		{
			string barcode = string(argv[3]);
			if (all_of(barcode.begin(), barcode.end(), ::isdigit))
			{
				Command::Delete(table, atol(argv[3]));
			}
			else
			{
				cerr << "Barcode must be a valid number." << endl;
				cerr << "See ./library help delete" << endl;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		switch (commandMapping[argv[1]])
		{
		case Command::CommandType::List:
			Command::ListBooks();
			break;

		case Command::CommandType::Get:
			handleGet(argc, argv);
			break;

		case Command::CommandType::New:
			handleNew(argc, argv);
			break;

		case Command::CommandType::Update:
			handleUpdate(argc, argv);
			break;

		case Command::CommandType::Delete:
			handleDelete(argc, argv);
			break;

		default:
			cout << "Command " << argv[1] << " not found!" << endl;
			// no break to continue to provide help info

		case Command::CommandType::Help:
			handleHelp(argc, argv);
			break;
		}
	}
	else
	{
		printUsage();
	}

	return 0;
}
