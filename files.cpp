#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>


struct Employee{
    std::string name;
    int age;
    double salary;
};


// create file 
void CreateEmployeeFile(){
    std::ofstream file("employees.txt",std::ios::trunc);
    if (!file.is_open()){
        std::cerr<<"file could not be opended";
    }
    file << "Alice 30 95000\n";
    file << "Bob 35 110000\n";
    file << "Charlie 28 85000\n";
    
     // No close() required.
    // file is automatically closed when this function ends and file goes out of scope.

};


// append record
void AppendRecord(const Employee& employee){
   std::ofstream file("employees.txt", std::ios::app);
   if (!file.is_open()){
        std::cerr<<"file could not be opended";
    }

    file << employee.name << ' '
         << employee.age << ' '
         << employee.salary << '\n';
};

// read file 
void Read(){
    std::fstream file("employees.txt");
    if (!file.is_open()){
        std::cerr<<"file could not be opended";
    }

    std::string line;
    double totalsal;
    int empcount;
    Employee employee;
    while(std::getline(file,line)){
        std::stringstream ss(line);
        if(ss>>employee.name>>employee.age>>employee.salary){
            std::cout
                << "Employee: " << employee.name
                << " | Age: " << employee.age
                << " | Salary: $" << employee.salary
                << '\n';
            totalsal += employee.salary;
            empcount++;

        }
        else{
            std::cerr<<"could not parse the line";
        }
        
        std::cout<<'\n'<<totalsal<<'\n'<<empcount<<'\n';

    }
}

int main(){
CreateEmployeeFile();

AppendRecord({
        "David",
        42,
        125000
    });

Read();

}