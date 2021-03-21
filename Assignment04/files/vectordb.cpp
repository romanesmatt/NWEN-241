#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>

#include "abstractdb.hpp"
#include "vectordb.hpp"

using namespace std;
using namespace nwen;

VectorDbTable::VectorDbTable(){
    rowsUsed = 0;
}

VectorDbTable:: ~VectorDbTable(){

}

bool VectorDbTable:: show(int rowNumber){

    /* Boundary checking */
    if(rowNumber < 0 || rowNumber > rows()){
        printf("Given row is outside boundaries of table.\n");
        return false;
    }
    /* Displaying contents of given row */
    cout << "Movie ID: " << table.at(rowNumber).id << ", Title: " << table.at(rowNumber).title
    << ", Year: " << table.at(rowNumber).year << ", Director: " << table.at(rowNumber).director <<endl;
 
    return true;

}


movie*VectorDbTable:: get(int rowNumber){

    /* Boundary checking */
    if(rowNumber < 0 || rowNumber > rows()){
        return nullptr;
    }

    movie *ptr = &table.at(rowNumber);
    return ptr;

}

bool VectorDbTable:: add(movie m){
    table.push_back(m);
    rowsUsed++;
    return true;
}


bool VectorDbTable:: update(int rowNumber, movie movie){

    /* Boundary checking */
    if(rowNumber < 0 || rowNumber > rows()){
        printf("Given row is outside boundaries of table.\n");
        return false;
    }
    else{
        /* Erasing contents of row before inserting new content */
        table.erase(table.begin() + rowNumber);

        /* Inserting the new contents */

        //Note: This way of inserting was inspired by an online solution
        //but NOT a direct copy
        table.insert(table.begin() + rowNumber, movie);
        return true;
    }

    return false; //if all else fails
}

bool VectorDbTable:: remove(unsigned long int movieId){
    bool isFound = false;
    int rowNumber;

    /* Searching for the movie with an ID that matches the given ID */
    for(int i = 0; i < rowsUsed; i++){
        if(table.at(i).id == movieId){
            rowNumber = i;
            isFound = true;
            break;
        }
    }

    if(!isFound){
        return false;
    }

    /* Erasing the contents that match the given movie ID */
    table.erase(table.begin() + rowNumber);

    rowsUsed--;
    return true;
}









