#include <iostream>


// simpe function template
template <typename T>
T getMax(T a, T b){
    if (a>=b){
        return a;
    }
    else{
        return b;
    };

};

int getMax2(int a, int b){
    if (a>=b){
        return a;
    }
    else{
        return b;
    };
};

// simple class template
template <typename T>
class Box{
    private:
        T value;
    
    public:
        Box(T val)
        : value(val){ };
    
    T getValue(){
        return value;
    }
};


// template function overloading dpeending on type.
template <typename T>
bool arequal(T a, T b){
    if (a==b){
        return true;
    }
    else{
        return false;
    }
};

// call this when double is used
template <>
bool arequal<double>(double a, double b){
    return std::abs(a - b) < 1e-9;
};

int main(){
    std::cout<<getMax(5,5)<<'\n';
    std::cout<<getMax(5.5,5.4)<<'\n';
    std::cout<<getMax(std::string("a"),std::string("b"))<<'\n';

    std::cout<<getMax2(5.2,5.5)<<'\n'; //does implicit conversion instead of passing float.

    Box<int> box(20);
    std::cout<<box.getValue()<<'\n';
    Box<std::string> box2("hello");
    std::cout<<box2.getValue()<<'\n';

    std::cout<<arequal(5, 5)<<'\n';
    std::cout<<arequal(1.000005, 1.000006)<<'\n';
    

}