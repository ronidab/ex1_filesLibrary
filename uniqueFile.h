#ifndef EX1_FILESLIBRARY_UNIQUEFILE_H
#define EX1_FILESLIBRARY_UNIQUEFILE_H


#include <fstream>
#include "outOfUniqFileRangeException.h"

using namespace std;

class uniqueFile {
private:
    string title_name;

    struct uniqF {
        uniqF(const string& file_name) : file(new fstream(file_name.c_str(), ios::app)),
                                       file_name(file_name), refCount(1) {file->close(); }

        fstream *file;
        string file_name;
        int refCount;

        ~uniqF() { if (--refCount == 0) {
            //*in case of someone will create a file in the same name, it has to be empty file
                file->open(file_name,ios::out);
                file->write("",0);
                file->close();
                delete file; }};
    };

    uniqF *my_file;


    void open_file() const { my_file->file->open(my_file->file_name); }

    void close_file() const { my_file->file->close(); }

    int count_lines() const;

    int count_words() const;

    int count_chars() const;

public:
    uniqueFile(const string& file_name);
    uniqueFile(uniqueFile &src, const string& title);

    uniqueFile& operator=(uniqueFile &src);
    uniqF *getFile() { return my_file; }

    int getRF() { return my_file->refCount; }

    const uniqueFile &operator[](int index) const throw(outOfUniqFileRangeException);

    operator char() const;

    uniqueFile &operator[](int index) throw(outOfUniqFileRangeException);

    uniqueFile &operator=(const char &);

    void cat() const;

    void wc() const;

    void copyFile(uniqueFile *cpy);

    string toString() const {return title_name;}

    ~uniqueFile() { delete my_file; }



};


#endif //EX1_FILESLIBRARY_UNIQUEFILE_H
