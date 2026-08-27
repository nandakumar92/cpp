#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <format>
#include <functional>

class Account{
    private:
        int balance;
        std::mutex mtx;

    public: 
       void deposit(int& amt){
         std::lock_guard<std::mutex> lock(mtx);
         balance+=amt;
         std::cout<<std::format("Deposited amount {}, now balance is {}", amt, balance);
       };

       int getBalance(){
        std::lock_guard<std::mutex> lock(mtx);
        return balance;
       };

       int calculatebonus(){
        return 500;
       }

}
;


int main(){

    Account acct;
    int amt=50;
    std::jthread t1(&Account::deposit, &acct,std::ref(amt));
    std::jthread t2(&Account::deposit, &acct,std::ref(amt));
    std::cout<<acct.getBalance();

}