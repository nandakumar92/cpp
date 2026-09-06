#include <iostream>
#include <vector>
#include <span>
#include <string_view>
using namespace std;

// function pointers allows us to create pointers to functio with same signatures and pass them to another function. 
// Ths way we use function and pass multiple differnet fucntions to process.

// function pointer for any func that accpes dobule and returns book.
using PriceRule = bool(*)(double);
// any function that accepts index, double and returns nothing.
using AlertHandler = void(*)(size_t,double);

bool isExpensive(double price){
    return price>100;
}

bool isCheap(double price){
    return price<50;
}

void printAlert(size_t position, double price){
cout << "Alert at index "
         << position
         << ": price = "
         << price
         << '\n';
}

void scanPrices(
    span<const double> prices,
    PriceRule rule,
    AlertHandler handler){

        for (size_t i{0}; i<prices.size();++i){
         if (rule(prices[i])){
            handler(i,prices[i]);
         }
        }
}

int main(){

    vector<double> prices={
       42.5,
        101.0,
        88.0,
        125.5,
        35.0
    };

    cout << "Expensive prices:\n";

    scanPrices(
        prices,
        isExpensive,
        printAlert
    );

    cout << "\nCheap prices:\n";

    scanPrices(
        prices,
        isCheap,
        printAlert
    );

}