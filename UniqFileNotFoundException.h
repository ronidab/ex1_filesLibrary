//
// Created by User on 23/04/2021.
//

#ifndef EX1_FILESLIBRARY_UNIQFILENOTFOUNDEXCEPTION_H
#define EX1_FILESLIBRARY_UNIQFILENOTFOUNDEXCEPTION_H

#include <exception>

using namespace std;

class UniqFileNotFoundException: public exception  {
public:
    virtual const char* what() const noexcept {return "ERROR: File Not Exist." ;}

};



#endif //EX1_FILESLIBRARY_UNIQFILENOTFOUNDEXCEPTION_H
