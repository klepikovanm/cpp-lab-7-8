#include "Customer.h"
#include <iostream>
#include <fstream>
using namespace std;

Customer::Customer() {
    setAll("Имя", "Почта", 0, "Статус");
}
Customer::Customer(const char* c_name, const char* c_mail, int c_age, const char* c_status) {
    setAll(c_name, c_mail, c_age, c_status);
}
Customer::Customer(Customer const & copy) {
    setAll(copy.name, copy.mail, copy.age, copy.status);
}
Customer::~Customer() {
	delete[] name;
    delete[] mail;
	delete[] status;
}
	//Функции для вывода на экран
	//get-функции позволяют посмотреть значения элементов данных
void Customer::getName()const {//пишем в конце const, так как метод не меняет содержимое класса
    cout << "Имя: " << name << endl;
}
void Customer::getMail()const {
    cout << "Почта: " << mail << endl;
}
void Customer::getAge()const {
    cout << "Возраст: " << age << endl;
}
void Customer::getStatus()const {
    cout << "Статус клиента: " << age << endl;
}
void Customer::getAll()const {
    cout << "Имя: " << name << endl;
    cout << "Почта: " << mail << endl;
    cout << "Возраст: " << age << endl;
    cout << "Статус клиента: " << status << endl;
}
void Customer::getAllFile(int number)const {
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
void Customer::setName(const char* c_name) {//передается строка, из-за чего на нее выделяется память, и деструктор не может удалить строку
    delete[] name;//чистим память, удаляя прошлые данные
    name = new char[strlen(c_name) + 1];//выделяем новую память: длина нового значения + \0
    strcpy(name, c_name);//побайтово копируем новое значение в переменную из char* в char* до \0
}
void Customer::setMail(const char* c_mail) {
    delete[] mail;
    mail = new char[strlen(c_mail) + 1];
    strcpy(mail, c_mail);
}
void Customer::setAge(int c_age) {
    age = c_age;
}
void Customer::setStatus(const char* c_status) {
    delete[] status;
    status = new char[strlen(c_status) + 1];
    strcpy(status, c_status);
}
void Customer::setAll(const char* c_name, const char* c_mail, int c_age, const char* c_status) {
    setName(c_name);
    setMail(c_mail);
    age = c_age;
    setStatus(c_status);
}
const char* Customer::backStatus()const {
    return status;
}
