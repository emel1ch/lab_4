#pragma once
#include "RegularDepositor.h" 
#include "InputForm.h"        
#include <vector>             
#include <fstream>            
#include <algorithm>          
#include <msclr/marshal_cppstd.h> 

// Функция сортировки (вынесена наружу, чтобы избежать ошибок лямбды)
inline bool compareDepositors(RegularDepositor& a, RegularDepositor& b) {
    return a.getAmount() > b.getAmount();
}
// Функция для ручной конвертации System::String^ -> std::string
// Помогает, когда msclr::marshal_as выдает ошибки
inline std::string SystemToStdString(System::String^ s) {
    if (s == nullptr) return ""; // Защита от пустых строк
    using namespace System::Runtime::InteropServices;
    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    std::string os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
    return os;
}

namespace Основнаяработа { // Проверьте, что это имя совпадает с именем вашего проекта!

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();

            // Выделяем память под вектор (решение ошибки смешанных типов)
            db = new std::vector<RegularDepositor>();

            // Инициализация таблицы
            dataGridView1->ColumnCount = 2;
            dataGridView1->Columns[0]->Name = "Имя вкладчика";
            dataGridView1->Columns[1]->Name = "Сумма вклада";
            dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            // Тестовая запись
            //db->push_back(RegularDepositor("Тестовый Вкладчик", 1000.0));
            //UpdateGrid();
        }

    protected:
        ~MainForm()
        {
            // Очистка памяти
            if (db) {
                delete db;
                db = nullptr;
            }
            if (components) delete components;
        }

    private:
        // Указатель на вектор (важно для Windows Forms!)
        std::vector<RegularDepositor>* db;

        // Элементы формы
    private: System::Windows::Forms::MenuStrip^ menuStrip1;
    private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ сохранитьToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ загрузитьToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ вкладчикиToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ добавитьToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ редактироватьToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ удалитьToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ сортироватьToolStripMenuItem;
    private: System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
    private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
    private: System::Windows::Forms::StatusStrip^ statusStrip1;
    private: System::Windows::Forms::ToolStripStatusLabel^ statsLabel;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
               this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
               this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->загрузитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->вкладчикиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->добавитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->редактироватьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->удалитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->сортироватьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
               this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
               this->menuStrip1->SuspendLayout();
               this->SuspendLayout();
               // 
               // dataGridView1
               // 
               this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
               this->dataGridView1->Location = System::Drawing::Point(0, 24);
               this->dataGridView1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
               this->dataGridView1->MultiSelect = false;
               this->dataGridView1->Name = L"dataGridView1";
               this->dataGridView1->ReadOnly = true;
               this->dataGridView1->RowHeadersWidth = 51;
               this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
               this->dataGridView1->Size = System::Drawing::Size(631, 412);
               this->dataGridView1->TabIndex = 1;
               this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridView1_CellContentClick);
               // 
               // menuStrip1
               // 
               this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
               this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                   this->файлToolStripMenuItem,
                       this->вкладчикиToolStripMenuItem
               });
               this->menuStrip1->Location = System::Drawing::Point(0, 0);
               this->menuStrip1->Name = L"menuStrip1";
               this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
               this->menuStrip1->Size = System::Drawing::Size(631, 24);
               this->menuStrip1->TabIndex = 0;
               this->menuStrip1->Text = L"menuStrip1";
               // 
               // файлToolStripMenuItem
               // 
               this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                   this->сохранитьToolStripMenuItem,
                       this->загрузитьToolStripMenuItem, this->выходToolStripMenuItem
               });
               this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
               this->файлToolStripMenuItem->Size = System::Drawing::Size(48, 20);
               this->файлToolStripMenuItem->Text = L"Файл";
               // 
               // сохранитьToolStripMenuItem
               // 
               this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
               this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(132, 22);
               this->сохранитьToolStripMenuItem->Text = L"Сохранить";
               this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveToolStripMenuItem_Click);
               // 
               // загрузитьToolStripMenuItem
               // 
               this->загрузитьToolStripMenuItem->Name = L"загрузитьToolStripMenuItem";
               this->загрузитьToolStripMenuItem->Size = System::Drawing::Size(132, 22);
               this->загрузитьToolStripMenuItem->Text = L"Загрузить";
               this->загрузитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadToolStripMenuItem_Click);
               // 
               // выходToolStripMenuItem
               // 
               this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
               this->выходToolStripMenuItem->Size = System::Drawing::Size(132, 22);
               this->выходToolStripMenuItem->Text = L"Выход";
               this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
               // 
               // вкладчикиToolStripMenuItem
               // 
               this->вкладчикиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                   this->добавитьToolStripMenuItem,
                       this->редактироватьToolStripMenuItem, this->удалитьToolStripMenuItem, this->сортироватьToolStripMenuItem
               });
               this->вкладчикиToolStripMenuItem->Name = L"вкладчикиToolStripMenuItem";
               this->вкладчикиToolStripMenuItem->Size = System::Drawing::Size(78, 20);
               this->вкладчикиToolStripMenuItem->Text = L"Вкладчики";
               // 
               // добавитьToolStripMenuItem
               // 
               this->добавитьToolStripMenuItem->Name = L"добавитьToolStripMenuItem";
               this->добавитьToolStripMenuItem->Size = System::Drawing::Size(154, 22);
               this->добавитьToolStripMenuItem->Text = L"Добавить";
               this->добавитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::addToolStripMenuItem_Click);
               // 
               // редактироватьToolStripMenuItem
               // 
               this->редактироватьToolStripMenuItem->Name = L"редактироватьToolStripMenuItem";
               this->редактироватьToolStripMenuItem->Size = System::Drawing::Size(154, 22);
               this->редактироватьToolStripMenuItem->Text = L"Редактировать";
               this->редактироватьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::editItemToolStripMenuItem_Click);
               // 
               // удалитьToolStripMenuItem
               // 
               this->удалитьToolStripMenuItem->Name = L"удалитьToolStripMenuItem";
               this->удалитьToolStripMenuItem->Size = System::Drawing::Size(154, 22);
               this->удалитьToolStripMenuItem->Text = L"Удалить";
               this->удалитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::deleteToolStripMenuItem_Click);
               // 
               // сортироватьToolStripMenuItem
               // 
               this->сортироватьToolStripMenuItem->Name = L"сортироватьToolStripMenuItem";
               this->сортироватьToolStripMenuItem->Size = System::Drawing::Size(154, 22);
               this->сортироватьToolStripMenuItem->Text = L"Сортировать";
               this->сортироватьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::sortToolStripMenuItem_Click);
               // 
               // saveFileDialog1
               // 
               this->saveFileDialog1->DefaultExt = L"txt";
               this->saveFileDialog1->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
               // 
               // MainForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(631, 436);
               this->Controls->Add(this->dataGridView1);
               this->Controls->Add(this->menuStrip1);
               this->MainMenuStrip = this->menuStrip1;
               this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
               this->Name = L"MainForm";
               this->Text = L"Управление вкладчиками";
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
               this->menuStrip1->ResumeLayout(false);
               this->menuStrip1->PerformLayout();
               this->ResumeLayout(false);
               // Внутри InitializeComponent(void)

// 1. Создаем объекты
               this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
               this->statsLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());

               // 2. Настраиваем statusStrip (панель внизу)
               this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^ >(1) { this->statsLabel });
               this->statusStrip1->Location = System::Drawing::Point(0, 414);
               this->statusStrip1->Name = L"statusStrip1";
               this->statusStrip1->Size = System::Drawing::Size(631, 22);
               this->statusStrip1->TabIndex = 2;
               this->statusStrip1->Text = L"statusStrip1";

               // 3. Настраиваем statsLabel (текст)
               this->statsLabel->Name = L"statsLabel";
               this->statsLabel->Size = System::Drawing::Size(118, 17);
               this->statsLabel->Text = L"Статистика...";

               // 4. Добавляем на форму
               this->Controls->Add(this->statusStrip1);
               this->PerformLayout();

           }
#pragma endregion

           // --- ЛОГИКА ---

           void UpdateGrid() {
               dataGridView1->Rows->Clear();

               // Переменная для подсчета общей суммы
               double totalSum = 0.0;

               for (int i = 0; i < db->size(); i++) {
                   RegularDepositor& dep = db->at(i);
                   String^ name = dep.getNameNet();

                   // Получаем сумму
                   double amount = dep.getAmount();

                   // Добавляем к общей сумме
                   totalSum += amount;

                   String^ amountStr = amount.ToString();
                   dataGridView1->Rows->Add(name, amountStr);
               }

               // Обновляем статистику внизу окна
               // db->size() - это количество людей
               // "N2" форматирует число красиво (два знака после запятой)
               this->statsLabel->Text = "Вкладчиков: " + db->size() +
                   " | Общая сумма: " + totalSum.ToString("N2") + " руб.";
           }

           // 1. ДОБАВИТЬ
           System::Void addToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
               // Проверка 1: Инициализирован ли вектор?
               if (db == nullptr) {
                   MessageBox::Show("Критическая ошибка: База данных не инициализирована!", "Ошибка");
                   db = new std::vector<RegularDepositor>(); // Пытаемся починить на ходу
               }

               InputForm^ form = gcnew InputForm();

               // Показываем форму
               if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                   try {
                       // Проверка 2: Получили ли мы данные?
                       if (form->EnteredName == nullptr) {
                           MessageBox::Show("Ошибка: Имя пустое (nullptr)", "Debug");
                           return;
                       }

                       // Конвертация
                       std::string n = SystemToStdString(form->EnteredName);
                       double a = form->EnteredAmount;

                       // Добавление
                       db->push_back(RegularDepositor(n, a));

                       // Обновление таблицы
                       UpdateGrid();
                   }
                   catch (Exception^ ex) {
                       MessageBox::Show("Ошибка при добавлении: " + ex->Message, "Crash Report");
                   }
                   catch (...) {
                       MessageBox::Show("Неизвестная ошибка C++ при добавлении", "Crash Report");
                   }
               }
           }

           // 2. РЕДАКТИРОВАТЬ
           System::Void editItemToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
               if (dataGridView1->SelectedRows->Count > 0) {
                   int index = dataGridView1->SelectedRows[0]->Index;
                   if (index >= 0 && index < db->size()) {
                       RegularDepositor& dep = db->at(index);
                       String^ curName = dep.getNameNet();
                       double curAmount = dep.getAmount();

                       InputForm^ form = gcnew InputForm(curName, curAmount);
                       if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                           std::string n = SystemToStdString(form->EnteredName);                        // ... внутри условия if (ShowDialog == OK) ...
                           dep.setName(n);
                           dep.setAmount(form->EnteredAmount);

                           UpdateGrid(); // <--- ОБЯЗАТЕЛЬНО ОБНОВИТЬ ТАБЛИЦУ
                       }
                   }
               }
               else {
                   MessageBox::Show("Выберите строку для редактирования!");
               }

           }

           // 3. УДАЛИТЬ
           System::Void deleteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
               if (dataGridView1->SelectedRows->Count > 0) {
                   int index = dataGridView1->SelectedRows[0]->Index;
                   if (index >= 0 && index < db->size()) {
                       db->erase(db->begin() + index);
                       UpdateGrid();
                   }
               }
               else {
                   MessageBox::Show("Выберите строку для удаления!");
               }
           }

           // 4. СОРТИРОВКА (теперь использует внешнюю функцию)
           System::Void sortToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
               std::sort(db->begin(), db->end(), compareDepositors);
               UpdateGrid();
               MessageBox::Show("Отсортировано по убыванию вклада!");
           }

           // 5. СОХРАНИТЬ
           System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
               if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                   std::string filename = SystemToStdString(saveFileDialog1->FileName);                   std::ofstream out(filename);
                   if (out.is_open()) {
                       for (int i = 0; i < db->size(); i++) {
                           out << db->at(i).getName() << ";" << db->at(i).getAmount() << "\n";
                       }
                       out.close();
                       MessageBox::Show("Сохранено!");
                   }
               }
           }

           // 6. ЗАГРУЗИТЬ
          // 6. ЗАГРУЗИТЬ
           System::Void loadToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
               // Настраиваем фильтр:
               // Слева от палочки | текст для пользователя
               // Справа от палочки | маска файла (*.txt)
               // Мы убрали "|Все файлы (*.*)|*.*", поэтому выбрать что-то другое теперь нельзя.
               openFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt";

               // Дополнительно: проверяем, существует ли файл (обычно True по умолчанию, но на всякий случай)
               openFileDialog1->CheckFileExists = true;

               if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                   // Конвертация имени файла
                   std::string filename = SystemToStdString(openFileDialog1->FileName);

                   std::ifstream in(filename);
                   if (in.is_open()) {
                       db->clear(); // Очищаем список

                       std::string lineName;
                       double lineAmount;

                       // 1. Читаем строку из файла до символа ';' и кладем в lineName
                       while (std::getline(in, lineName, ';')) {

                           // 2. Сразу после этого пытаемся считать число
                           if (in >> lineAmount) {

                               // Добавляем в вектор
                               db->push_back(RegularDepositor(lineName, lineAmount));

                               // ВАЖНО: После числа в файле остался символ переноса строки (\n).
                               // Его нужно "съесть", чтобы перейти к следующей записи.
                               std::string dummy;
                               std::getline(in, dummy);
                           }
                       }

                       in.close();
                       UpdateGrid();
                       MessageBox::Show("Данные успешно загружены из текстового файла!", "Успех");
                   }
                   else {
                       MessageBox::Show("Не удалось открыть файл!", "Ошибка");
                   }
               }
           }

           // 7. ВЫХОД
           System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
               Application::Exit();
           }
    private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
    }
};
}