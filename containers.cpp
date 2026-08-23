#include <iostream>
#include <array>
#include <vector>
#include <print>

void arrays(std::array<int,5>& arr){
// arrays are fixed size. 
std::cout<<arr.at(1)<<'\n';
std::cout<<arr.size()<<'\n';
std::cout<<arr.front()<<'\n';
std::cout<<arr.back()<<'\n';
std::cout<<*arr.begin()<<'\n'; //same as front but returns iterator.
std::cout<<*arr.end()<<'\n'; //same as front but returns iterator.
std::cout<<arr.empty()<<'\n'; 
std::cout<<arr.max_size()<<'\n'; //same as front but returns iterator.

for(int i=0; i<arr.size();++i){
    std::cout<<arr[i]<<'\n';
};
//same with iterator
for(std::array<int,5>::iterator it=arr.begin();it!=arr.end();++it){
std::cout<<*it<<'\n';
};

// in sytnax
for(int&num: arr){
    std::cout<<num<<'\n';
};
};

void vector(std::vector<int>& vec){
// vectors are dynamic array. size can update in heap.
std::cout<<vec.at(1)<<'\n';
std::cout<<vec.size()<<'\n';
std::cout<<vec.front()<<'\n';
std::cout<<vec.back()<<'\n';
std::cout<<*vec.begin()<<'\n'; //same as front but returns iterator.
std::cout<<*vec.end()<<'\n'; //same as front but returns iterator

std::cout<<vec.size()<<'\n'; // vec size
std::cout<<vec.capacity()<<'\n';  // total reserved capcaity >=size.
vec.reserve(10); // reserve capacity.
vec.resize(10); //resize ved.
std::cout<<vec.size()<<'\n'; // vec size

vec.push_back(5);
vec.push_back(5);
vec.push_back(5);

for(int i=0; i<vec.size();++i){
    std::cout<<vec[i]<<'\n';
};
//same with iterator
for(std::vector<int>::iterator it=vec.begin();it!=vec.end();++it){
std::cout<<*it<<'\n';
};

// in sytnax
for(int&num: vec){
    std::cout<<num<<'\n';
};

//remove element
vec.erase(vec.begin()+2);
  std::cout<<vec.size()<<'\n';

};

int main(){
    std::cout<<"main function"<<'\n';

    std::array<int,5> arr ={1,2,3};
    std::cout<<arr[0]<<'\n'<<arr[4]<<'\n';
    arrays(arr);

    std::vector<int> vec ={1,2,3};
    std::cout<<vec[0]<<'\n'<<vec[4]<<'\n';
    vector(vec);

};