#include <iostream>
#include <cstring>
#include <cstdlib>

#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>


#include "abstractdb.hpp"

using namespace std;
using namespace nwen;


/**
* Loads data from file into database
*/
bool loadCSV(const char *info)
{
    /* If the given file contains nothing */
    if (info == nullptr)
    {
        return false;
    }

    ifstream csv;

    /* If file can't be opened for whatever reason */
    csv.open(info);
    if (!csv.is_open())
    {
        printf("Opening of csv file failed.\n");
        return false;
    }

    movie m;
    while (!csv.eof())
    {
        string s;

        /* Movie ID */
        if (!getline(csv, s, ','))
            break;
        if (atoi(s.c_str()) == 0)
        {
            csv.close();
            return false;
        }
        m.id = atoi(s.c_str());

        /* Movie Title */
        if (!getline(csv, s, ','))
            break;
        if (s.size() > 50 || s.size() == 0)
        {
            csv.close();
            return false;
        }
        strncpy(m.title, s.c_str(), s.length() + 1);

        /* Movie Year */
        if (!getline(csv, s, ','))
            break;
        if (s.size() != 4 || atoi(s.c_str()) == 0)
        {
            csv.close();
            return false;
        }
        m.year = atoi(s.c_str());

        /* Movie Director */
        if (!getline(csv, s))
            break;
        if (s.size() > 50 || s.size() == 0)
        {
            csv.close();
            return false;
        }
        strncpy(m.director, s.c_str(), s.length());
        // add(m);
        
    }
    csv.close();
    return true;
}