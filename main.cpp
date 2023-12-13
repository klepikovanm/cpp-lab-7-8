#include <iostream>
#include <fstream>

#include "Vehicle.h"
#include "Customer.h"
#include "MaintenanceRecord.h"
using namespace std;

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
        char V[] = "Впервые";
        char P[] = "Постоянный";
        cin >> status;
        if (!Vehicle::equals(status,V) && !Vehicle::equals(status,P)) {
            while (!Vehicle::equals(status,V) && !Vehicle::equals(status,P)) {
                cout << "Значение введено неверно, повторите попытку: ";
                cin >> status;
            }
        }
        
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
            char T[] = "Тех.обслуживание";
            if (!Vehicle::equals(work,A) && !Vehicle::equals(work,R) && !Vehicle::equals(work,T)) {
                while(!Vehicle::equals(work,A) && !Vehicle::equals(work,R) && !Vehicle::equals(work,T)) {
                    cout << "Значение введено неверно, повторите попытку: ";
                    cin >> work;
                }
            }

            ofstream file;
            file.open("Daily_report.txt", ios_base::app);
            file << work << ": ";
            file.close();

            char C[] = "Автомобиль";
            char G[] = "Грузовик";
            char M[] = "Мотоцикл";
            if (Vehicle::equals(work, A)) {//аренда
                char* vehicle = new char[32];
                cout << "Что вы бы хотели арендовать? Автомобиль/Грузовик/Мотоцикл: ";
                cin >> vehicle;
                if (!Vehicle::equals(vehicle,C) && !Vehicle::equals(vehicle,G) && !Vehicle::equals(vehicle,M)) {
                    while(!Vehicle::equals(vehicle,C) && !Vehicle::equals(vehicle,G) && !Vehicle::equals(vehicle,M)) {
                        cout << "Значение введено неверно, повторите попытку: ";
                        cin >> vehicle;
                    }
                }
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
                if (!Vehicle::equals(vehicle,C) && !Vehicle::equals(vehicle,G) && !Vehicle::equals(vehicle,M)) {
                    while(!Vehicle::equals(vehicle,C) && !Vehicle::equals(vehicle,G) && !Vehicle::equals(vehicle,M)) {
                        cout << "Значение введено неверно, повторите попытку: ";
                        cin >> vehicle;
                    }
                }
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
                if (!Vehicle::equals(vehicle,C) && !Vehicle::equals(vehicle,G) && !Vehicle::equals(vehicle,M)) {
                    while(!Vehicle::equals(vehicle,C) && !Vehicle::equals(vehicle,G) && !Vehicle::equals(vehicle,M)) {
                        cout << "Значение введено неверно, повторите попытку: ";
                        cin >> vehicle;
                    }
                }
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
                char fix[] = "Ремонт";
                if (!Vehicle::equals(deal,find) && !Vehicle::equals(deal,oil) && !Vehicle::equals(deal,details) && !Vehicle::equals(deal,fix)) {
                    while(!Vehicle::equals(deal,find) && !Vehicle::equals(deal,oil) && !Vehicle::equals(deal,details) && !Vehicle::equals(deal,fix)) {
                        cout << "Значение введено неверно, повторите попытку: ";
                        cin >> deal;
                    }
                }

                char type[] = "Впервые";
                if (Vehicle::equals(vehicle, C)) {//автомобиль
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
                } else if (Vehicle::equals(vehicle, M)) {//мотоцикл
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
