#include <iostream>
#include <utility>

class Laptop{
    private:
      int m_id;
    public:
      Laptop(int id)
      : m_id(id){ 
        std::cout << "Laptop " << m_id << " CREATED\n";
      };

      ~Laptop(){
        //destrucotr
        std::cout << "Laptop " << m_id << " DESTROYED\n";
      }

      void use(){
        std::cout << "Using Laptop\n";
      }

};

// simple smart pointer
template <typename T>
class SmartPtr{
    private:
        T* m_ptr;

    public:
       SmartPtr(T* ptr= nullptr)
       : m_ptr(ptr)
      {
        std::cout << "SmartPtr now OWNS the resource\n";
      };

    // Desturctor deletes poitners evne if exception is thrown. This prevents dangling pointers and memory leaks.
      ~SmartPtr()
     {
        std::cout << "SmartPtr destroyed -> deleting resource\n";

        delete m_ptr;
     }


     //copy constructor allows dangling pointers when ojbect is create with other object
    //  SmartPtr(const SmartPtr& other)
    // : m_ptr(other.m_ptr)
    // {
    //   };

    // to prevent stop copy construcotors
     SmartPtr(const SmartPtr&) = delete;

    //move semantics , add move constructor to transfer ownsership insteaf of copying.
    SmartPtr(SmartPtr&& other)
      : m_ptr(other.m_ptr)
    {
       other.m_ptr=nullptr;
       std::cout << "SmartPtr MOVE constructor -> ownership transferred\n";
    };



     T* operator->(){
      return m_ptr;
     };

   


};


int main(){
 std::cout << "\n--- STEP 1: CREATE RESOURCE ---\n";
 SmartPtr<Laptop> laptop1(new Laptop(101));
 laptop1->use();

 std::cout << "\n--- STEP 2: MOVE OWNERSHIP ---\n";
 SmartPtr<Laptop> laptop2(std::move(laptop1));
 laptop2->use();
}