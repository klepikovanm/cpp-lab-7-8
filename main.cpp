#include <iostream>
#include <fstream>
using namespace std;

class Vehicle {
private: 
    char* brand = nullptr;
    int year;
    int mileage;
    char* status = nullptr;//зарегистрировано или нет
public:
    Vehicle() {
        setAll("Марка", 0, 0, "Статус регистрации");
    }
    Vehicle(const char* v_brand, int v_year, int v_mileage, const char* v_status) {
        setAll(v_brand, v_year, v_mileage, v_status);
    }
    Vehicle(Vehicle const & copy) {
        setAll(copy.brand, copy.year, copy.mileage, copy.status);
    }
    ~Vehicle() {
        delete[] brand;
        delete[] status;
    }

    void getBrand()const {
        cout << "Марка: " << brand << endl;
    }
    void getVehicleYear()const {
        cout << "Год выпуска: " << year << endl;
    }
    void getMileage()const {
        cout << "Пробег: " << mileage << endl;
    }
    void getStatus()const {
        cout << "Cтатус регистрации: " << status << endl;
    }
    void getAll()const {
        cout << "Марка автомобиля: " << brand << endl;
        cout << "Год выпуска автомобиля: " << year << endl;
        cout << "Пробег автомобиля: " << mileage << endl;
        cout << "Cтатус регистрации автомобиля: " << status << endl;
    }

    void setBrand(const char* v_brand) {
        delete[] brand;
        brand = new char[strlen(v_brand) + 1];
        strcpy(brand, v_brand);
    }
    void setVechicleYear(int v_year) {
        year = v_year;
    }
    void setMileage(int v_mileage) {
        mileage = v_mileage;
    }
    void setStatus(const char* v_status) {
        delete[] status;
        status = new char[strlen(v_status) + 1];
        strcpy(status, v_status);
    }
    void setAll(const char* v_brand, int v_year, int v_mileage, const char* v_status) {
        setBrand(v_brand);
        year = v_year;
        mileage = v_mileage;
        setStatus(v_status);
    }
    //метод для того, чтобы сверять данные посимвольно, а не по адресам
    static bool equals(const char* first, const char* second) {
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
protected://помещаю эти функции в protected, так как доступ необхoдим только наследникам, через которые функциями можно будет пользоваться снаружи
//стоимость регистрации
    virtual void RegistrationPrice(const char* c_status) {//для того, чтобы мы могли переопределить этот метод в классе наследнике/сделать другую реализацию надо сделать его виртуальным
        cout << "Стоимость регистрации: " << 0 << endl;//0, так как будет переопределение в классах наследниках
        this->setStatus("Зарегистрировано");
        cout << "Транспортное средство зарегистрировано." << endl;
    }
//запись регистрации в отчет
    virtual void RegistrationPriceFile(const char* c_status) {//указатель на базовый класс может принимать ссылки на любого своего наследника/если не будет virtual, то функции не будут переобределяться
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "Стоимость регистрации: " << 0 << endl;
        file << "ЗАРЕГИСТРИРОВАНО" << endl;
        file.close();
    }
//стоимости аренды
    virtual void RentPrice(int v_time, const char* c_status) {//virtual нужен, чтобы мы могли использовать указатель на базовый класс и менять поведение классов наследников
        char status[] = "Впервые";
        if (equals(c_status, status)) {
            cout << "Стоимость аренды: " << 0*v_time << endl;//0, так как будет переопределение в классах настелдниках
        } else {
            cout << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (0 - 0*0.2)*v_time << endl;
        }
        cout << "Транспортное средство арендовано." << endl;
    }
//запись аренды в отчет
    virtual void RentPriceFile(int v_time, const char* c_status) {
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        char status[] = "Впервые";
        if (equals(c_status, status)) {
            file << "Стоимость аренды: " << 0*v_time << endl;//0, так как будет переопределение в классах настелдниках
        } else {
            file << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (0 - 0*0.2)*v_time << endl;
        }
        file << "Транспортное средство арендовано." << endl;
        file.close();
    }
//запись в отчет информации о техническом средстве
    void getAllFile()const {
        ofstream file;//открываем файл для записи
        file.open("Daily_report.txt", ios_base::app);//параметр app необходим для записи в конец(чтобы предыдущие клиенты не стирались)
        file << "Марка: " << brand << endl;
        file << "Год выпуска: " << year << endl;
        file << "Пробег: " << mileage << endl;
        file << "Статус регистрации: " << status << endl;
        file.close();
    }
};

class Passenger_car : public Vehicle {
public:
    void getAllFileCar() {
        ofstream file;//открываем файл для записи
        file.open("Daily_report.txt", ios_base::app);//параметр app необходим для записи в конец(чтобы предыдущие клиенты не стирались)
        file << "Автомобиль" << endl;
        file.close();
        getAllFile();
    }
    void RegistrationPrice() {
        cout << "Стоимость регистрации: " << 2000 << endl;
        this->setStatus("Зарегистрировано");//ПРОВЕРИТЬ КАК ТУТ РАБОТАЕТ ААААААА
        cout << "ЗАРЕГИСТРИРОВАНО" << endl;
    }
    void RegistrationPriceFile() {
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "Стоимость регистрации: " << 3200 << endl;
        file << "ЗАРЕГИСТРИРОВАНО" << endl;
        file.close();
    }
    void RentPrice(int v_time, const char* c_status) {
        char status[] = "Впервые";
        if (equals(c_status, status)) {
            cout << "Стоимость аренды: " << 46990*v_time << endl;
        } else {
            cout << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (46990 - 46990*0.2)*v_time << endl;
        }
        cout << "АРЕНДОВАНО" << endl;
    }
    void RentPriceFile(int v_time, const char* c_status) {
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
};
class Truck : public Vehicle {
public:
    void getAllFileTruck() {
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "Грузовик" << endl;
        file.close();
        getAllFile();
    }
    void RegistrationPrice() {
        cout << "Стоимость регистрации: " << 3200 << endl;
        this->setStatus("Зарегистрировано");
        cout << "ЗАРЕГИСТРИРОВАНО" << endl;
    }
    void RegistrationPriceFile() {
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "Стоимость регистрации: " << 3200 << endl;
        file << "ЗАРЕГИСТРИРОВАНО" << endl;
        file.close();
    }
    void RentPrice(int v_time, const char* c_status) {
        char status[] = "Впервые";
        if (equals(c_status, status)) {
            cout << "Стоимость аренды: " << 114000*v_time << endl;
        } else {
            cout << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (114000 - 114000*0.2)*v_time << endl;
        }
        cout << "АРЕНДОВАНО" << endl;
    }
    void RentPriceFile(int v_time, const char* c_status) {
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
};
class Motorcycle : public Vehicle {
public:
    void getAllFileMotorcycle() {
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "Мотоцикл" << endl;
        file.close();
        getAllFile();
    }
    void RegistrationPrice() {
        cout << "Стоимость регистрации: " << 1500 << endl;
        this->setStatus("Зарегистрировано");
        cout << "ЗАРЕГИСТРИРОВАНО" << endl;
    }
    void RegistrationPriceFile() {
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "Стоимость регистрации: " << 3200 << endl;
        file << "ЗАРЕГИСТРИРОВАНО" << endl;
        file.close();
    }
    void RentPrice(int v_time, const char* c_status) {
        char status[] = "Впервые";
        if (equals(c_status, status)) {
            cout << "Стоимость аренды: " << 39800*v_time << endl;
        } else {
            cout << "Стоимость аренды со скидкой 20%: " << setprecision(10) << (39800 - 39800*0.2)*v_time << endl;
        }
        cout << "АРЕНДОВАНО" << endl;
    }
    void RentPriceFile(int v_time, const char* c_status) {
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
};

class Customer {
private:
	char* name = nullptr;
    char* mail = nullptr;
	int age;
	char* status = nullptr;//постоянный клиент или нет
    //сделать фуекцию дающую скидку если клиент постоянный
public:
	//Конструкторы
	Customer() {
        setAll("Имя", "Почта", 0, "Статус");
	}
	Customer(const char* c_name, const char* c_mail, int c_age, const char* c_status) {
        setAll(c_name, c_mail, c_age, c_status);
	}
	Customer(Customer const & copy) {
        setAll(copy.name, copy.mail, copy.age, copy.status);
	}
	//Деструктор
	~Customer() {
		delete[] name;
        delete[] mail;
		delete[] status;
	}
	//Функции для вывода на экран
	//get-функции позволяют посмотреть значения элементов данных
    void getName()const {//пишем в конце const, так как метод не меняет содержимое класса
        cout << "Имя: " << name << endl;
    }
    void getMail()const {
        cout << "Почта: " << mail << endl;
    }
    void getAge()const {
        cout << "Возраст: " << age << endl;
    }
    void getStatus()const {
        cout << "Статус клиента: " << age << endl;
    }
    void getAll()const {
        cout << "Имя: " << name << endl;
        cout << "Почта: " << mail << endl;
        cout << "Возраст: " << age << endl;
        cout << "Статус клиента: " << status << endl;
    }
    void getAllFile(int number)const {
        ofstream file;//открываем файл для записи
        file.open("Daily_report.txt", ios_base::app);//параметр app необходим для записи в конец(чтобы предыдущие клиенты не стирались)
        file << "Клиент №" << number << endl;
        file << "Имя: " << name << endl;
        file << "Почта: " << mail << endl;
        file << "Возраст: " << age << endl;
        file << "Статус клиента: " << status << endl;
        file.close();
    }
    //функции для редактирования каждого поля
    //set-функции инициализируют элементы данных
    void setName(const char* c_name) {//передается строка, из-за чего на нее выделяется память, и деструктор не может удалить строку
        delete[] name;//чистим память, удаляя прошлые данные
        name = new char[strlen(c_name) + 1];//выделяем новую память: длина нового значения + \0
        strcpy(name, c_name);//побайтово копируем новое значение в переменную из char* в char* до \0
    }
    void setMail(const char* c_mail) {
        delete[] mail;
        mail = new char[strlen(c_mail) + 1];
        strcpy(mail, c_mail);
    }
    void setAge(int c_age) {
        age = c_age;
    }
    void setStatus(const char* c_status) {
        delete[] status;
        status = new char[strlen(c_status) + 1];
        strcpy(status, c_status);
    }
    void setAll(const char* c_name, const char* c_mail, int c_age, const char* c_status) {
        setName(c_name);
        setMail(c_mail);
        age = c_age;
        setStatus(c_status);
    }
    const char* backStatus()const {
        return status;
    }
};

class MaintenanceRecord {
private:
    char* deal = nullptr;//какое именно обслуживание и его итог
    int price;
public:
    MaintenanceRecord() {
        setAll("Тип", 0);
    }
    MaintenanceRecord(const char* m_deal, int m_price) {
        setAll(m_deal, m_price);
    }
    MaintenanceRecord(MaintenanceRecord const & copy) {
        setAll(copy.deal, copy.price);
    }
    ~MaintenanceRecord() {
        delete[] deal;
    }

    void getDeal() {
        cout << deal << endl;
    }
    void getPrice() {
        cout << "Стоимость технического обслуживания: " << price << endl;
    }
    void getAll() {
        cout << deal << endl;
        cout << "Стоимость технического обслуживания: " << price << endl;
    }
    void getAllFile() {
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << deal << endl;
        file << "Стоимость технического обслуживания: " << price << endl;
        file.close();
    }

    void setDeal(const char* m_deal) {
        delete[] deal;
        deal = new char[strlen(m_deal) + 1];
        strcpy(deal, m_deal);
    }
    void setPrice(int m_price) {
        price = m_price;
    }
    void setAll(const char* m_deal, int m_price) {
        setDeal(m_deal);
        price = m_price;
    }
    //перегрузка функции с использованием скидки и нет(то есть два параметра и один)/одновременная запись в файл
    void Price(int money) {//суть перегрузки - использование одного имени функции для нескольких функций
        cout << this->deal << " по стоимости: " << money << endl;
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << this->deal << " по стоимости: " << money << endl;
        file.close();
    }
    void Price(int money, double sale) {//внешние функции могут отличаться только типом возвращаемого значения/количеством и типом параметров, а внутренние еще и реализацией
        cout << this->deal << " по стоимости со скидкой 20%: " << money - money*sale << endl;
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << this->deal << " по стоимости со скидкой 20%: " << money - money*sale << endl;
        file.close();
    }
    //перегрузка операторов для Диагностики/Смены масла/ Замены деталей/ Ремонта
    MaintenanceRecord operator +() {
        MaintenanceRecord find(deal, price);
        find.setDeal("Диагностика - ВСЕ ИСПРАВНО");
        return find;
    }
    MaintenanceRecord operator -() {
        MaintenanceRecord oil(deal, price);
        oil.setDeal("Смена масла - ГОТОВО");
        return oil;
    }
    MaintenanceRecord operator *() {
        MaintenanceRecord details(deal, price);
        details.setDeal("Замена деталей - ГОТОВО");
        return details;
    }
    MaintenanceRecord operator !() {
        MaintenanceRecord fix(deal, price);
        fix.setDeal("Ремонт - ВСЕ ИСПРАВНО");
        return fix;
    }
};

int main() {
    cout << "Начало рабочего дня. Прием звонков клиентов." << endl <<'\v';

    int f_1=0;
    int number = 1;
    while (f_1!=1) {
        cout << "Звонок №" << number << endl;
        cout << "Здравствуйте, вы позвонили в компанию 'Hot Wheels'." << endl << "Для дальнейшего взаимодействия нам необходимы ваши персональные данные." << endl;
        
        char* name = new char[64];
        cout << "Ваше имя: ";
        cin >> name;

        char* mail = new char[32];
        cout << "Ваша почта: ";
        cin >> mail;

        int age;
        cout << "Ваш возраст: ";
        cin >> age;

        char* status = new char[16];
        cout << "Вы постоянный клиент или обратились к нам впервые? "; //надо ввести Постоянный/Впервые
        cin >> status;

        Customer human(name, mail, age, status);
        human.getAllFile(number);

        delete[] name;
        delete[] mail;
        delete[] status;

        int f_2=1;
        while (f_2!=0) {
            char* work = new char[32];
            cout << "Что вас интересует? Аренда/Тех.обслуживание/Регистрация: " << endl;
            cin >> work;
            char A[] = "Аренда";
            char R[] = "Регистрация";

            ofstream file;
            file.open("Daily_report.txt", ios_base::app);
            file << work << ": ";
            file.close();

            if (Vehicle::equals(work, A)) {//аренда
                char* vehicle = new char[32];
                cout << "Что вы бы хотели арендовать? Автомобиль/Грузовик/Мотоцикл: ";
                cin >> vehicle;
                char* brand = new char[16];
                cout << "Марка: ";
                cin >> brand;
                int year;
                cout << "Желаемый год выпуска: ";
                cin >> year;
                int mileage;
                cout << "Желаемый пробег: ";
                cin >> mileage;
                int time;
                cout << "На сколько месяцев вы арендуете " << vehicle << "? ";
                cin >> time;

                char car[] = "Автомобиль";
                char bike[] = "Мотоцикл";
                if (Vehicle::equals(vehicle, car)) {//автомобиль
                    Passenger_car car;
                    car.setAll(brand, year, mileage, "Зарегистрировано");
                    car.getAllFileCar();
                    car.RentPrice(time, human.backStatus());
                    car.RentPriceFile(time, human.backStatus());
                } else if (Vehicle::equals(vehicle, bike)) {//мотоцикл
                    Motorcycle motorcycle;
                    motorcycle.setAll(brand, year, mileage, "Зарегистрировано");
                    motorcycle.getAllFileMotorcycle();
                    motorcycle.RentPrice(time, human.backStatus());
                    motorcycle.RentPriceFile(time, human.backStatus());
                } else {//грузовик
                    Truck truck;
                    truck.setAll(brand, year, mileage, "Зарегистрировано");
                    truck.getAllFileTruck();
                    truck.RentPrice(time, human.backStatus());
                    truck.RentPriceFile(time, human.backStatus());
                }
                delete[] vehicle;
                delete[] brand;

            } else if (Vehicle::equals(work,R)) {//регистрация
                char* vehicle = new char[32];
                cout << "Что вам нужно зарегистрировать? Автомобиль/Грузовик/Мотоцикл: ";
                cin >> vehicle;
                char* brand = new char[16];
                cout << "Марка: ";
                cin >> brand;
                int year;
                cout << "Год выпуска: ";
                cin >> year;
                int mileage;
                cout << "Пробег: ";
                cin >> mileage;

                char car[] = "Автомобиль";
                char bike[] = "Мотоцикл";
                if (Vehicle::equals(vehicle, car)) {//автомобиль
                    Passenger_car car;
                    car.setAll(brand, year, mileage, "Не зарегистрировано");
                    car.getAllFileCar();
                    car.RegistrationPrice();
                    car.RegistrationPriceFile();
                } else if (Vehicle::equals(vehicle, bike)) {//мотоцикл
                    Motorcycle motorcycle;
                    motorcycle.setAll(brand, year, mileage, "Не зарегистрировано");
                    motorcycle.getAllFileMotorcycle();
                    motorcycle.RegistrationPrice();
                    motorcycle.RegistrationPriceFile();
                } else {//грузовик
                    Truck truck;
                    truck.setAll(brand, year, mileage, "Не зарегистрировано");
                    truck.getAllFileTruck();
                    truck.RegistrationPrice();
                    truck.RegistrationPriceFile();
                    
                }
                delete[] vehicle;
                delete[] brand;

            } else {//тех.обслуживание
                char* vehicle = new char[32];
                cout << "Какое у вас транспортное средство? Автомобиль/Грузовик/Мотоцикл: ";
                cin >> vehicle;
                char* brand = new char[16];
                cout << "Марка: ";
                cin >> brand;
                int year;
                cout << "Год выпуска: ";
                cin >> year;
                int mileage;
                cout << "Пробег: ";
                cin >> mileage;

                char* deal = new char[64];
                cout << "Что вам необходимо? Диагностика/Смена_масла/Замена_деталей/Ремонт: ";
                cin >> deal;
                char find[] = "Диагностика";
                char oil[] = "Смена_масла";
                char details[] = "Замена_деталей";

                char car[] = "Автомобиль";
                char bike[] = "Мотоцикл";
                char type[] = "Впервые";
                if (Vehicle::equals(vehicle, car)) {//автомобиль
                    Passenger_car car;
                    car.setAll(brand, year, mileage, "Зарегистрировано");
                    car.getAllFileCar();
                    if (Vehicle::equals(deal,find)) {//диагностика
                        MaintenanceRecord service;
                        service.setAll(deal, 3000);
                        MaintenanceRecord final = +service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(3000);
                        } else {
                            service.Price(3000,0.2);
                        }
                    } else if (Vehicle::equals(deal,oil)) {//замена масла
                        MaintenanceRecord service;
                        service.setAll(deal, 4700);
                        MaintenanceRecord final = -service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(4700);
                        } else {
                            service.Price(4700,0.2);
                        }
                    } else if (Vehicle::equals(deal,details)) {//замена деталей
                        MaintenanceRecord service;
                        service.setAll(deal, 7200);
                        MaintenanceRecord final = *service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(7200);
                        } else {
                            service.Price(7200,0.2);
                        }
                    } else {//ремонт
                        MaintenanceRecord service;
                        service.setAll(deal, 11500);
                        MaintenanceRecord final = !service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(11500);
                        } else {
                            service.Price(11500,0.2);
                        }
                    }
                } else if (Vehicle::equals(vehicle, bike)) {//мотоцикл
                    Motorcycle motorcycle;
                    motorcycle.setAll(brand, year, mileage, "Зарегистрировано");
                    motorcycle.getAllFileMotorcycle();
                    if (Vehicle::equals(deal,find)) {//диагностика
                        MaintenanceRecord service;
                        service.setAll(deal, 2000);
                        MaintenanceRecord final = +service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(2000);
                        } else {
                            service.Price(2000,0.2);
                        }
                    } else if (Vehicle::equals(deal,oil)) {//замена масла
                        MaintenanceRecord service;
                        service.setAll(deal, 4700);
                        MaintenanceRecord final = -service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(4700);
                        } else {
                            service.Price(4700,0.2);
                        }
                    } else if (Vehicle::equals(deal,details)) {//замена деталей
                        MaintenanceRecord service;
                        service.setAll(deal, 5600);
                        MaintenanceRecord final = *service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(5600);
                        } else {
                            service.Price(5600,0.2);
                        }
                    } else {//ремонт
                        MaintenanceRecord service;
                        service.setAll(deal, 9400);
                        MaintenanceRecord final = !service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(9400);
                        } else {
                            service.Price(9400,0.2);
                        }
                    }
                } else {//грузовик
                    Truck truck;
                    truck.setAll(brand, year, mileage, "Зарегистрировано");
                    truck.getAllFileTruck();
                    if (Vehicle::equals(deal,find)) {//диагностика
                        MaintenanceRecord service;
                        service.setAll(deal, 5000);
                        MaintenanceRecord final = +service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(5000);
                        } else {
                            service.Price(5000,0.2);
                        }
                    } else if (Vehicle::equals(deal,oil)) {//замена масла
                        MaintenanceRecord service;
                        service.setAll(deal, 5700);
                        MaintenanceRecord final = -service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(5700);
                        } else {
                            service.Price(5700,0.2);
                        }
                    } else if (Vehicle::equals(deal,details)) {//замена деталей
                        MaintenanceRecord service;
                        service.setAll(deal, 9200);
                        MaintenanceRecord final = *service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(9200);
                        } else {
                            service.Price(9200,0.2);
                        }
                    } else {//ремонт
                        MaintenanceRecord service;
                        service.setAll(deal, 16500);
                        MaintenanceRecord final = !service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(16500);
                        } else {
                            service.Price(16500,0.2);
                        }
                    }
                }
                delete[] vehicle;
                delete[] brand;
                delete[] deal;
            }
            delete[] work;
            cout << "Интересует ли вас что-то еще? Да-1, нет-0: ";
            cin >> f_2;
        }
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "-----------------------------------------" << endl;
        file.close();
        number++;
        cout << "Услуга оказана, до свидания!" << endl << '\v';
        cout << "Если прием звонков завершен, введите 1, иначе 0: ";
        cin >> f_1;
        cout << '\v';
    }
    cout << "Выполнение онлайн записей на услуги..." << endl << '\v';
    int f_3 = 0;
    ifstream file_read;
    file_read.open("Online_record.txt");
    while (f_3!=1) {
        int num;
        file_read >> num;
        char* name = new char[64];
        file_read >> name;
        char* mail = new char[32];
        file_read >> mail;
        int age;
        file_read >> age;
        char* status = new char[16];
        file_read >> status;
        Customer human(name, mail, age, status);
        human.getAllFile(num+number-1);
 
        int f_2=1;
        while (f_2!=0) {
            char* work = new char[32];
            file_read >> work;
            char A[] = "Аренда";
            char R[] = "Регистрация";
            ofstream file;
            file.open("Daily_report.txt", ios_base::app);
            file << work << ": ";
            file.close();

            if (Vehicle::equals(work, A)) {//аренда
                char* vehicle = new char[32];
                file_read >> vehicle;
                char* brand = new char[16];
                file_read >> brand;
                int year;
                file_read >> year;
                int mileage;
                file_read >> mileage;
                int time;
                file_read >> time;

                char car[] = "Автомобиль";
                char bike[] = "Мотоцикл";
                if (Vehicle::equals(vehicle, car)) {//автомобиль
                    Passenger_car car;
                    car.setAll(brand, year, mileage, "Зарегистрировано");
                    car.getAllFileCar();
                    car.RentPriceFile(time, human.backStatus());
                } else if (Vehicle::equals(vehicle, bike)) {//мотоцикл
                    Motorcycle motorcycle;
                    motorcycle.setAll(brand, year, mileage, "Зарегистрировано");
                    motorcycle.getAllFileMotorcycle();
                    motorcycle.RentPriceFile(time, human.backStatus());
                } else {//грузовик
                    Truck truck;
                    truck.setAll(brand, year, mileage, "Зарегистрировано");
                    truck.getAllFileTruck();
                    truck.RentPriceFile(time, human.backStatus());
                }
                delete[] vehicle;
                delete[] brand;

            } else if (Vehicle::equals(work,R)) {//регистрация
                char* vehicle = new char[32];
                file_read >> vehicle;
                char* brand = new char[16];
                file_read >> brand;
                int year;
                file_read >> year;
                int mileage;
                file_read >> mileage;

                char car[] = "Автомобиль";
                char bike[] = "Мотоцикл";
                if (Vehicle::equals(vehicle, car)) {//автомобиль
                    Passenger_car car;
                    car.setAll(brand, year, mileage, "Не зарегистрировано");
                    car.getAllFileCar();
                    car.RegistrationPriceFile();
                } else if (Vehicle::equals(vehicle, bike)) {//мотоцикл
                    Motorcycle motorcycle;
                    motorcycle.setAll(brand, year, mileage, "Не зарегистрировано");
                    motorcycle.getAllFileMotorcycle();
                    motorcycle.RegistrationPriceFile();
                } else {//грузовик
                    Truck truck;
                    truck.setAll(brand, year, mileage, "Не зарегистрировано");
                    truck.getAllFileTruck();
                    truck.RegistrationPriceFile();     
                }
                delete[] vehicle;
                delete[] brand;

            } else {//тех.обслуживание
                char* vehicle = new char[32];
                file_read >> vehicle;
                char* brand = new char[16];
                file_read >> brand;
                int year;
                file_read >> year;
                int mileage;
                file_read >> mileage;

                char* deal = new char[64];
                file_read >> deal;
                char find[] = "Диагностика";
                char oil[] = "Смена_масла";
                char details[] = "Замена_деталей";

                char car[] = "Автомобиль";
                char bike[] = "Мотоцикл";
                char type[] = "Впервые";
                if (Vehicle::equals(vehicle, car)) {//автомобиль
                    Passenger_car car;
                    car.setAll(brand, year, mileage, "Зарегистрировано");
                    car.getAllFileCar();
                    if (Vehicle::equals(deal,find)) {//диагностика
                        MaintenanceRecord service;
                        service.setAll(deal, 3000);
                        MaintenanceRecord final = +service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(3000);
                        } else {
                            service.Price(3000,0.2);
                        }
                    } else if (Vehicle::equals(deal,oil)) {//замена масла
                        MaintenanceRecord service;
                        service.setAll(deal, 4700);
                        MaintenanceRecord final = -service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(4700);
                        } else {
                            service.Price(4700,0.2);
                        }
                    } else if (Vehicle::equals(deal,details)) {//замена деталей
                        MaintenanceRecord service;
                        service.setAll(deal, 7200);
                        MaintenanceRecord final = *service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(7200);
                        } else {
                            service.Price(7200,0.2);
                        }
                    } else {//ремонт
                        MaintenanceRecord service;
                        service.setAll(deal, 11500);
                        MaintenanceRecord final = !service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(11500);
                        } else {
                            service.Price(11500,0.2);
                        }
                    }
                } else if (Vehicle::equals(vehicle, bike)) {//мотоцикл
                    Motorcycle motorcycle;
                    motorcycle.setAll(brand, year, mileage, "Зарегистрировано");
                    motorcycle.getAllFileMotorcycle();
                    if (Vehicle::equals(deal,find)) {//диагностика
                        MaintenanceRecord service;
                        service.setAll(deal, 2000);
                        MaintenanceRecord final = +service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(2000);
                        } else {
                            service.Price(2000,0.2);
                        }
                    } else if (Vehicle::equals(deal,oil)) {//замена масла
                        MaintenanceRecord service;
                        service.setAll(deal, 4700);
                        MaintenanceRecord final = -service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(4700);
                        } else {
                            service.Price(4700,0.2);
                        }
                    } else if (Vehicle::equals(deal,details)) {//замена деталей
                        MaintenanceRecord service;
                        service.setAll(deal, 5600);
                        MaintenanceRecord final = *service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(5600);
                        } else {
                            service.Price(5600,0.2);
                        }
                    } else {//ремонт
                        MaintenanceRecord service;
                        service.setAll(deal, 9400);
                        MaintenanceRecord final = !service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(9400);
                        } else {
                            service.Price(9400,0.2);
                        }
                    }
                } else {//грузовик
                    Truck truck;
                    truck.setAll(brand, year, mileage, "Зарегистрировано");
                    truck.getAllFileTruck();
                    if (Vehicle::equals(deal,find)) {//диагностика
                        MaintenanceRecord service;
                        service.setAll(deal, 5000);
                        MaintenanceRecord final = +service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(5000);
                        } else {
                            service.Price(5000,0.2);
                        }
                    } else if (Vehicle::equals(deal,oil)) {//замена масла
                        MaintenanceRecord service;
                        service.setAll(deal, 5700);
                        MaintenanceRecord final = -service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(5700);
                        } else {
                            service.Price(5700,0.2);
                        }
                    } else if (Vehicle::equals(deal,details)) {//замена деталей
                        MaintenanceRecord service;
                        service.setAll(deal, 9200);
                        MaintenanceRecord final = *service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(9200);
                        } else {
                            service.Price(9200,0.2);
                        }
                    } else {//ремонт
                        MaintenanceRecord service;
                        service.setAll(deal, 16500);
                        MaintenanceRecord final = +service;
                        final.getAllFile();
                        if (Vehicle::equals(human.backStatus(), type)) {
                        service.Price(16500);
                        } else {
                            service.Price(16500,0.2);
                        }
                    }
                }
                delete[] vehicle;
                delete[] brand;
                delete[] deal;
            }
            delete[] work;
            file_read >> f_2;
        }
        ofstream file;
        file.open("Daily_report.txt", ios_base::app);
        file << "-----------------------------------------" << endl;
        file.close();
        num++;
        file_read >> f_3;
    }
    file_read.close();

    cout << "Рабочий день завершен." << endl;

	return 0;
}
