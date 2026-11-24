#pragma once

namespace Motioncompensation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			this->trackBarAmplitude->Scroll += gcnew System::EventHandler(this, &MyForm::trackBarAmplitude_Scroll);
		}

	protected:
		~MyForm()
		{
			if (components) delete components;
		}

	private:
		System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
		System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::Button^ button2;
		System::Windows::Forms::Button^ button3;
		System::Windows::Forms::Button^ button4;
		System::Windows::Forms::Button^ button5;
		System::Windows::Forms::Button^ button6;
		System::Windows::Forms::NumericUpDown^ numericOrderShip;
		System::Windows::Forms::NumericUpDown^ numericOrderTrain;
		System::Windows::Forms::NumericUpDown^ numericKalmanQ;
		System::Windows::Forms::NumericUpDown^ numericKalmanR;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::Label^ label4;
		System::Windows::Forms::Label^ label5;
		System::Windows::Forms::Label^ labelAmplitudeValue;
		System::Windows::Forms::TrackBar^ trackBarAmplitude;
		System::Windows::Forms::GroupBox^ groupBoxAR;
		System::Windows::Forms::GroupBox^ groupBoxKalman;
		System::Windows::Forms::GroupBox^ groupBoxAmplitude;
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->numericOrderShip = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericOrderTrain = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericKalmanQ = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericKalmanR = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->labelAmplitudeValue = (gcnew System::Windows::Forms::Label());
			this->trackBarAmplitude = (gcnew System::Windows::Forms::TrackBar());
			this->groupBoxAR = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxKalman = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxAmplitude = (gcnew System::Windows::Forms::GroupBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericOrderShip))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericOrderTrain))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericKalmanQ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericKalmanR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarAmplitude))->BeginInit();
			this->groupBoxAR->SuspendLayout();
			this->groupBoxKalman->SuspendLayout();
			this->groupBoxAmplitude->SuspendLayout();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Location = System::Drawing::Point(12, 12);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(750, 300);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->ChartAreas["ChartArea1"]->AxisX->Title = L"Время (с)";
			this->chart1->ChartAreas["ChartArea1"]->AxisY->Title = L"Амплитуда";
			this->chart1->Series["Series1"]->BorderWidth = 2;
			this->chart1->Series["Series1"]->Color = System::Drawing::Color::Blue;
			// 
			// chart2
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			this->chart2->Location = System::Drawing::Point(12, 318);
			this->chart2->Name = L"chart2";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->Name = L"Series1";
			this->chart2->Series->Add(series2);
			this->chart2->Size = System::Drawing::Size(750, 300);
			this->chart2->TabIndex = 1;
			this->chart2->Text = L"chart2";
			this->chart2->ChartAreas["ChartArea1"]->AxisX->Title = L"Время (с)";
			this->chart2->ChartAreas["ChartArea1"]->AxisY->Title = L"Амплитуда";
			this->chart2->Series["Series1"]->BorderWidth = 2;
			this->chart2->Series["Series1"]->Color = System::Drawing::Color::Red;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(780, 580);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(130, 37);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Запустить";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(920, 580);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(130, 37);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Очистить";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// groupBoxAmplitude
			// 
			this->groupBoxAmplitude->Controls->Add(this->label5);
			this->groupBoxAmplitude->Controls->Add(this->labelAmplitudeValue);
			this->groupBoxAmplitude->Controls->Add(this->trackBarAmplitude);
			this->groupBoxAmplitude->Location = System::Drawing::Point(780, 12);
			this->groupBoxAmplitude->Name = L"groupBoxAmplitude";
			this->groupBoxAmplitude->Size = System::Drawing::Size(270, 110);
			this->groupBoxAmplitude->TabIndex = 10;
			this->groupBoxAmplitude->Text = L"Управление разбросом амплитуды";
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(10, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(250, 20);
			this->label5->TabIndex = 2;
			this->label5->Text = L"Постоянная << --- >> Сильный разброс";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelAmplitudeValue
			// 
			this->labelAmplitudeValue->Location = System::Drawing::Point(10, 80);
			this->labelAmplitudeValue->Name = L"labelAmplitudeValue";
			this->labelAmplitudeValue->Size = System::Drawing::Size(250, 20);
			this->labelAmplitudeValue->TabIndex = 1;
			this->labelAmplitudeValue->Text = L"Разброс: 50%";
			this->labelAmplitudeValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trackBarAmplitude
			// 
			this->trackBarAmplitude->Location = System::Drawing::Point(10, 45);
			this->trackBarAmplitude->Name = L"trackBarAmplitude";
			this->trackBarAmplitude->Size = System::Drawing::Size(250, 35);
			this->trackBarAmplitude->TabIndex = 0;
			this->trackBarAmplitude->Minimum = 0;
			this->trackBarAmplitude->Maximum = 100;
			this->trackBarAmplitude->Value = 50;
			this->trackBarAmplitude->TickFrequency = 10;
			this->trackBarAmplitude->LargeChange = 10;
			// 
			// groupBoxAR
			// 
			this->groupBoxAR->Controls->Add(this->label2);
			this->groupBoxAR->Controls->Add(this->label1);
			this->groupBoxAR->Controls->Add(this->numericOrderTrain);
			this->groupBoxAR->Controls->Add(this->numericOrderShip);
			this->groupBoxAR->Controls->Add(this->button4);
			this->groupBoxAR->Controls->Add(this->button3);
			this->groupBoxAR->Location = System::Drawing::Point(780, 130);
			this->groupBoxAR->Name = L"groupBoxAR";
			this->groupBoxAR->Size = System::Drawing::Size(270, 210);
			this->groupBoxAR->TabIndex = 8;
			this->groupBoxAR->Text = L"AR модель";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(15, 82);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(150, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Порядок AR (поезд):";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(15, 42);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(150, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Порядок AR (корабль):";
			// 
			// numericOrderTrain
			// 
			this->numericOrderTrain->Location = System::Drawing::Point(175, 80);
			this->numericOrderTrain->Name = L"numericOrderTrain";
			this->numericOrderTrain->Size = System::Drawing::Size(70, 22);
			this->numericOrderTrain->TabIndex = 7;
			this->numericOrderTrain->Minimum = System::Decimal(1);
			this->numericOrderTrain->Maximum = System::Decimal(20);
			this->numericOrderTrain->Value = System::Decimal(5);
			// 
			// numericOrderShip
			// 
			this->numericOrderShip->Location = System::Drawing::Point(175, 40);
			this->numericOrderShip->Name = L"numericOrderShip";
			this->numericOrderShip->Size = System::Drawing::Size(70, 22);
			this->numericOrderShip->TabIndex = 6;
			this->numericOrderShip->Minimum = System::Decimal(1);
			this->numericOrderShip->Maximum = System::Decimal(20);
			this->numericOrderShip->Value = System::Decimal(5);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(15, 125);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(240, 35);
			this->button3->TabIndex = 4;
			this->button3->Text = L"AR предсказание (корабль)";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(15, 166);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(240, 35);
			this->button4->TabIndex = 5;
			this->button4->Text = L"AR предсказание (поезд)";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// groupBoxKalman
			// 
			this->groupBoxKalman->Controls->Add(this->label4);
			this->groupBoxKalman->Controls->Add(this->label3);
			this->groupBoxKalman->Controls->Add(this->numericKalmanR);
			this->groupBoxKalman->Controls->Add(this->numericKalmanQ);
			this->groupBoxKalman->Controls->Add(this->button6);
			this->groupBoxKalman->Controls->Add(this->button5);
			this->groupBoxKalman->Location = System::Drawing::Point(780, 350);
			this->groupBoxKalman->Name = L"groupBoxKalman";
			this->groupBoxKalman->Size = System::Drawing::Size(270, 210);
			this->groupBoxKalman->TabIndex = 9;
			this->groupBoxKalman->Text = L"Фильтр Калмана";
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(15, 82);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(150, 20);
			this->label4->TabIndex = 3;
			this->label4->Text = L"R (шум измерений):";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(15, 42);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(150, 20);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Q (шум процесса):";
			// 
			// numericKalmanR
			// 
			this->numericKalmanR->Location = System::Drawing::Point(175, 80);
			this->numericKalmanR->Name = L"numericKalmanR";
			this->numericKalmanR->Size = System::Drawing::Size(70, 22);
			this->numericKalmanR->TabIndex = 7;
			this->numericKalmanR->Minimum = System::Decimal(1);
			this->numericKalmanR->Maximum = System::Decimal(100);
			this->numericKalmanR->Value = System::Decimal(1);
			// 
			// numericKalmanQ
			// 
			this->numericKalmanQ->Location = System::Drawing::Point(175, 40);
			this->numericKalmanQ->Name = L"numericKalmanQ";
			this->numericKalmanQ->Size = System::Drawing::Size(70, 22);
			this->numericKalmanQ->TabIndex = 6;
			this->numericKalmanQ->Minimum = System::Decimal(1);
			this->numericKalmanQ->Maximum = System::Decimal(100);
			this->numericKalmanQ->Value = System::Decimal(10);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(15, 125);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(240, 35);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Калман (корабль)";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(15, 166);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(240, 35);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Калман (поезд)";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1064, 630);
			this->Controls->Add(this->groupBoxAmplitude);
			this->Controls->Add(this->groupBoxKalman);
			this->Controls->Add(this->groupBoxAR);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Name = L"MyForm";
			this->Text = L"Компенсация движения";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericOrderShip))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericOrderTrain))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericKalmanQ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericKalmanR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarAmplitude))->EndInit();
			this->groupBoxAR->ResumeLayout(false);
			this->groupBoxAR->PerformLayout();
			this->groupBoxKalman->ResumeLayout(false);
			this->groupBoxKalman->PerformLayout();
			this->groupBoxAmplitude->ResumeLayout(false);
			this->groupBoxAmplitude->PerformLayout();
			this->ResumeLayout(false);
		}

	public:
		// Публичное свойство для доступа к значению амплитуды
		static property double AmplitudeVariation
		{
			double get() { return amplitudeVariation; }
			void set(double value) { amplitudeVariation = value; }
		}

		void button1_Click(System::Object^ sender, System::EventArgs^ e);
		void button2_Click(System::Object^ sender, System::EventArgs^ e);
		void button3_Click(System::Object^ sender, System::EventArgs^ e);
		void button4_Click(System::Object^ sender, System::EventArgs^ e);
		void button5_Click(System::Object^ sender, System::EventArgs^ e);
		void button6_Click(System::Object^ sender, System::EventArgs^ e);
		void trackBarAmplitude_Scroll(System::Object^ sender, System::EventArgs^ e);
		void BuildShipGraph();
		void BuildTrainGraph();
		void ClearGraphs();
		void PredictWithAR(int order, bool isShip);
		void PredictWithKalman(bool isShip, double Q, double R);
		void ShowErrorWithSKO(array<double>^ signal, array<double>^ prediction, String^ methodName, bool isShip);

	private:
		// Статическая переменная для хранения разброса амплитуды
		static double amplitudeVariation = 0.5;
	};
}