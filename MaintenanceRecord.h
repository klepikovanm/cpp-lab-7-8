#include <iostream>
#include <fstream>
using namespace std;

#ifndef CPP_LAB_7_8_MAINTENANCERECORD
#define CPP_LAB_7_8_MAINTENANCERECORD

class MaintenanceRecord {
private:
    char* deal = nullptr;//какое именно обслуживание и его итог
    int price;
public:
    MaintenanceRecord();
    MaintenanceRecord(const char* m_deal, int m_price);
    MaintenanceRecord(MaintenanceRecord const & copy);
    ~MaintenanceRecord();

    void getDeal();
    void getPrice();
    void getAll();
    void getAllFile();
    void setDeal(const char* m_deal);
    void setPrice(int m_price);
    void setAll(const char* m_deal, int m_price);
    //перегрузка функции с использованием скидки и нет(то есть два параметра и один)/одновременная запись в файл
    void Price(int money);
    void Price(int money, double sale);
    //перегрузка операторов для Диагностики/Смены масла/ Замены деталей/ Ремонта
    MaintenanceRecord operator +();
    MaintenanceRecord operator -();
    MaintenanceRecord operator *();
    MaintenanceRecord operator !();
};

#endif