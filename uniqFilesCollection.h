
#ifndef EX1_FILESLIBRARY_uniqFilesCollection_H
#define EX1_FILESLIBRARY_uniqFilesCollection_H

#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "uniqueFile.h"
#include "UniqFileNotFoundException.h"
#include "directoryExistException.h"
#include "dirNotExistException.h"
#include <string>


class uniqFilesCollection {
private:
    map<uniqueFile*,string> files;
    vector<string> directories;
    string curr_dir_name;

public:
    uniqFilesCollection();

    uniqueFile* find_file_by_name (const string& file_name, const string& dir_name);  //returns pointer to uniqFile in files by file name
    bool find_dir_by_name (const string& dir_name);       //returns true if directory exist

    string& getCurrDir() { return curr_dir_name;}
    void write(const string& file_name,const string& dir_name, int index, char c) throw (UniqFileNotFoundException, outOfUniqFileRangeException);
    char read(const string& file_name,const string& dir_name, int index) throw (UniqFileNotFoundException, outOfUniqFileRangeException);
    void cat(const string& file_name,const string& dir_name) throw (UniqFileNotFoundException);
    void wc(const string& file_name,const string& dir_name) throw (UniqFileNotFoundException);
    void touch(const string& file_name, const string& dir_name);
    void copy(const string& src_file,const string& src_dir, string& dst_file, const string& dst_dir) throw (UniqFileNotFoundException);
    void remove(const string& del_file, const string& file_dir) throw (UniqFileNotFoundException);
    void move(const string& src_file, const string& src_dir, const string& dst_file, const string& dst_dir) throw (UniqFileNotFoundException);
    void ln(const string& tar_file, const string& tar_dir,  const string& link, const string& link_dir) throw (UniqFileNotFoundException);
    void mkdir(const string& dir_name) throw (directoryExistException);
    void chdir(const string& dir_name) throw (dirNotExistException);
    void rmdir(const string& dir_name) throw (dirNotExistException);
    void ls();
    void lproot();
    void pwd() const;



};

bool dir_inside_dir(const string &main_dir, const string &sub_dir);
//string& separate_dir_from_root(const string &dir_with_root);


#endif //EX1_FILESLIBRARY_uniqFilesCollection_H
