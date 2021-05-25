//
// Created by User on 24/04/2021.
//

#ifndef EX1_FILESLIBRARY_DIRECTORYEXISTEXCEPTION_H
#define EX1_FILESLIBRARY_DIRECTORYEXISTEXCEPTION_H
using namespace std;

class directoryExistException: public exception  {
public:
    virtual const char *what() const noexcept{ return "ERROR: Name Of Directory Already Exist."; }

};



#endif //EX1_FILESLIBRARY_DIRECTORYEXISTEXCEPTION_H
