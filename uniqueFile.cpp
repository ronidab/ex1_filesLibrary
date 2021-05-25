//
// Created by User on 23/04/2021.
//
#include <iostream>
#include "uniqueFile.h"


uniqueFile::uniqueFile(const string& file_name) : title_name(file_name),my_file(new uniqF(file_name)) {
};

uniqueFile::uniqueFile(uniqueFile &lnk, const string& title) {
    title_name = title;
    lnk.my_file->refCount++;
    my_file = lnk.my_file;
};

uniqueFile& uniqueFile::operator=(uniqueFile &lnk){
    lnk.my_file->refCount++;
    my_file = lnk.my_file;
    return *this;
}

void uniqueFile::copyFile(uniqueFile *cpy) {
    //check if this function working good ???????
    open_file();
    cpy->open_file();
    fstream *cpy_file = cpy->getFile()->file;
    my_file->file->clear();
    cpy_file->seekg(0, ios::beg);
    my_file->file->seekg(0, ios::beg);

    string line;
    while (getline(*(my_file->file), line)) {
        *(cpy_file) << line;
    }
    close_file();
    cpy->close_file();
}

const uniqueFile &uniqueFile::operator[](int index) const throw(outOfUniqFileRangeException) {
    open_file();
    my_file->file->clear();
    my_file->file->seekg(0, ios::end);
    if (my_file->file->tellg() < index) {
        throw outOfUniqFileRangeException();
    }
    my_file->file->seekg(index, ios::beg);
    return *this;
}

uniqueFile::operator char() const {
    char res = my_file->file->get();
    close_file();
    return res;
}

uniqueFile &uniqueFile::operator[](int index) throw(outOfUniqFileRangeException) {
    open_file();
    my_file->file->clear();
    my_file->file->seekp(0, ios::end);

    if (my_file->file->tellg() < index) {
        throw outOfUniqFileRangeException();
    }
    my_file->file->seekp(index, ios::beg);
    return *this;
}

uniqueFile &uniqueFile::operator=(const char &c) {
    my_file->file->put(c);
    my_file->file->close();
    return *this;
}

void uniqueFile::cat() const {
    open_file();
    my_file->file->seekg(0, ios::beg);
    string line;
    while (getline(*my_file->file, line, '/')) {
        std::cout << line << endl;
    }
    close_file();
}

void uniqueFile::wc() const {
    cout << count_lines() << " " << count_words() << " " << count_chars() << endl;
}


int uniqueFile::count_lines() const{
    open_file();
    int counter;
    my_file->file->clear();
    my_file->file->seekg(0, ios::beg);
    string line;
    while (getline(*my_file->file, line)) {
        counter++;
    }
   close_file();
    return counter;
}

int uniqueFile::count_words() const {
    open_file();
    int counter;
    my_file->file->clear();
    my_file->file->seekg(0, ios::beg);
    string word;
    while (getline(*my_file->file, word, ' ')) {
        counter++;
    }
    close_file();
    return counter;
}

int uniqueFile::count_chars() const {
    open_file();
    my_file->file->clear();
    my_file->file->seekg(0, ios::beg);
    char byte;
    int counter;
    while (my_file->file->get(byte)) {
        if (byte != '\n') { counter++; }
    }
    close_file();
    return counter;
}