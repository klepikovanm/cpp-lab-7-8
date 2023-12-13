#include <iostream>
#include <fstream>
using namespace std;

#ifndef CPP_LAB_7_8_CUSTOMER
#define CPP_LAB_7_8_CUSTOMER

class Customer {
private:
	char* name = nullptr;
    char* mail = nullptr;
	int age;
	char* status = nullptr;
public:
	Customer();
	Customer(const char* c_name, const char* c_mail, int c_age, const char* c_status);
	Customer(Customer const & copy);
	~Customer();

    void getName()const;
    void getMail()const;
    void getAge()const;
    void getStatus()const;
    void getAll()const;
    void getAllFile(int number)const;
    void setName(const char* c_name);
    void setMail(const char* c_mail);
    void setAge(int c_age);
    void setStatus(const char* c_status);
    void setAll(const char* c_name, const char* c_mail, int c_age, const char* c_status);
    const char* backStatus()const;
};

#endif