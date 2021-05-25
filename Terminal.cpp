#include "Terminal.h"

Terminal::Terminal() : trans_orders(map<string, Orders>()) {
    trans_orders.insert(pair<string, Orders>("read", read));
    trans_orders.insert(pair<string, Orders>("write", write));
    trans_orders.insert(pair<string, Orders>("touch", touch));
    trans_orders.insert(pair<string, Orders>("copy", Orders::copy));
    trans_orders.insert(pair<string, Orders>("remove", rm));
    trans_orders.insert(pair<string, Orders>("move", Orders::move));
    trans_orders.insert(pair<string, Orders>("cat", cat));
    trans_orders.insert(pair<string, Orders>("wc", wc));
    trans_orders.insert(pair<string, Orders>("ln", ln));
    trans_orders.insert(pair<string, Orders>("mkdir", mkdir));
    trans_orders.insert(pair<string, Orders>("chdir", chdir));
    trans_orders.insert(pair<string, Orders>("rmdir", rmdir));
    trans_orders.insert(pair<string, Orders>("ls", ls));
    trans_orders.insert(pair<string, Orders>("lproot", lproot));
    trans_orders.insert(pair<string, Orders>("pwd", pwd));
    trans_orders.insert(pair<string, Orders>("exit", Exit));
};

void Terminal::separate_file_from_dir(const string &file_with_dir, bool other) {
    //*first count num of '/' in root
    //*if there is no '/' -> dir = current dir
    //*else find the position of the last '/' and initialized ord_dir & ord_file
    int slash_nums = count(file_with_dir.begin(), file_with_dir.end(), '/');
    if (slash_nums == 0) {
        if (other) {
            //*can use depolatively current directory only for first argument
            other_dir = "";
            other_file = file_with_dir;
        } else {
            ord_dir = all_dirs_files.getCurrDir();
            ord_file = file_with_dir;
        }
    } else {
        int count = 0, i = 0;

        while (count < slash_nums) {
            if (file_with_dir[i++] == '/') {
                count++;
            }
        }
        if (other) {
            other_dir = file_with_dir.substr(0, i);
            other_file = file_with_dir.substr(i, file_with_dir.size() - 1);
        } else {
            ord_dir = file_with_dir.substr(0, i);
            ord_file = file_with_dir.substr(i, file_with_dir.size() - 1);
        }
    }

}

void Terminal::read_order() {
    string ord_input, file_with_dir, other_file_dir;
    cin >> ord_input;
    ord = trans_orders.find(ord_input)->second;

    if (ord == read) {
        cin >> file_with_dir;
        cin >> position;
    } else if (ord == write) {
        cin >> file_with_dir;
        cin >> position;
        cin >> character;
    } else if (ord == touch | ord == rm | ord == cat | ord == wc) { cin >> file_with_dir; }
    else if (ord == Orders::copy | ord == Orders::move | ord == ln) {
        cin >> file_with_dir;
        cin >> other_file_dir;
    } else if (ord == mkdir | ord == chdir | ord == rmdir ) { cin >> ord_dir; }

    if (!file_with_dir.empty()) { separate_file_from_dir(file_with_dir, false); }
    if (!other_file_dir.empty()) { separate_file_from_dir(other_file_dir, true); }
}

void Terminal::run() {
    bool con_flag = true;
    while (con_flag) {
        read_order();
        try {
            switch (ord) {
                case read: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    char c = all_dirs_files.read(ord_file, ord_dir, position);
                    cout << c << endl;
                    break;
                }
                case write: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    all_dirs_files.write(ord_file, ord_dir, position, character);
                    break;
                }
                case touch: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    all_dirs_files.touch(ord_file, ord_dir);
                    break;
                }
                case Orders::copy: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    if(!all_dirs_files.find_dir_by_name(other_dir)){throw dirNotExistException();}
                    all_dirs_files.copy(ord_file, ord_dir, other_file, other_dir);
                    break;
                }
                case rm: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    all_dirs_files.remove(ord_file, ord_dir);
                    break;
                }
                case Orders::move: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    if(!all_dirs_files.find_dir_by_name(other_dir)){throw dirNotExistException();}
                    all_dirs_files.move(ord_file, ord_dir, other_file, other_dir);
                    break;
                }
                case cat: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    all_dirs_files.cat(ord_file, ord_dir);
                    break;
                }
                case wc: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    all_dirs_files.wc(ord_file, ord_dir);
                    break;
                }
                case ln: {
                    if(!all_dirs_files.find_dir_by_name(ord_dir)){throw dirNotExistException();}
                    if(!all_dirs_files.find_dir_by_name(other_dir)){throw dirNotExistException();}
                    if(ord_file.empty() || other_file.empty()){cerr << "ERROR: system can link only files. "<<endl;}
                    else{all_dirs_files.ln(ord_file, ord_dir, other_file, other_dir);}
                    break;
                }
                case mkdir: {
                    if(!dir_inside_dir(all_dirs_files.getCurrDir(),ord_dir)){
                        string tmp = all_dirs_files.getCurrDir() + ord_dir;
                        ord_dir=tmp;
                    }
                    all_dirs_files.mkdir(ord_dir);
                    break;
                }
                case chdir: {
                    if(ord_dir.substr(0,2 ) != "V/"){
                        //*if name is not included full root, then its a directory inside current directory
                        string tmp = all_dirs_files.getCurrDir() + ord_dir;
                        ord_dir=tmp;
                    }
                    all_dirs_files.chdir(ord_dir);
                    break;
                }
                case rmdir: {
                    if(!dir_inside_dir(all_dirs_files.getCurrDir(),ord_dir)){
                        string tmp = all_dirs_files.getCurrDir() + ord_dir;
                        ord_dir=tmp;
                    }
                    all_dirs_files.rmdir(ord_dir);
                    break;
                }
                case ls: {
                    all_dirs_files.ls();
                    break;
                }
                case lproot: {
                    all_dirs_files.lproot();
                    break;
                }
                case pwd: {
                    all_dirs_files.pwd();
                    break;
                }
                case Exit: {
                    con_flag = false;
                    break;
                }
                default: {
                    cerr << "ERROR: Unknown Order." << endl;
                    break;
                }
            }

        }
        catch (exception& e){
            cerr << e.what() <<endl;
        }
    }

}