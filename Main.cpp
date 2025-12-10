#include "MainForm.h" // Подключаем заголовочный файл вашей формы

using namespace System;
using namespace System::Windows::Forms;

// Указываем, что это оконное приложение с одним потоком
[STAThreadAttribute]
int main(array<String^>^ args) {
    // Включаем визуальные стили (чтобы кнопки были красивые, как в Windows 10/11)
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // !!! ВАЖНО: Замените 'Основнаяработа' на имя пространства имен из вашего MainForm.h
    // Если вы копировали мой прошлый код, то namespace там был 'Основнаяработа'
    Основнаяработа::MainForm form;

    // Запускаем форму
    Application::Run(% form);

    return 0;
}