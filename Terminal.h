//
// Created by User on 28/04/2021.
//

#ifndef EX1_FILESLIBRARY_TERMINAL_H
#define EX1_FILESLIBRARY_TERMINAL_H


#include "uniqFilesCollection.h"
#include <string>

using namespace std;

enum Orders {read,write,touch,copy,rm,move,cat,wc,ln,mkdir,chdir,rmdir,ls,lproot,pwd,Exit};

class Terminal {
private:
    uniqFilesCollection all_dirs_files;
    map<string,Orders> trans_orders;

    Orders ord;
    string ord_dir, ord_file, other_dir, other_file;
    char character;
    int position;
public:
    Terminal();
    void run();
    void read_order();
    void separate_file_from_dir(const string& file_with_dir, bool other);

};


#endif //EX1_FILESLIBRARY_TERMINAL_H
