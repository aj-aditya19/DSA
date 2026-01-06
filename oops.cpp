// 06-01-2025 - 11:40
#include <iostream>
#include <string>

using namespace std;

class Teacher
{

private:
    float salary;

public:
    // Teacher()
    // {
    //     cout << "Teacher permeterized constructor is called" << endl;
    // }
    Teacher(string name, string dept, float salary, float cgpa) // -> Constructor
    {
        cout << "Teacher function is called" << endl;
        this->role = "Teacher";
        this->name = name;
        this->dept = dept;
        this->salary = salary;
        cgpaPtr = new double;
        *cgpaPtr = cgpa;
    }

    Teacher(Teacher &obj)
    {
        this->name = obj.name;
        this->salary = obj.salary;
        this->dept = obj.dept;
        this->role = obj.role;
        cgpaPtr = new double;
        *cgpaPtr = *obj.cgpaPtr;
    }

    ~Teacher() // Destructor
    {
        cout << "Distructor is called" << endl;
        delete cgpaPtr;
    }
    string name;
    string dept;
    string role;
    double *cgpaPtr;

    void changeDept(string newDept)
    {
        dept = newDept;
    }

    void setSalary(float s)
    {
        salary = s;
    }
    float getSalary()
    {
        return salary;
    }
    void getInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Role: " << role << endl;
        cout << "Salary: " << salary << endl;
        cout << "Dept: " << dept << endl;
        cout << "CGPA: " << *cgpaPtr << endl;
        cout << "----------------------------" << endl;
    }
};

class Person
{
public:
    string name;
    int age;
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }
};
class Student : public Person
{
public:
    int roll;
    Student(string name, int age, int roll) : Person(name, age)
    {
        this->roll = roll;
    }
    void getInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Roll-no.: " << roll << endl;
    }
};
int main()
{
    cout << "OOPs Started" << endl;
    Teacher t1("Araydha", "CS", 4500.323, 9.7);
    t1.getInfo();
    Teacher t2(t1);
    t2.getInfo();
    t2.name = "Kritkia";
    *(t2.cgpaPtr) = 9.5;
    t2.getInfo();
    Student s1("Aditya", 17, 34);
    // s1.name = "Aditya ";
    // s1.age = 17;
    s1.roll = 1;
    s1.getInfo();
}