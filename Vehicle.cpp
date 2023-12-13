#include "Vehicle.h"
#include <iostream>
#include <fstream>
using namespace std;

Vehicle::Vehicle() {
    setAll("Марка", 0, 0, "Статус регистрации");
}
Vehicle::Vehicle(const char* v_brand, int v_year, int v_mileage, const char* v_status) {
    setAll(v_brand, v_year, v_mileage, v_status);
}
Vehicle::Vehicle(Vehicle const & copy) {
    setAll(copy.brand, copy.year, copy.mileage, copy.status);
}
Vehicle::~Vehicle() {
    delete[] brand;
    delete[] status;
}

void Vehicle::getBrand()const {
    cout << "Марка: " << brand << endl;
}
void Vehicle::getVehicleYear()const {
    cout << "Год выпуска: " << year << endl;
}
void Vehicle::getMileage()const {
    cout << "Пробег: " << mileage << endl;
}
void Vehicle::getStatus()const {
    cout << "Cтатус регистрации: " << status << endl;
}
void Vehicle::getAll()const {
    cout << "Марка автомобиля: " << brand << endl;
    cout << "Год выпуска автомобиля: " << year << endl;
    cout << "Пробег автомобиля: " << mileage << endl;
    cout << "Cтатус регистрации автомобиля: " << status << endl;
}

void Vehicle::setBrand(const char* v_brand) {
    delete[] brand;
    brand = new char[strlen(v_brand) + 1];
    strcpy(brand, v_brand);
}
void Vehicle::setVechicleYear(int v_year) {
    year = v_year;
}
void Vehicle::setMileage(int v_mileage) {
    mileage = v_mileage;
}
void Vehicle::setStatus(const char* v_status) {
    delete[] status;
    status = new char[strlen(v_status) + 1];
    strcpy(status, v_status);
}
void Vehicle::setAll(const char* v_brand, int v_year, int v_mileage, const char* v_status) {
    setBrand(v_brand);
    year = v_year;
    mileage = v_mileage;
    setStatus(v_status);
}
    //метод для того, чтобы сверять данные посимвольно, а не по адресам
bool Vehicle::equals(const char* first, const char* second) {
        int i = 0;
        while (true) {
            if (first[i] != second[i]) {//если хоть одно несовпадение
                return false;
            }
            if (first[i] == '\0' ) {//если все совпало и мы дошли до конца
                return true;
            }
            i++;
        }
    }
void Vehicle::RegistrationPrice(const char* c_status) {//для того, чтобы мы могли переопределить этот метод в классе наследнике/сделать другую реализацию надо сделать его виртуальным       
}
//запись регистрации в отчет
void Vehicle::RegistrationPriceFile(const char* c_status) {//указатель на базовый класс может принимать ссылки на любого своего наследника/если не будет virtual, то функции не будут переобределяться
}
//стоимости аренды
void Vehicle::RentPrice(int v_time, const char* c_status) {//virtual нужен, чтобы мы могли использовать указатель на базовый класс и менять поведение классов наследников
}
//запись аренды в отчет
void Vehicle::RentPriceFile(int v_time, const char* c_status) {
}
//запись в отчет информации о техническом средстве
void Vehicle::getAllFile()const {
    ofstream file;//открываем файл для записи
    file.open("Daily_report.txt", ios_base::app);//параметр app необходим для записи в конец(чтобы предыдущие клиенты не стирались)
    file << "Марка: " << brand << endl;
    file << "Год выпуска: " << year << endl;
    file << "Пробег: " << mileage << endl;
    file << "Статус регистрации: " << status << endl;
    file.close();
}

void Passenger_car::getAllFileCar() {
    ofstream file;//открываем файл для записи
    file.open("Daily_report.txt", ios_base::app);//параметр app необходим для записи в конец(чтобы предыдущие клиенты не стирались)
    file << "Автомобиль" << endl;
    file.close();
    getAllFile();
}
void Passenger_car::RegistrationPrice() {
    cout << "Стоимость регистрации: " << 2000 << endl;
    this->setStatus("Зарегистрировано");//ПРОВЕРИТЬ КАК ТУТ РАБОТАЕТ ААААААА
    cout << "ЗАРЕГИСТРИРОВАНО" << endl;
}
void Passenger_car::RegistrationPriceFile() {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << "Стоимость регистрации: " << 3200 << endl;
    file << "ЗАРЕГИСТРИРОВАНО" << endl;
    file.close();
}
void Passenger_car::RentPrice(int v_time, const char* c_status) {
    char status[] = "Впервые";
    if (equals(c_status, status)) {
        cout << "Стоимость аренды: " << 46990*v_time << endl;
    } else {
        cout << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (46990 - 46990*0.2)*v_time << endl;
    }
    cout << "АРЕНДОВАНО" << endl;
}
void Passenger_car::RentPriceFile(int v_time, const char* c_status) {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    char status[] = "Впервые";
    if (equals(c_status, status)) {
        file << "Стоимость аренды: " << 46990*v_time << endl;//0, так как будет переопределение в классах настелдниках
    } else {
        file << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (46990 - 46990*0.2)*v_time << endl;
    }
    file << "АРЕНДОВАНО" << endl;
    file.close();
}

void Truck::getAllFileTruck() {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << "Грузовик" << endl;
    file.close();
    getAllFile();
}
void Truck::RegistrationPrice() {
    cout << "Стоимость регистрации: " << 3200 << endl;
    this->setStatus("Зарегистрировано");
    cout << "ЗАРЕГИСТРИРОВАНО" << endl;
}
void Truck::RegistrationPriceFile() {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << "Стоимость регистрации: " << 3200 << endl;
    file << "ЗАРЕГИСТРИРОВАНО" << endl;
    file.close();
}
void Truck::RentPrice(int v_time, const char* c_status) {
    char status[] = "Впервые";
    if (equals(c_status, status)) {
        cout << "Стоимость аренды: " << 114000*v_time << endl;
    } else {
        cout << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (114000 - 114000*0.2)*v_time << endl;
    }
    cout << "АРЕНДОВАНО" << endl;
}
void Truck::RentPriceFile(int v_time, const char* c_status) {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    char status[] = "Впервые";
    if (equals(c_status, status)) {
        file << "Стоимость аренды: " << 114000*v_time << endl;//0, так как будет переопределение в классах настелдниках
    } else {
        file << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (114000 - 114000*0.2)*v_time << endl;
    }
    file << "АРЕНДОВАНО" << endl;
    file.close();
}

void Motorcycle::getAllFileMotorcycle() {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << "Мотоцикл" << endl;
    file.close();
    getAllFile();
}
void Motorcycle::RegistrationPrice() {
    cout << "Стоимость регистрации: " << 1500 << endl;
    this->setStatus("Зарегистрировано");
    cout << "ЗАРЕГИСТРИРОВАНО" << endl;
}
void Motorcycle::RegistrationPriceFile() {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << "Стоимость регистрации: " << 3200 << endl;
    file << "ЗАРЕГИСТРИРОВАНО" << endl;
    file.close();
}
void Motorcycle::RentPrice(int v_time, const char* c_status) {
    char status[] = "Впервые";
    if (equals(c_status, status)) {
        cout << "Стоимость аренды: " << 39800*v_time << endl;
    } else {
        cout << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (39800 - 39800*0.2)*v_time << endl;
    }
    cout << "АРЕНДОВАНО" << endl;
}
void Motorcycle::RentPriceFile(int v_time, const char* c_status) {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    char status[] = "Впервые";
    if (equals(c_status, status)) {
        file << "Стоимость аренды: " << 39800*v_time << endl;//0, так как будет переопределение в классах настелдниках
    } else {
        file << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (39800 - 39800*0.2)*v_time << endl;
    }
    file << "АРЕНДОВАНО" << endl;
    file.close();
}
