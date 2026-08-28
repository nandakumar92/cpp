#include <iostream>
#include <array>
#include <vector>
#include <print>
#include <unordered_map>
#include <utility>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>

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

std::println("{}", vec);
};

void unordered_map(std::unordered_map<int,int>& map){
   // hashmap
    std::cout<<map.size()<<'\n';
    std::cout<<map.empty()<<'\n';
    map.insert({3,3});
    std::cout<<map[3]<<'\n';
    std::cout<<map.size()<<'\n';
    map.insert({4,4});
    map.insert({5,5});
    std::println("{}", map);

    for(auto& [k,v]:map){
        std::cout<<k<<'\n'<<v<<'\n';
    }

    for(auto item:map){
        std::cout<<item.first<<":"<<item.second;
    }
};

void omap(std::map<int,int>& omap){
// ordered hashmap , keys are unique
    std::cout<<omap.size()<<'\n';
    std::cout<<omap.empty()<<'\n';
    omap.insert({3,3});
    std::cout<<omap[3]<<'\n';
    std::cout<<omap.size()<<'\n';
    omap.insert({4,4});
    omap.insert({5,5});
    std::println("{}", omap);

    for(auto& [k,v]:omap){
        std::cout<<k<<'\n'<<v<<'\n';
    }
};

void unordered_set(std::unordered_set<int>& set){
    //set unique elements
    std::cout<<set.size()<<'\n';
    std::cout<<set.empty()<<'\n';   
    set.insert(1);
    set.insert(1);
    set.insert(2);
    set.insert(3);
    std::println("{}",set);
    std::cout<<*set.find(3)<<'\n';   
};

void oset(std::set<int>& oset){
    //ordered set unique elements
    std::cout<<oset.size()<<'\n';
    std::cout<<oset.empty()<<'\n';   
    oset.insert(1);
    oset.insert(1);
    oset.insert(2);
    oset.insert(3);
    std::println("{}",oset);
    std::cout<<*oset.find(3)<<'\n';   
};

void stack(std::stack<int>& stacks){
    std::cout<<stacks.size()<<'\n';
    std::cout<<stacks.empty()<<'\n';
    stacks.push(10);
    stacks.push(20);
    stacks.push(30);
    stacks.push(40);
    std::cout<<stacks.top()<<'\n';
    stacks.pop();
    std::cout<<stacks.top()<<'\n';

};

void queue(std::queue<int>& queues){
    std::cout<<queues.size()<<'\n';
    std::cout<<queues.empty()<<'\n';
    queues.push(10);
    queues.push(20);
    queues.push(30);
    queues.push(40);
    std::cout<<queues.front()<<'\n';
    queues.pop();
    std::cout<<queues.front()<<'\n';
    std::cout<<queues.back()<<'\n';
};

void priority_queue(std::priority_queue<int>& pqueues){
    std::cout<<pqueues.size()<<'\n';
    std::cout<<pqueues.empty()<<'\n';
    pqueues.push(10);
    pqueues.push(20);
    std::cout<<pqueues.top()<<'\n';
    pqueues.push(30);
    pqueues.push(40);
    std::cout<<pqueues.top()<<'\n';
};


int main(){
    std::cout<<"main function"<<'\n';

    std::array<int,5> arr ={1,2,3};
    std::cout<<arr[0]<<'\n'<<arr[4]<<'\n';
    arrays(arr);

    std::vector<int> vec ={1,2,3};
    std::cout<<vec[0]<<'\n'<<vec[4]<<'\n';
    vector(vec);

    std::unordered_map<int,int> map={{0,0}};
    unordered_map(map);
    
    std::map<int,int> map2={{0,0}};
    omap(map2);
    
    std::unordered_set<int> set={0};
    unordered_set(set);

    std::set<int> oset2={0};
    oset(oset2);
    
    std::stack<int> stacks;
    stack(stacks);
    
    std::queue<int> queues;
    queue(queues);

    std::priority_queue<int> pqueue;
    priority_queue(pqueue);


};