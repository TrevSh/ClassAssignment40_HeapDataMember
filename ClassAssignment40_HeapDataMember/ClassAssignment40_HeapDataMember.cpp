//See Page 300 of Beginning C++ Through Game Programming for more info. This had me stumped for a minute.

#include <iostream>
#include <string>

class Critter {
public:
    Critter(const std::string& name = " ", int age = 0);
    ~Critter();                     //destructor prototype. Signified by the tilde (~).
    Critter(const Critter& c);      //copy constructor prototype
    Critter& operator=(const Critter& c);
    void Greet() const;
private:
    std::string* m_pName;           //Declaring data member that points to value on heap
    int m_Age;
};

Critter::Critter(const std::string& name, int age) {
    m_pName = new std::string(name);//Allocating memory on heap for name in constructor which is pointed to by m_pName.
    m_Age = age;                    //Age will remain on the stack memory
    std::cout << "Constructor called\n";
}

Critter::~Critter() {               //This will be called when an object is destroyed. All classes that allocate memory must have a destructor that frees that memory lest you'll end up with a leak.
    std::cout << "Destructor called\n";
    delete m_pName;                 //Destroying the pointer to prevent memory leaks. Age is not destroyed since its on stack memory and is automatically cleared.
}

Critter::Critter(const Critter& c) {                     //Copies any data members from the original object.
    std::cout << "Copy Constructor called\n";
    m_pName = new std::string(*(c.m_pName));             //This copy constructor creates a new pointer for the new object but keeps same name. This way you dont have two copies pointing to the same address.
    m_Age = c.m_Age;                                     //Copies age from the original object.
}

Critter& Critter::operator=(const Critter& c) {         //To prevent shallow-copies(objects pointing to the same address) we write out own assignment operator.
    std::cout << "Overloaded Assignment Operator called\n";
    if (this != &c) {
        delete m_pName;                                 //Clears the original name...
        m_pName = new std::string(*(c.m_pName));        //...and takes the name of the assignee
        m_Age = c.m_Age;
    }
    return *this;
}

void Critter::Greet() const {
    std::cout << "I'm " << *m_pName << " and I'm " << m_Age << " year old. \n";
    std::cout << "&m_pName: " << &m_pName;
    std::cout << "m_pName" << m_pName << "\n";
}

void testDestructor();
void testCopyConstructor(Critter aCopy);
void testAssignmentOp();

int main()
{
    testDestructor();
    std::cout << "\n";

    Critter crit("Tom", 7);
    crit.Greet();
    testCopyConstructor(crit);
    crit.Greet();
    std::cout << "\n";

    testAssignmentOp();

    system("pause");
    return 0;
}

void testDestructor() {         //Since there is no return, this Critter is destroyed which invokes the destructor.
    Critter toDestroy("Koby", 3);
    toDestroy.Greet();
}

void testCopyConstructor(Critter aCopy) {
    aCopy.Greet();
}

void testAssignmentOp() {
    Critter crit1("crit1", 7);
    Critter crit2("crit2", 9);
    crit1 = crit2;          //Using our own assignment operator

    crit1.Greet();
    crit2.Greet();
    std::cout<<"\n";

    Critter crit3("crit3", 11);
    crit3 = crit3;
    crit3.Greet();
}