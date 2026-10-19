#include <iostream>


class Database{
    protected:
        int pool;
        std::string hostname;
        bool connected;

    public:
        //default constructor
        Database()
            :hostname(std::string("temp")),
            pool(0),
            connected(false){};
        
        Database(int pool, const std::string& hostname)
         : 
         pool(pool),
         hostname(hostname){};

        void connect(){
            connected=true;
            std::cout << "connected";
            std::cout<<'\n';
         };

         virtual std::string gethost(){
            std::cout<<"main gethost function"<<'\n';
            return hostname;
         }

         virtual ~Database(){
            //destructor not used most cases. Used to free up pointer memorires created with new ..etc.
         }

};


class Mysqldb:public Database{
private:
   int version;

public:
    Mysqldb(int pool, const std::string& hostname, int version)
    : Database(pool,hostname), // constructor with base class initilization
      version(version){};

    int getmysqlvesion(){
        return version;
    }

    //polymorphism - runtime same method signature. Use virtual in base class to override at run time.
    std::string gethost() override {
        std::cout<<"mysql gethost function"<<'\n';
        return hostname;
    }

};

void process(Database& db){
  db.connect();
  db.gethost();
  std::cout<<db.gethost()<<'\n';
}

int main(){
   
    // general c++ pass and mutation types
    // Database db;
    // void process(std::string hostname) = creates separate copy of variable. Changes to hostname inside wont affect original variable.
    // pass by non-const ref -  void process(std::string& hostname) - cretes ref. Changes to hostname inside function affects original vairiable *mutable ref in rust.
    // pass by const ref - void process(const std::string& hostname) - created ref , hostname cannot be changed. *immutable ref in rust.
    // pass by non-const point - void process(std::string* hostname)  - Created duplicate pointer. Changes to hostname inside function affects original vairiable.
    // psss by const point - void process(const std::string* hostname) - create duplicate constant pointer. hostname cannot be changed.
    
    // virtual keyword usage //
    // If a base class has few child class and we create object direct on child class like Mysqldb mysql1(0,std::string("mysqlhost2"),20)
    // then when the object goes out of scope both child class destructor and base class destructor automatically called.
    //  But if we create base class pointer reference to child class object like - Database* db = new Mysqldb(); then delete db; then we need 
    // virtual destructor in base class virtual ~Database(), otherwise delete db might not correct call child class destructors. 
    // virtual functions - these enabled run time polymorphism 
    // When a base class has gethost function and mysql child class has same function. WHen we create mysql class object and directly call
    // gethost it will work and correctyl call mysql class function. Mysql mysql; mysql.gethost(). But when use a base class reference to child class object
    // such as Database& db = Mysql mysql, then if we call db.gethost(), program wont correctly run child class funciton. 
    // To enable this rum time plymorphism we use virtual keywork on base class function and override keywork on the child class function. Then refernece and functions will work.


    std::cout<< "main";
    std::cout<<'\n';
    std::string temp="host1";
    Database db1;
    Database db2(0,temp);
    std::cout<< db1.gethost()<<'\n';
    std::cout<<db2.gethost()<<'\n';

    Mysqldb mysql1(0,std::string("mysqlhost2"),20); // std::string(str) creates a temp object. std::string& cannot bind to this , so use const std::string& in class to bind to temp objects.
    std::cout<<mysql1.gethost()<<'\n'<< mysql1.getmysqlvesion()<<'\n'; // base class function
    // virtual keyword is useful when we want same function signature in mutliple seprate implementation in child classes. Then we can create reference to base class and call seprate functions which should be marked virtual in base.
    process(mysql1);


}