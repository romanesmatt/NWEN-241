#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "abstractdb.hpp"

using namespace std;

 // namespace nwen

 namespace nwen
{
    class VectorDbTable : AbstractDbTable
    {
    public:
        //temporary
        VectorDbTable();
        ~VectorDbTable();

        bool show(int);
        movie *get(int);
        bool add(movie);
        bool remove(unsigned long int);
        bool update(int, movie);
        int rows()
        {
            return rowsUsed;
        };


        vector<movie> table;
        int rowsUsed;
    };

}



