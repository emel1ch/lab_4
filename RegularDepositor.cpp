#include "RegularDepositor.h"

// Реализация конструктора по умолчанию
RegularDepositor::RegularDepositor() {
    this->fullName = "Unknown";
    this->depositAmount = 0.0;
}

// Реализация основного конструктора
RegularDepositor::RegularDepositor(std::string name, double amount) {
    this->fullName = name;
    this->depositAmount = amount;
}

std::string RegularDepositor::getName() {
    return this->fullName;
}

double RegularDepositor::getAmount() {
    return this->depositAmount;
}

void RegularDepositor::setName(std::string name) {
    this->fullName = name;
}

void RegularDepositor::setAmount(double amount) {
    this->depositAmount = amount;
}

// Конвертация std::string -> System::String^
String^ RegularDepositor::getNameNet() {
    return msclr::interop::marshal_as<String^>(this->fullName);
}