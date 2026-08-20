#include <iostream>


int getsum(int x,int y); // forward declarartion

int main(){
    std::cout << "helo world" <<std::endl ;
    std::cout << "new line"<<std::endl;
    std::cout<<"new line better\n";
    std::cout<<"hello\n";

    [[maybe_unused]] double pi { 3.14159 };
    [[maybe_unused]] double gravity { 9.8 };
    [[maybe_unused]] double phi { 1.61803 };
    

    int x1=5;
    int y1=6;
    int z=getsum(x1,y1);
    std::cout<<z<<'\n';

    double temp{3.14};
    int temp2=temp;
    std::cout<<temp2;
    int cost{19.099};
}

int getsum(int x,int y){
    return x+y;
}

