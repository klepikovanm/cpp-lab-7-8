#include <iostream>
#include <fstream>
using namespace std;

#ifndef CPP_LAB_7_8_VEHICLE
#define CPP_LAB_7_8_VEHICLE

class Vehicle {
private: 
    char* brand = nullptr;
    int year;
    int mileage;
    char* status = nullptr;//зарегистрировано или нет
public:
    Vehicle();
    Vehicle(const char* v_brand, int v_year, int v_mileage, const char* v_status);
    Vehicle(Vehicle const & copy);
    ~Vehicle();

    void getBrand()const;
    void getVehicleYear()const;
    void getMileage()const;
    void getStatus()const;
    void getAll()const;
    void setBrand(const char* v_brand);
    void setVechicleYear(int v_year);
    void setMileage(int v_mileage);
    void setStatus(const char* v_status);
    void setAll(const char* v_brand, int v_year, int v_mileage, const char* v_status);
    //метод для того, чтобы сверять данные посимвольно, а не по адресам
    static bool equals(const char* first, const char* second);
protected://помещаю эти функции в protected, так как доступ необхoдим только наследникам, через которые функциями можно будет пользоваться снаружи
//стоимость регистрации
    virtual void RegistrationPrice(const char* c_status);
//запись регистрации в отчет
    virtual void RegistrationPriceFile(const char* c_status);
//стоимости аренды
    virtual void RentPrice(int v_time, const char* c_status);
//запись аренды в отчет
    virtual void RentPriceFile(int v_time, const char* c_status);
//запись в отчет информации о техническом средстве
    void getAllFile()const;
};

class Passenger_car : public Vehicle {
public:
    void getAllFileCar();
    void RegistrationPrice();
    void RegistrationPriceFile();
    void RentPrice(int v_time, const char* c_status);
    void RentPriceFile(int v_time, const char* c_status);
};
class Truck : public Vehicle {
public:
    void getAllFileTruck();
    void RegistrationPrice();
    void RegistrationPriceFile();
    void RentPrice(int v_time, const char* c_status);
    void RentPriceFile(int v_time, const char* c_status);
};
class Motorcycle : public Vehicle {
public:
    void getAllFileMotorcycle();
    void RegistrationPrice();
    void RegistrationPriceFile();
    void RentPrice(int v_time, const char* c_status);
    void RentPriceFile(int v_time, const char* c_status);
};

#endif