#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class BaseClass
{
public:
    BaseClass()
    {
        m_x = 7;
        m_name = "Preposterous and pompous";
    }

    virtual ~BaseClass()
    {
        cout << "BaseClass destructor was invoked!" << endl;
    }

    BaseClass& operator=(BaseClass& rhs)
    {
        m_x = rhs.m_x * 2;
        return *this;
    }

    int getX()
    {
        return m_x;
    }
    
    string getName()
    {
        return m_name;
    }
    
    string& getNameByRef()
    {
        return m_name;
    }
    
    void printNameAddress()
    {
        cout << "Name address: " << hex << showbase << (size_t)&m_name << endl;
    }    

    static void printAddress(void* address)
    {
        cout << "address: " << hex << showbase << (size_t)address << endl;
    }    

protected:
    int m_x;
    string m_name;
};

class DerivedClass : public BaseClass
{
public:
    DerivedClass() = default;
    DerivedClass& operator=(DerivedClass& rhs) = default;

    virtual ~DerivedClass()
    {
        cout << "DerivedClass destructor was invoked" << endl;
    }

    int getY()
    {
        return m_y;
    }

protected:
    int m_y{0};
};

void TestSizeof()
{
  int* pi1;
  int* pi2;
  int* pi3;
  int rg1[20];

  pi1 = new int();
  pi2 = new int[10];
  pi3 = rg1;

  cout << "sizeof(pi1) = " << sizeof(pi1) << endl;
  cout << "sizeof(*pi1) = " << sizeof(*pi1) << endl;
  cout << "sizeof(pi2) = " << sizeof(pi2) << endl;
  cout << "sizeof(*pi2) = " << sizeof(*pi2) << endl;
  cout << "sizeof(pi3) = " << sizeof(pi3) << endl;
  cout << "sizeof(*pi3) = " << sizeof(*pi3) << endl;
  cout << "sizeof(rg1) = " << sizeof(rg1) << endl;
  cout << "sizeof(*rg1) = " << sizeof(*rg1) << endl;
}

void TestConstructorInheritance()
{
    DerivedClass dc1;

    cout << "dc1.x = " << dc1.getX() << "; dc1.y = " << dc1.getY() << endl;

    DerivedClass dc2;

    dc2 = dc1;

    cout << "dc2.x = " << dc2.getX() << "; dc2.y = " << dc2.getY() << endl;
}

void TestSharedPtr()
{
    shared_ptr<uint8_t[]> ptr;

    if (ptr)
    {
        cout << "ptr is initialized!" << endl;
    }
    else
    {
        cout << "ptr is uninitialized!" << endl;
    }

    ptr = make_shared<uint8_t[]>(sizeof(uint64_t));

    if (ptr)
    {
        cout << "ptr is initialized!" << endl;
    }
    else
    {
        cout << "ptr is uninitialized!" << endl;
    }

    uint64_t& value = *reinterpret_cast<uint64_t*>(&ptr[0]);
    value = -1;

    cout << "ptr[0] address: " << hex << showbase << (size_t)&ptr[0] << endl;
    cout << "ptr value: ";
    for (size_t i = 0; i < sizeof(uint64_t); ++i)
    {
        cout << hex << showbase << (int)ptr[i] << " ";
    }
    cout << endl;

    shared_ptr<uint8_t[]> ptr2 = ptr;

    cout << "ptr2[0] address: " << hex << showbase << (size_t)&ptr2[0] << endl;
    cout << "ptr2 value: ";
    for (size_t i = 0; i < sizeof(uint64_t); ++i)
    {
        cout << hex << showbase << (int)ptr2[i] << " ";
    }
    cout << endl;

    value = *reinterpret_cast<uint64_t*>(&ptr2[0]);
    value = 0;

    cout << "ptr2[0] address: " << hex << showbase << (size_t)&ptr2[0] << endl;
    cout << "ptr2 value: ";
    for (size_t i = 0; i < sizeof(uint64_t); ++i)
    {
        cout << hex << showbase << (int)ptr2[i] << " ";
    }
    cout << endl;

    cout << "ptr[0] address: " << hex << showbase << (size_t)&ptr[0] << endl;
    cout << "ptr value: ";
    for (size_t i = 0; i < sizeof(uint64_t); ++i)
    {
        cout << hex << showbase << (int)ptr[i] << " ";
    }
    cout << endl;


    shared_ptr<uint8_t[]> ptr3 = ptr;
    value = *reinterpret_cast<uint64_t*>(&ptr3[0]);
    value = 0x1122334455667788;

    cout << "ptr3[0] address: " << hex << showbase << (size_t)&ptr3[0] << endl;
    cout << "ptr3 value: ";
    for (size_t i = 0; i < sizeof(uint64_t); ++i)
    {
        cout << hex << showbase << (int)ptr3[i] << " ";
    }
    cout << endl;

    cout << "ptr[0] address: " << hex << showbase << (size_t)&ptr[0] << endl;
    cout << "ptr value: ";
    for (size_t i = 0; i < sizeof(uint64_t); ++i)
    {
        cout << hex << showbase << (int)ptr[i] << " ";
    }
    cout << endl;

}

void TestVirtualDestructor()
{
    cout << "Step 1" << endl;
    BaseClass* pbc = new BaseClass();
    delete pbc;

    cout << "\nStep 2" << endl;
    pbc = new DerivedClass();
    delete pbc;

    cout << "\nStep 3" << endl;
    shared_ptr<BaseClass> shpbc;
    shpbc.reset(new BaseClass());

    cout << "\nStep 4" << endl;
    shpbc.reset(new DerivedClass());

    cout << "\nStep 5" << endl;
    shpbc.reset();
}


class IntegerWrapper
{
public:
    IntegerWrapper(uint16_t value)
    {
        cout << "IntegerWrapper(uint16_t) got called!" << endl;
        m_value = value;
    }

    void print()
    {
        cout << "Value = " << m_value << endl;
    }

private:
    uint16_t m_value;
};

void TestDirectInitialization()
{
    uint64_t large_value = -1;

    IntegerWrapper wrap1(7);
    wrap1.print();

    IntegerWrapper wrap2{7};
    wrap2.print();

    IntegerWrapper wrap3 = IntegerWrapper(7);
    wrap3.print();

    IntegerWrapper wrap4 = IntegerWrapper{7};
    wrap4.print();

    IntegerWrapper wrap5(large_value);
    wrap5.print();

    IntegerWrapper wrap6{(uint16_t)large_value};
    wrap6.print();

    IntegerWrapper wrap7 = IntegerWrapper(large_value);
    wrap7.print();

    IntegerWrapper wrap8 = IntegerWrapper{(uint16_t)large_value};
    wrap8.print();
}

void TestVector()
{
    vector<int> int_list;
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);

    cout << "Vector size = " << int_list.size() << endl;

    cout << "First scan:" << endl;
    for (int i : int_list)
    {
        cout << "\tElement = " << i << endl;
    }

    cout << "Second scan:" << endl;
    for (int i = 0; i < int_list.size(); ++i)
    {
        cout << "\tElement = " << int_list[i] << endl;
    }
}

void TestReferenceAccess()
{
    BaseClass instance;
    instance.printNameAddress();
    string& nameRef = instance.getNameByRef();
    BaseClass::printAddress(&nameRef);
    cout << instance.getName() << endl;
    cout << nameRef << endl;
}

void TestVectorResizing()
{
    vector<string> vector;
    vector.push_back("First String");
    vector.push_back("Second String");
    vector.push_back("Third String");
    vector.resize(5);

    size_t counter = 0;    
    while (!vector.empty())
    {
        cout << ++counter << ": " << vector.back() << endl;
        vector.pop_back();
    }
    
    vector.resize(2);
    counter = 0;
    while (!vector.empty())
    {
        cout << ++counter << ": " << vector.back() << endl;
        vector.pop_back();
    }
   
}

void TestIntSize()
{
    cout << "Size of unsigned long = " << sizeof(unsigned long) << endl;
    cout << "Size of unsigned long long = " << sizeof(unsigned long long) << endl;
    cout << "Size of size_t = " << sizeof(size_t) << endl;
    cout << "Size of uint64_t = " << sizeof(uint64_t) << endl;
    cout << "Size of int64_t = " << sizeof(int64_t) << endl;
}

int main(void)
{
    // TestSizeof();
    // TestConstructorInheritance();
    // TestSharedPtr();
    // TestVirtualDestructor();
    // TestDirectInitialization();
    // TestVector();
    // TestReferenceAccess();
    // TestVectorResizing();
    TestIntSize();
}
