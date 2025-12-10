#pragma once
#include <string>
#include <msclr/marshal_cppstd.h> // Библиотека для конвертации строк

using namespace System;

// Обычный C++ класс (Model)
class RegularDepositor {
private:
    std::string fullName;
    double depositAmount;

public:
    // Конструктор по умолчанию
    RegularDepositor();

    // Основной конструктор
    RegularDepositor(std::string name, double amount);

    // Геттеры (получение данных)
    std::string getName();
    double getAmount();

    // Сеттеры (изменение данных)
    void setName(std::string name);
    void setAmount(double amount);

    // Метод для получения имени в формате .NET (для GUI)
    String^ getNameNet();
};
