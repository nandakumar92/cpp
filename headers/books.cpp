#include <iostream>
#include "books.h"



 std::unordered_map<int,std::string> createBooks(std::unordered_map<int,std::string>& temp){
    temp.insert({1,"book1"});
    temp.insert({2,"book2"});
    temp.insert({3,"book3"});
    return temp;
};

std::unordered_map<int,std::string> getBooks(){
    std::unordered_map<int,std::string> temp={};
    return createBooks(temp);
};

