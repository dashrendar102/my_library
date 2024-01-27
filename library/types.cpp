// types.cpp : Defines basic types of data stored in the library.
//

#include "types.h"

namespace Types
{
    string StrJoin(vector<string> values, string delimiter)
    {
        if (values.size() == 0)
        {
            return "";
        }

        stringstream toReturn;

        bool hasRunOnce = false;

        for (string value : values)
        {
            if (hasRunOnce)
            {
                toReturn << delimiter;
            }
            else
            {
                hasRunOnce = true;
            }

            toReturn << value;
        }

        return toReturn.str();
    }

    string TimePointToString(time_point<system_clock, duration<int>> date)
    {
        time_t clockTime = system_clock::to_time_t(date);
        tm localTime = *localtime(&clockTime);

        return StrJoin({to_string(localTime.tm_mon), to_string(localTime.tm_mday), to_string(localTime.tm_year)}, "-");
    }

    string Patrons::ToString()
    {
        return StrJoin({to_string(Id), Name, to_string(Barcode)}, ", ");
    }

    string Books::ToString()
    {
        return Id + ", " +
               to_string(Barcode) + ", " +
               Title + ", " +
               Author + ",\n" +
               Description;
    }

    string LibraryBooks::ToString()
    {
        return Id + ", " +
               to_string(LibraryBarcode) + ", " +
               to_string(BookId) + ", ";
    }

    string Loans::ToString()
    {
        time_t clockStartTime = system_clock::to_time_t(StartDate);
        tm localStartTime = *localtime(&clockStartTime);

        string strStart = TimePointToString(StartDate);

        return Id + ", " +
               to_string(LibraryBookId) + ", " +
               to_string(PatronId) + ", " +
               strStart;
    }
}