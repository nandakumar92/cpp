#include <iostream>
#include <iterator>
#include <vector>

int temp(int& x, int& y){
    return x+y;
}

int temp2(int* x, int* y){
    return *x + *y;
}

int main(){

    int distance=463;
    double price_per_litre=1.12;
    const double consumption=0.08;
    float total=distance*price_per_litre*consumption;
    std::cout << total;
   
    int x=100;
    std::cout<<'\n';
    switch(x){
        case 1:{
             std::cout<<1; 
        } 

        case 2:{
             std::cout<<2; 
        } 
    }

    int& y=x;
   

    while(y>90){
    std::cout<<y;
    y-=1;
    }
    std::cout<<'\n';
    std::cout<<x;
    std::cout<<'\n';

    for(int& i{x};i>=60;i--){
        if (x==65){
            break;
        }
    std::cout<<i;
    std::cout<<'\n';
    }
    std::cout<<'\n';
    std::cout<<x;
    std::cout<<'\n';
    
    std::cout<< temp(x,y);

    int* xptr=&x;
    std::cout<<'\n';
    std::cout<<xptr;
    std::cout<<'\n';
    std::cout<<(*xptr);
    std::cout<<'\n';
    
    std::cout<< temp2(&x,&y);

    //arrays - fixed size
    int a[5]={};
    std::cout<<'\n';
    std::cout<<a;
    std::cout<<'\n';
    int a2[5]={1,2,3};
    std::cout<<'\n';
    std::cout<<a2[0];
    std::cout<<'\n';
    std::cout<<std::size(a2);
    
    // vectors - dynamic arrays

    std::vector<int> vec;
    std::cout<<'\n';
    std::cout<<vec.size() << vec.capacity();
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    std::print("{}\n", vec); 
    std::print("{}\n", *vec.begin()); 
    vec.erase(vec.begin()+2);
    std::print("{}\n", vec); 
    vec.insert(vec.begin()+2,4);
    std::print("{}\n", vec); 

}
