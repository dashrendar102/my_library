// commands.cpp : executes code specific to each command line command
//

#include "commands.h"

namespace Command
{
    void ListBooks()
    {
        try
        {
            char *connStr = getenv("DATABASE_URL");

            if (connStr == nullptr)
            {
                cerr << "No connection string in ENV. Cannot connect." << endl;
                return;
            }

            connection c(connStr);

            work w(c);
            row r = w.exec1("SELECT 1");
            w.commit();

            cout << "GOT ROW: " << r[0].as<int>() << endl;
        }
        catch (exception const &e)
        {
            cerr << e.what() << endl;
        }
        cout << "All books" << endl;
    }
}