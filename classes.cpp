// classes.cpp — Chapter 5 study version, based on the original Database/Mysqldb example.
// Topics: concrete vs abstract classes, virtual functions, inheritance, dynamic_cast,
// virtual destructors, RAII/unique_ptr, and selected class-design guidelines.
// The original Database, Mysqldb, and process() ideas are preserved and expanded.
// The method getmysqlvesion() is corrected to getMysqlVersion().

#include <cstddef>          // std::size_t
#include <initializer_list> // std::initializer_list
#include <iostream>
#include <memory>           // std::unique_ptr, std::make_unique
#include <stdexcept>        // std::invalid_argument
#include <string>
#include <typeinfo>         // std::bad_cast
#include <vector>

// ============================================================================
// 1. ABSTRACT CLASS / INTERFACE  (book 5.3; advice 14, 16, 18)
// ============================================================================
// Unlike the original concrete Database, IDatabase cannot be instantiated:
//   IDatabase x;  // ERROR: pure virtual functions are not implemented.
//
// Pure virtual (= 0) means a concrete derived class must implement the method.
// An abstract class MAY have fields, implemented methods, and constructors;
// this one is intentionally a minimal interface.
class IDatabase {
public:
    virtual void connect() = 0;
    virtual std::string gethost() const = 0;

    // Crucial if objects may be destroyed through IDatabase* or
    // std::unique_ptr<IDatabase>. The actual derived destructor runs first.
    virtual ~IDatabase() = default;
};

// ============================================================================
// 2. CONCRETE BASE CLASS  (original Database; advice 3, 5, 9, 20)
// ============================================================================
// Database IS concrete: it implements every pure virtual IDatabase function.
// It also provides reusable state and implementation for child classes.
// This is implementation inheritance in addition to interface inheritance.
class Database : public IDatabase {
protected:
    int pool_;                  // Available to derived classes.
    std::string hostname_;     // Owns its own copy of the host string.
    bool connected_;           // Must initialize! Original code missed this
                               // in the two-argument constructor.

public:
    // Delegating constructor: reuse the fully initialized main constructor.
    Database() : Database(0, "temp") {}

    Database(int pool, const std::string& hostname)
        : pool_{pool}, hostname_{hostname}, connected_{false} {}
    // const std::string& accepts lvalues and temporary strings.
    // hostname_ COPIES the value, so the temporary can safely go away.

    // Override of IDatabase::connect(); changes this object's state.
    void connect() override {
        connected_ = true;
        std::cout << "Connected: " << gethost() << '\n';
        // gethost() is virtual. Even from within Database::connect(), it can
        // call Mysqldb::gethost() if this object's actual type is Mysqldb.
    }

    // 'const' means this method cannot modify the object's ordinary state.
    // It is part of the signature: derived overrides must also use const.
    std::string gethost() const override { return hostname_; }

    bool isConnected() const noexcept { return connected_; }

    // Destructors of derived objects run child -> base, whether local or heap.
    // Virtual is specifically required for safe deletion through a base
    // pointer in the ordinary polymorphic-delete design.
    ~Database() override { std::cout << "~Database()\n"; }
};

// ============================================================================
// 3. DERIVED CLASSES / RUNTIME POLYMORPHISM  (book 5.4, 5.5; advice 17-20)
// ============================================================================
class Mysqldb : public Database {
private:
    int version_;

public:
    Mysqldb(int pool, const std::string& hostname, int version)
        : Database(pool, hostname), version_{version} {}

    int getMysqlVersion() const noexcept { return version_; }

    // With an actual Mysqldb object, a Database& or IDatabase& will still
    // invoke THIS implementation, because gethost() is virtual.
    std::string gethost() const override { return "mysql://" + hostname_; }

    ~Mysqldb() override { std::cout << "~Mysqldb()\n"; }
};

class Postgresdb : public Database {
public:
    Postgresdb(int pool, const std::string& hostname)
        : Database(pool, hostname) {}

    std::string gethost() const override { return "postgres://" + hostname_; }

    ~Postgresdb() override { std::cout << "~Postgresdb()\n"; }
};

// A free (non-member) function is appropriate: no direct private member
// access required. It depends ONLY on the interface, not a specific DB type.
// IDatabase& does not own or copy the object. It refers to the real object.
void process(IDatabase& db) {
    db.connect();
    std::cout << "process() uses: " << db.gethost() << '\n';
}

// ============================================================================
// 4. RUNTIME TYPE CHECKING / DYNAMIC_CAST  (book 5.5.2)
// ============================================================================
// Prefer virtual interface methods when possible. dynamic_cast is useful
// when you REALLY need behavior that exists only on a derived class.
void printMysqlVersion(IDatabase& db) {
    if (auto* mysql = dynamic_cast<Mysqldb*>(&db)) {
        // Pointer cast succeeded: db actually refers to a Mysqldb.
        std::cout << "MySQL version = " << mysql->getMysqlVersion() << '\n';
    } else {
        // A failed pointer dynamic_cast returns nullptr.
        std::cout << "Not a Mysqldb object\n";
    }
}

// ============================================================================
// 5. FACTORY + RAII / OWNERSHIP  (book 5.5.3; advice 10-12)
// ============================================================================
// A factory selects a concrete class and returns ownership via unique_ptr.
// The caller does NOT need 'delete' (even if exceptions are thrown).
enum class Engine { mysql, postgres };

std::unique_ptr<IDatabase> makeDatabase(Engine engine,
                                        const std::string& hostname) {
    switch (engine) {
    case Engine::mysql:
        return std::make_unique<Mysqldb>(0, hostname, 8);
    case Engine::postgres:
        return std::make_unique<Postgresdb>(0, hostname);
    }
    throw std::invalid_argument("Unknown engine");
}

// ============================================================================
// 6. SIMPLE CONCRETE COLLECTION  (book advice 2, 4, 7, 8, 13)
// ============================================================================
// A small concrete class is often better than creating another hierarchy.
// The initializer_list constructor lets us write HostCollection{"a", "b"}.
class HostCollection {
private:
    std::vector<std::string> hosts_;

public:
    HostCollection(std::initializer_list<std::string> hosts) : hosts_{hosts} {}

    // operator[] is appropriate because HostCollection is indexed data.
    // This teaching implementation uses at() internally for bounds checks.
    const std::string& operator[](std::size_t i) const { return hosts_.at(i); }

    std::size_t size() const noexcept { return hosts_.size(); }

    // A symmetric comparison operator is a non-member (friend) function.
    // It can read both collections equally; unlike a member, neither side
    // is treated as the special implicit 'this' object.
    friend bool operator==(const HostCollection& a, const HostCollection& b) {
        return a.hosts_ == b.hosts_;
    }
};

int main() {
    

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



    std::cout << "\n[A] Direct objects\n";
    std::string temp = "host1";
    Database db1;                 // Concrete base object: legal.
    Database db2(0, temp);
    Mysqldb mysql1(0, std::string("mysqlhost2"), 20);
    Postgresdb postgres1(0, "pg-host");

    std::cout << db1.gethost() << '\n';
    std::cout << db2.gethost() << '\n';
    std::cout << mysql1.gethost() << '\n'; // Derived method even WITHOUT virtual
                                             // when called directly on mysql1.
    std::cout << "MySQL version: " << mysql1.getMysqlVersion() << '\n';

    // ========================================================================
    // B. Virtual dispatch through a BASE REFERENCE (book 5.3-5.4).
    // ========================================================================
    std::cout << "\n[B] Virtual dispatch through references\n";
    Database& base_ref = mysql1;
    std::cout << base_ref.gethost() << '\n'; // Mysqldb::gethost()

    // Works for either derived class; process() knows only IDatabase.
    process(mysql1);
    process(postgres1);
    std::cout << std::boolalpha << "mysql connected? "
              << mysql1.isConnected() << '\n';

    // ========================================================================
    // C. dynamic_cast: pointer failure -> nullptr; reference failure -> throw.
    // ========================================================================
    std::cout << "\n[C] dynamic_cast\n";
    printMysqlVersion(mysql1);     // Succeeds.
    printMysqlVersion(postgres1);  // Prints: Not a Mysqldb object.

    try {
        auto& mysql_ref = dynamic_cast<Mysqldb&>(postgres1);
        std::cout << mysql_ref.getMysqlVersion() << '\n';
    } catch (const std::bad_cast&) {
        std::cout << "Reference dynamic_cast failed: std::bad_cast\n";
    }

    // ========================================================================
    // D. Own multiple implementations safely with unique_ptr.
    // ========================================================================
    std::cout << "\n[D] Factory, ownership, RAII\n";
    std::vector<std::unique_ptr<IDatabase>> databases;
    databases.push_back(makeDatabase(Engine::mysql, "mysql-prod"));
    databases.push_back(makeDatabase(Engine::postgres, "postgres-prod"));
    for (const auto& db : databases) {
        process(*db); // *db is an IDatabase&; virtual dispatch picks child.
    }
    // At the end of main(), the vector destroys its unique_ptrs.
    // Each unique_ptr deletes the owned object; IDatabase destructor is virtual.

    // Scoped ownership demonstration: destructor messages appear immediately.
    {
        auto short_lived = std::make_unique<Mysqldb>(0, "temporary", 8);
        std::cout << short_lived->gethost() << '\n';
    } // ~Mysqldb(), then ~Database() (IDatabase also destroyed silently).

    // ========================================================================
    // E. initializer_list and operator[] for an indexed concrete class.
    // ========================================================================
    std::cout << "\n[E] Concrete collection\n";
    HostCollection hosts{"primary", "replica"};
    HostCollection same_hosts{"primary", "replica"};
    std::cout << "First host: " << hosts[0] << '\n';
    std::cout << "Number of hosts: " << hosts.size() << '\n';
    std::cout << "Equal? " << (hosts == same_hosts) << '\n';

    // Key reminders:
    // - Local Mysqldb mysql1: child and base destructors run automatically.
    // - unique_ptr<IDatabase>: child and base destructors also run safely.
    // - Naked owning 'new'/'delete' are avoidable with unique_ptr (RAII).
    // - Vtable/vptr is a common compiler implementation of virtual calls,
    //   NOT a memory layout guaranteed by the C++ language standard.
    // - A pure virtual method (= 0) makes a class abstract; 'override'
    //   asks the compiler to verify that your derived method overrides.
    // - A base pointer/reference may refer to a derived object stored locally;
    //   polymorphism does NOT inherently require heap allocation.

    std::cout << "\n[End] Remaining local objects will be destroyed\n";


    // ========================================================
    // CONST OBJECTS AND CONST MEMBER FUNCTIONS
    // ========================================================

    // 1. Normal object (non-const)
    Database db1(0, "mysqlhost");

    db1.connect();       // OK: non-const member function
    db1.gethost();       // OK: const member function
    db1.isConnected();   // OK: const member function


    // 2. Constant object
    const Database db2(0, "postgreshost");

    std::cout << db2.gethost() << '\n';     // OK
    std::cout << db2.isConnected() << '\n'; // OK

    // db2.connect(); // COMPILATION ERROR!
    // A const object cannot call a non-const member function.


    // 3. Const reference to a normal object
    const Database& db3 = db1;

    std::cout << db3.gethost() << '\n';     // OK
    std::cout << db3.isConnected() << '\n'; // OK

    // db3.connect(); // COMPILATION ERROR!
    // Even though db1 is non-const, db3 is a const reference.


    // 4. Original object can still be modified
    db1.connect(); // OK
}
