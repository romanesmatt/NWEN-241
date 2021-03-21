#ifndef __ABSTRACT_DB_HPP__
#define __ABSTRACT_DB_HPP__

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

/**
 * You will need to add the necessary class declaration for Task 4 in this
 * file.
 */

namespace nwen
{
    struct movie
    {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };

    class AbstractDbTable
    {
    public:
        virtual ~AbstractDbTable(){};
        //Returns amount of rows used in table
        virtual int rows(void) = 0;
        //Displays information shown in table
        virtual bool show(int) = 0;
        //Gets a movie from the structure from table
        virtual movie *get(int) = 0;
        //Adds given movie to table
        virtual bool add(movie) = 0;
        //Updates table
        virtual bool update(int, movie) = 0;
        //Removes movie from table via given ID
        virtual bool remove(unsigned long int) = 0;
        //loads the CSV file into the table;
        bool loadCSV(const char *info);
       
    };
} // namespace nwen

#endif /* __ABSTRACT_DB_HPP__ */





