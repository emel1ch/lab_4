#pragma once
#include "RegularDepositor.h"
#include <msclr/marshal_cppstd.h>

namespace Основнаяработа {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class InputForm : public System::Windows::Forms::Form
	{
	public:
		// Поля для данных
		String^ EnteredName;
		double EnteredAmount;

		// --- КОНСТРУКТОР 1 (Добавление) ---
		InputForm(void)
		{
			InitializeComponent();
			this->Text = "Добавление нового вкладчика";
			this->btnOk->Text = "Добавить";
		}

		// --- КОНСТРУКТОР 2 (Редактирование) ---
		InputForm(String^ currentName, double currentAmount)
		{
			InitializeComponent();
			this->Text = "Редактирование данных";
			this->btnOk->Text = "Сохранить";
			this->BackColor = Color::LightYellow;

			// Заполняем поля старыми данными
			this->txtName->Text = currentName;
			this->txtAmount->Text = currentAmount.ToString();
		}

	protected:
		~InputForm()
		{
			if (components) delete components;
		}

	private: System::Windows::Forms::TextBox^ txtName;
	private: System::Windows::Forms::TextBox^ txtAmount;
	private: System::Windows::Forms::Button^ btnOk;
	private: System::Windows::Forms::Button^ btnCancel;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->txtName = (gcnew System::Windows::Forms::TextBox());
			   this->txtAmount = (gcnew System::Windows::Forms::TextBox());
			   this->btnOk = (gcnew System::Windows::Forms::Button());
			   this->btnCancel = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(72, 32);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(33, 16);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"Имя";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(202, 32);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(50, 16);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"Сумма";
			   // 
			   // txtName
			   // 
			   this->txtName->Location = System::Drawing::Point(39, 82);
			   this->txtName->Name = L"txtName";
			   this->txtName->Size = System::Drawing::Size(100, 22);
			   this->txtName->TabIndex = 2;
			   // 
			   // txtAmount
			   // 
			   this->txtAmount->Location = System::Drawing::Point(170, 82);
			   this->txtAmount->Name = L"txtAmount";
			   this->txtAmount->Size = System::Drawing::Size(100, 22);
			   this->txtAmount->TabIndex = 3;
			   // 
			   // btnOk
			   // 
			   this->btnOk->DialogResult = System::Windows::Forms::DialogResult::None;
			   this->btnOk->Location = System::Drawing::Point(55, 143);
			   this->btnOk->Name = L"btnOk";
			   this->btnOk->Size = System::Drawing::Size(75, 23);
			   this->btnOk->TabIndex = 4;
			   this->btnOk->Text = L"Ok";
			   this->btnOk->UseVisualStyleBackColor = true;
			   this->btnOk->Click += gcnew System::EventHandler(this, &InputForm::btnOk_Click);
			   // 
			   // btnCancel
			   // 
			   this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			   this->btnCancel->Location = System::Drawing::Point(186, 143);
			   this->btnCancel->Name = L"btnCancel";
			   this->btnCancel->Size = System::Drawing::Size(75, 23);
			   this->btnCancel->TabIndex = 5;
			   this->btnCancel->Text = L"Отмена";
			   this->btnCancel->UseVisualStyleBackColor = true;
			   // 
			   // InputForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(400, 250);
			   this->Controls->Add(this->btnCancel);
			   this->Controls->Add(this->btnOk);
			   this->Controls->Add(this->txtAmount);
			   this->Controls->Add(this->txtName);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Name = L"InputForm";
			   this->Text = L"Ввод данных";
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

	private: System::Void btnOk_Click(System::Object^ sender, System::EventArgs^ e) {
		// 1. Считываем данные
		this->EnteredName = this->txtName->Text;

		// 2. Считываем и проверяем число
		try {
			if (this->txtAmount->Text->Length > 0)
				this->EnteredAmount = Convert::ToDouble(this->txtAmount->Text);
			else
				this->EnteredAmount = 0;

			// Проверка диапазона 0..100000
			if (this->EnteredAmount < 0 || this->EnteredAmount > 100000) {
				MessageBox::Show("Сумма должна быть от 0 до 100 000!", "Ошибка ввода");
				return;
			}
		}
		catch (...) {
			MessageBox::Show("Некорректная сумма (введите число)", "Ошибка");
			return;
		}

		// 3. Проверяем имя
		if (String::IsNullOrEmpty(this->EnteredName)) {
			MessageBox::Show("Введите имя!", "Ошибка");
			return;
		}

		// 4. Всё ок -> закрываем
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
	};
}