//
// Created by User on 23/04/2021.
//

#ifndef EX1_FILESLIBRARY_outOfUniqFileRangeException_H
#define EX1_FILESLIBRARY_outOfUniqFileRangeException_H

#include <exception>

using namespace std;

class outOfUniqFileRangeException: public exception  {
public:
    virtual const char* what() const noexcept{ return "ERROR: Index Out Of File Range";}

};


#endif //EX1_FILESLIBRARY_outOfUniqFileRangeException_H
