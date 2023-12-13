#include "MaintenanceRecord.h"
#include <iostream>
#include <fstream>
using namespace std;

MaintenanceRecord::MaintenanceRecord() {
    setAll("Тип", 0);
}
MaintenanceRecord::MaintenanceRecord(const char* m_deal, int m_price) {
    setAll(m_deal, m_price);
}
MaintenanceRecord::MaintenanceRecord(MaintenanceRecord const & copy) {
    setAll(copy.deal, copy.price);
}
MaintenanceRecord::~MaintenanceRecord() {
    delete[] deal;
}

void MaintenanceRecord::getDeal() {
    cout << deal << endl;
}
void MaintenanceRecord::getPrice() {
    cout << "Стоимость технического обслуживания: " << price << endl;
}
void MaintenanceRecord::getAll() {
    cout << deal << endl;
    cout << "Стоимость технического обслуживания: " << price << endl;
}
void MaintenanceRecord::getAllFile() {
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << deal << endl;
    file << "Стоимость технического обслуживания: " << price << endl;
    file.close();
}

void MaintenanceRecord::setDeal(const char* m_deal) {
    delete[] deal;
    deal = new char[strlen(m_deal) + 1];
    strcpy(deal, m_deal);
}
void MaintenanceRecord::setPrice(int m_price) {
    price = m_price;
}
void MaintenanceRecord::setAll(const char* m_deal, int m_price) {
    setDeal(m_deal);
    price = m_price;
}
//перегрузка функции с использованием скидки и нет(то есть два параметра и один)/одновременная запись в файл
void MaintenanceRecord::Price(int money) {//суть перегрузки - использование одного имени функции для нескольких функций
    cout << this->deal << " по стоимости: " << money << endl;
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << this->deal << " по стоимости: " << money << endl;
    file.close();
}
void MaintenanceRecord::Price(int money, double sale) {//внешние функции могут отличаться только типом возвращаемого значения/количеством и типом параметров, а внутренние еще и реализацией
    cout << this->deal << " по стоимости со скидкой 20%: " << money - money*sale << endl;
    ofstream file;
    file.open("Daily_report.txt", ios_base::app);
    file << this->deal << " по стоимости со скидкой 20%: " << money - money*sale << endl;
    file.close();
}
//перегрузка операторов для Диагностики/Смены масла/ Замены деталей/ Ремонта
MaintenanceRecord MaintenanceRecord::operator +() {
    MaintenanceRecord find(deal, price);
    find.setDeal("Диагностика - ВСЕ ИСПРАВНО");
    return find;
}
MaintenanceRecord MaintenanceRecord::operator -() {
    MaintenanceRecord oil(deal, price);
    oil.setDeal("Смена масла - ГОТОВО");
    return oil;
}
MaintenanceRecord MaintenanceRecord::operator *() {
    MaintenanceRecord details(deal, price);
    details.setDeal("Замена деталей - ГОТОВО");
    return details;
}
MaintenanceRecord MaintenanceRecord::operator !() {
    MaintenanceRecord fix(deal, price);
    fix.setDeal("Ремонт - ВСЕ ИСПРАВНО");
    return fix;
}
