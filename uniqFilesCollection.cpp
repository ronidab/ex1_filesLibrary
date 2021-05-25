//
// Created by User on 23/04/2021.
//

#include "uniqFilesCollection.h"

//global touch function
void ftouch(const string &file) {
    ofstream xfile;
    xfile.open(file);
    xfile.flush();
    xfile.close();
}

uniqFilesCollection::uniqFilesCollection() : files(map<uniqueFile *, string>()), directories(vector<string>()),
                                             curr_dir_name("V/") {
    directories.push_back(curr_dir_name);
};

uniqueFile *uniqFilesCollection::find_file_by_name(const string &file_name, const string &dir_name) {
    for (auto file : files) {
        if ((file.first->toString()) == (file_name) && (file.second == dir_name)) {
            return file.first;
        }
    }
    return nullptr;
}

bool uniqFilesCollection::find_dir_by_name(const string &dir_name) {
    if (!dir_name.empty()) {
        for (vector<string>::iterator i = directories.begin(); i != directories.end(); i++) {
            if ((*i) == (dir_name)) {
                return true;
            }
        }
    }
    return false;
}

void uniqFilesCollection::write(const string &file_name, const string &dir_name, int index,
                                char c) throw(UniqFileNotFoundException, outOfUniqFileRangeException) {
    uniqueFile *change_file = find_file_by_name(file_name, dir_name);
    if (change_file == nullptr) {
        throw UniqFileNotFoundException();
    }
    (*change_file)[index] = c;
}

char uniqFilesCollection::read(const string &file_name, const string &dir_name,
                               int index) throw(UniqFileNotFoundException, outOfUniqFileRangeException) {
    uniqueFile *read_file = find_file_by_name(file_name, dir_name);
    if (read_file == nullptr) { throw UniqFileNotFoundException(); }
    return ((*read_file)[index]);
}

void uniqFilesCollection::cat(const string &file_name, const string &dir_name) throw(UniqFileNotFoundException) {
    uniqueFile *cat_file = find_file_by_name(file_name, dir_name);
    if (cat_file == nullptr) { throw UniqFileNotFoundException(); }
    cat_file->cat();
}

void uniqFilesCollection::wc(const string &file_name, const string &dir_name) throw(UniqFileNotFoundException) {
    uniqueFile *wc_file = find_file_by_name(file_name, dir_name);
    if (wc_file == nullptr) { throw UniqFileNotFoundException(); }
    wc_file->wc();
}

void uniqFilesCollection::touch(const string &file_name, const string &dir_name) {
    if (find_file_by_name(file_name, dir_name) == nullptr) {
        files.insert(pair<uniqueFile *, string>(new uniqueFile(file_name), dir_name));
    }
    ftouch(file_name);
}

void uniqFilesCollection::copy(const string &src_file, const string &src_dir, string &dst_file,
                               const string &dst_dir) throw(UniqFileNotFoundException) {
    //copy src file to dst file
    uniqueFile *src = find_file_by_name(src_file, src_dir);
    if (src == NULL) {
        throw UniqFileNotFoundException();
    }
    uniqueFile *dst = find_file_by_name(dst_file, dst_dir);

    if (dst == NULL) {
        dst = new uniqueFile(dst_file);
        files.insert(pair<uniqueFile *, string>(dst, dst_dir));
    }
    src->copyFile(dst);
}

void uniqFilesCollection::remove(const string &del_file, const string &file_dir) throw(UniqFileNotFoundException) {
    if (!find_file_by_name(del_file, file_dir)) {
        throw UniqFileNotFoundException();
    }
    map<uniqueFile *, string>::iterator it = files.begin();
    for (; it != files.end(); it++) {
        if (((*it).first->toString() == del_file) && ((*it).second == file_dir)) {
            uniqueFile *del = (*it).first;
            files.erase(it);
            delete del;
            break;
        }
    }
}

void uniqFilesCollection::move(const string &src_file, const string &src_dir, const string &dst_file,
                               const string &dst_dir) throw(UniqFileNotFoundException) {
    //*copy src to dst
    //*delete src
    copy(src_file, src_dir, const_cast<string &>(dst_file), dst_dir);
    remove(src_file, src_dir);
}

void uniqFilesCollection::ln(const string &tar_file, const string &tar_dir, const string &link,
                             const string &link_dir) throw(UniqFileNotFoundException) {
    //*link will be link to file -> current link file won't be exist anymore
    //*file must be exist
    uniqueFile *exist_file = find_file_by_name(tar_file, tar_dir);
    if (exist_file == nullptr) {
        throw UniqFileNotFoundException();
    }
    uniqueFile *link_file = find_file_by_name(link, link_dir);
    if (link_file == nullptr) {
        //link file dose not exist
        //create it here
        link_file = new uniqueFile(*exist_file, link);
        files.insert(pair<uniqueFile *, string>(link_file, link_dir));
    } else {
        *link_file = *exist_file;
    }
}

void uniqFilesCollection::mkdir(const string &dir_name) throw(directoryExistException) {
    if (find_dir_by_name(dir_name)) {
        throw directoryExistException();
    }
    directories.push_back(dir_name);
}

void uniqFilesCollection::chdir(const string &dir_name) throw(dirNotExistException) {
    if (!find_dir_by_name(dir_name)) {
        throw dirNotExistException();
    }
    curr_dir_name = dir_name;
}

bool dir_inside_dir(const string &main_dir, const string &sub_dir) {
    //returns true if dir sub root contains dir main name
    int len = main_dir.size();
    if (sub_dir.substr(0, len) == main_dir) {
        return true;
    }
    return false;
}

void uniqFilesCollection::rmdir(const string &del_dir_name) throw(dirNotExistException) {

    if (find_dir_by_name(del_dir_name)) {
        //1.delete dir and dirs inside dir from directories vector
        auto i = directories.begin();
        while (i != directories.end()) {
            if (dir_inside_dir(del_dir_name, (*i))) {
                directories.erase(i);
            } else { i++; }
        }


        //2.delete all files inside directory
        auto it = files.begin();
        while (it != files.end()) {
            if (dir_inside_dir(del_dir_name, (*it).second)) {
                uniqueFile *del_file = (*it).first;
                files.erase(it++);
                delete del_file;
            } else { it++; }


        }
    } else { throw dirNotExistException(); }

    if (curr_dir_name == del_dir_name) { curr_dir_name = "V/"; }

}


void uniqFilesCollection::ls() {
    cout << curr_dir_name << ":" << endl;
    //*first prints files inside current directory
    //*then prints directories inside current directory
    for (map<uniqueFile *, string>::iterator it = files.begin(); it != files.end(); it++) {
        if (curr_dir_name == ((*it).second)) {
            cout << (*it).first->getFile()->file_name << endl;
        }
    }
    for (int i = 0; i < directories.size(); i++) {
        if (dir_inside_dir(curr_dir_name, directories[i])) {
            if(curr_dir_name != directories[i]){cout << directories[i] <<endl;}

        }
    }

}

void uniqFilesCollection::lproot() {
    //sorts directories by amount of '/'
    std::sort(directories.begin(), directories.end(), [](string a, string b) -> bool {
        return std::count(a.begin(), a.end(), '/') < std::count(b.begin(), b.end(), '/');
    });
    for (int i = 0; i < directories.size(); i++) {
        string print_dir = directories[i];
        cout << print_dir << ":" << endl;
        for (map<uniqueFile *, string>::iterator it = files.begin(); it != files.end(); it++) {
            if ((*it).second == print_dir) {
                cout << ((*it).first)->toString() << " " << (*it).first->getRF() << endl;
            }
        }
    }
}

void uniqFilesCollection::pwd() const {
    cout << curr_dir_name << endl;
}




