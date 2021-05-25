cmake_minimum_required(VERSION 3.17)
project(ex1_filesLibrary)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex1_filesLibrary main.cpp uniqueFile.cpp uniqueFile.h outOfUniqFileRangeException.h UniqFileNotFoundException.h uniqFilesCollection.cpp uniqFilesCollection.h directoryExistException.h dirNotExistException.h Terminal.cpp Terminal.h)