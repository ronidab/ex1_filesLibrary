//
// Created by User on 24/04/2021.
//

#ifndef EX1_FILESLIBRARY_DIRNOTEXISTEXCEPTION_H
#define EX1_FILESLIBRARY_DIRNOTEXISTEXCEPTION_H
class dirNotExistException: public exception  {
public:
    virtual const char* what() const noexcept{ return "ERROR: Directory not Exist."; }

};
#endif //EX1_FILESLIBRARY_DIRNOTEXISTEXCEPTION_H
