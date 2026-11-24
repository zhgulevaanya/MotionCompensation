#include "MyForm.h"
#define _USE_MATH_DEFINES
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <math.h>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <cliext/vector>

using namespace cliext;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Collections::Generic;

[STAThread]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Motioncompensation::MyForm^ form = gcnew Motioncompensation::MyForm();
    Application::Run(form);
    return 0;
}

// Глобальный класс для генерации случайных чисел
public ref class GlobalData
{
public:
    static Random^ rand = gcnew Random();
};

// Глобальные флаги для сброса статических переменных
static bool resetShipModel = false;
static bool resetTrainModel = false;

// Функция для сброса модели корабля
void ResetShipModel()
{
    resetShipModel = true;
}

// Функция для сброса модели поезда
void ResetTrainModel()
{
    resetTrainModel = true;
}

// Модель движения корабля
double ShipModel(double t)
{
    static bool initialized = false;
    static std::vector<double> time_points;
    static std::vector<double> amplitude_points;
    static double w0_random = 0.0;
    static double phi_random = 0.0;

    if (!initialized || resetShipModel)
    {
        time_points.clear();
        amplitude_points.clear();

        w0_random = 0.2 + GlobalData::rand->NextDouble() * 0.8;
        phi_random = GlobalData::rand->NextDouble() * 2 * Math::PI;

        double baseAmplitude = 10.0;
        double variation = Motioncompensation::MyForm::AmplitudeVariation;

        int num_points = 15 + GlobalData::rand->Next() % 20;
        for (int i = 0; i <= num_points; i++)
        {
            double time = (double)i / num_points * 100.0;
            double amplitude;

            if (variation < 0.01)
            {
                amplitude = baseAmplitude + (GlobalData::rand->NextDouble() - 0.5) * 0.2;
            }
            else
            {
                double minAmp = baseAmplitude * (1.0 - variation * 0.9);
                double maxAmp = baseAmplitude * (1.0 + variation * 0.9);
                amplitude = minAmp + GlobalData::rand->NextDouble() * (maxAmp - minAmp);
            }

            time_points.push_back(time);
            amplitude_points.push_back(amplitude);
        }
        initialized = true;
        resetShipModel = false;
    }

    double A_t = 0.0;
    for (int i = 0; i < time_points.size() - 1; i++)
    {
        if (t >= time_points[i] && t <= time_points[i + 1])
        {
            double ratio = (t - time_points[i]) / (time_points[i + 1] - time_points[i]);
            A_t = amplitude_points[i] * (1.0 - ratio) + amplitude_points[i + 1] * ratio;
            break;
        }
    }
    if (t > time_points[time_points.size() - 1])
        A_t = amplitude_points[amplitude_points.size() - 1];

    double oscillation = A_t * Math::Sin(w0_random * t + phi_random);
    double noise = 0.0;
    for (int i = 1; i <= 20; i++)
    {
        double freq = i * 0.2;
        double amplitude = (A_t / 10.0) * 0.2 / (freq * freq);
        double phase = GlobalData::rand->NextDouble() * 2 * Math::PI;
        noise += amplitude * Math::Sin(2 * Math::PI * freq * t + phase);
    }
    return oscillation + noise;
}

// Импульсная составляющая для поезда
double TrainImpulses(double t)
{
    double result = 0.0;
    double L = 25.0;
    double V = 20.0;
    double w = 0.1;
    double t_st = L / V;
    int impuls = static_cast<int>(t / t_st) + 3;
    for (int i = 0; i <= impuls; i++)
    {
        double Ti = i * t_st;
        double Ai = 2.0 * (1.0 + 0.5 * Math::Sin(i * 0.5));
        double exponent = -Math::Pow((t - Ti) / w, 2);
        if (Math::Abs(t - Ti) < 0.5)
            result += Ai * Math::Exp(exponent);
    }
    return result;
}

// Модель движения поезда
double TrainModel(double t)
{
    static bool initialized = false;
    static std::vector<double> time_points;
    static std::vector<double> amplitude_points;

    if (!initialized || resetTrainModel)
    {
        time_points.clear();
        amplitude_points.clear();

        double baseAmplitude = 7.0;
        double variation = Motioncompensation::MyForm::AmplitudeVariation;

        int num_points = 10 + GlobalData::rand->Next() % 15;
        for (int i = 0; i <= num_points; i++)
        {
            double time = (double)i / num_points * 50.0;
            double amplitude;

            if (variation < 0.01)
            {
                amplitude = baseAmplitude + (GlobalData::rand->NextDouble() - 0.5) * 0.2;
            }
            else
            {
                double minAmp = baseAmplitude * (1.0 - variation * 0.9);
                double maxAmp = baseAmplitude * (1.0 + variation * 0.9);
                amplitude = minAmp + GlobalData::rand->NextDouble() * (maxAmp - minAmp);
            }

            time_points.push_back(time);
            amplitude_points.push_back(amplitude);
        }
        initialized = true;
        resetTrainModel = false;
    }

    double A_variable = 0.0;
    for (int i = 0; i < time_points.size() - 1; i++)
    {
        if (t >= time_points[i] && t <= time_points[i + 1])
        {
            double ratio = (t - time_points[i]) / (time_points[i + 1] - time_points[i]);
            A_variable = amplitude_points[i] * (1.0 - ratio) + amplitude_points[i + 1] * ratio;
            break;
        }
    }
    if (t > time_points[time_points.size() - 1])
        A_variable = amplitude_points[amplitude_points.size() - 1];

    double f = 0.1;
    double main_oscillation = A_variable * Math::Sin(2 * Math::PI * f * t);
    double noise = (A_variable * 0.1) * (2.0 * GlobalData::rand->NextDouble() - 1.0);
    double impulses = TrainImpulses(t) * (A_variable / 5.0);
    return main_oscillation + noise + impulses;
}

// Расчет AR коэффициентов
array<double>^ CalculateARCoefficients(array<double>^ signal, int order)
{
    int n = signal->Length;
    array<double>^ a = gcnew array<double>(order);
    if (n <= order)
    {
        for (int i = 0; i < order; i++) a[i] = 0.0;
        return a;
    }

    array<double>^ r = gcnew array<double>(order + 1);
    double mean = 0.0;
    for (int i = 0; i < n; i++) mean += signal[i];
    mean /= n;

    array<double>^ centered = gcnew array<double>(n);
    for (int i = 0; i < n; i++) centered[i] = signal[i] - mean;

    for (int k = 0; k <= order; k++)
    {
        double sum = 0.0;
        for (int i = 0; i < n - k; i++)
            sum += centered[i] * centered[i + k];
        r[k] = sum / n;
    }

    array<double>^ a_prev = gcnew array<double>(order);
    array<double>^ a_curr = gcnew array<double>(order);
    double kappa = 0.0;
    double sigma = r[0];

    for (int i = 1; i <= order; i++)
    {
        kappa = r[i];
        for (int j = 1; j < i; j++)
            kappa -= a_prev[j - 1] * r[i - j];
        kappa /= sigma;

        a_curr[i - 1] = kappa;
        for (int j = 1; j < i; j++)
            a_curr[j - 1] = a_prev[j - 1] - kappa * a_prev[i - j - 1];

        sigma = sigma * (1.0 - kappa * kappa);
        for (int j = 0; j < i; j++)
            a_prev[j] = a_curr[j];
    }
    return a_curr;
}

// Функция для показа ошибки и СКО
void Motioncompensation::MyForm::ShowErrorWithSKO(array<double>^ signal, array<double>^ prediction, String^ methodName, bool isShip)
{
    int n = Math::Min(signal->Length, prediction->Length);

    double sumSquared = 0.0;
    for (int i = 0; i < n; i++)
    {
        double error = signal[i] - prediction[i];
        sumSquared += error * error;
    }
    double sko = Math::Sqrt(sumSquared / n);

    double maxError = 0.0;
    for (int i = 0; i < n; i++)
    {
        double error = Math::Abs(signal[i] - prediction[i]);
        if (error > maxError) maxError = error;
    }

    Form^ errorForm = gcnew Form();
    errorForm->Text = String::Format("Ошибка предсказания - {0}", methodName);
    errorForm->Size = System::Drawing::Size(500, 400);
    errorForm->StartPosition = FormStartPosition::CenterScreen;

    Panel^ infoPanel = gcnew Panel();
    infoPanel->Dock = DockStyle::Top;
    infoPanel->Height = 80;
    infoPanel->BackColor = System::Drawing::Color::LightYellow;

    Label^ skoLabel = gcnew Label();
    skoLabel->Text = String::Format("СКО: {0:F4}", sko);
    skoLabel->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
    skoLabel->Location = System::Drawing::Point(10, 10);
    skoLabel->Size = System::Drawing::Size(400, 30);

    Label^ maxErrorLabel = gcnew Label();
    maxErrorLabel->Text = String::Format("Максимальная ошибка: {0:F4}", maxError);
    maxErrorLabel->Font = gcnew System::Drawing::Font("Arial", 10);
    maxErrorLabel->Location = System::Drawing::Point(10, 45);
    maxErrorLabel->Size = System::Drawing::Size(400, 25);

    infoPanel->Controls->Add(skoLabel);
    infoPanel->Controls->Add(maxErrorLabel);

    System::Windows::Forms::DataVisualization::Charting::Chart^ errorChart =
        gcnew System::Windows::Forms::DataVisualization::Charting::Chart();
    errorChart->Dock = DockStyle::Fill;

    System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea =
        gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea();
    errorChart->ChartAreas->Add(chartArea);

    System::Windows::Forms::DataVisualization::Charting::Series^ errorSeries =
        gcnew System::Windows::Forms::DataVisualization::Charting::Series();
    errorSeries->Name = "Error";
    errorSeries->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
    errorSeries->BorderWidth = 2;
    errorSeries->Color = System::Drawing::Color::Red;
    errorChart->Series->Add(errorSeries);

    System::Windows::Forms::DataVisualization::Charting::Series^ zeroLine =
        gcnew System::Windows::Forms::DataVisualization::Charting::Series();
    zeroLine->Name = "Zero";
    zeroLine->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
    zeroLine->BorderWidth = 1;
    zeroLine->Color = System::Drawing::Color::Gray;
    zeroLine->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
    errorChart->Series->Add(zeroLine);

    for (int i = 0; i < n; i++)
    {
        double error = signal[i] - prediction[i];
        errorSeries->Points->AddXY(i, error);
        zeroLine->Points->AddXY(i, 0);
    }

    chartArea->AxisX->Title = "Номер отсчета";
    chartArea->AxisY->Title = "Ошибка";
    chartArea->AxisY->TitleFont = gcnew System::Drawing::Font("Arial", 10);
    chartArea->AxisX->TitleFont = gcnew System::Drawing::Font("Arial", 10);

    errorChart->Titles->Add("График ошибки предсказания");

    Panel^ mainPanel = gcnew Panel();
    mainPanel->Dock = DockStyle::Fill;
    mainPanel->Controls->Add(errorChart);
    mainPanel->Controls->Add(infoPanel);

    errorForm->Controls->Add(mainPanel);
    errorForm->ShowDialog();
}

// AR предсказание
void Motioncompensation::MyForm::PredictWithAR(int order, bool isShip)
{
    array<double>^ signal;
    System::Windows::Forms::DataVisualization::Charting::Chart^ targetChart;
    double t_start, t_end, step;

    if (isShip)
    {
        targetChart = chart1;
        t_start = 0.0; t_end = 100.0; step = 0.1;
        List<double>^ tempList = gcnew List<double>();
        for (double t = t_start; t <= t_end; t += step)
            tempList->Add(ShipModel(t));
        signal = tempList->ToArray();
    }
    else
    {
        targetChart = chart2;
        t_start = 0.0; t_end = 50.0; step = 0.05;
        List<double>^ tempList = gcnew List<double>();
        for (double t = t_start; t <= t_end; t += step)
            tempList->Add(TrainModel(t));
        signal = tempList->ToArray();
    }

    array<double>^ coefficients = CalculateARCoefficients(signal, order);

    String^ predictSeriesName = "AR_Predictions";
    if (targetChart->Series->IndexOf(predictSeriesName) == -1)
    {
        targetChart->Series->Add(predictSeriesName);
        targetChart->Series[predictSeriesName]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
        targetChart->Series[predictSeriesName]->BorderWidth = 2;
        targetChart->Series[predictSeriesName]->Color = System::Drawing::Color::Green;
    }
    else
        targetChart->Series[predictSeriesName]->Points->Clear();

    int n = signal->Length;
    array<double>^ predictions = gcnew array<double>(n);
    double currentTime = t_start;

    for (int i = 0; i < n; i++)
    {
        double prediction = 0.0;
        for (int j = 0; j < order; j++)
        {
            int index = i - j - 1;
            if (index >= 0)
                prediction += coefficients[j] * signal[index];
        }
        predictions[i] = prediction;
        currentTime = t_start + i * step;
        targetChart->Series[predictSeriesName]->Points->AddXY(currentTime, prediction);
    }

    targetChart->Titles->Clear();
    String^ titleText = isShip ?
        String::Format("Корабль (AR предсказание, порядок={0})", order) :
        String::Format("Поезд (AR предсказание, порядок={0})", order);
    targetChart->Titles->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Title(titleText));

    if (targetChart->Legends->Count == 0)
        targetChart->Legends->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
    targetChart->Series["Series1"]->LegendText = "Реальный сигнал";
    targetChart->Series[predictSeriesName]->LegendText = String::Format("AR (порядок {0})", order);

    ShowErrorWithSKO(signal, predictions, String::Format("AR модель (порядок {0})", order), isShip);
}

// Калман предсказание
void Motioncompensation::MyForm::PredictWithKalman(bool isShip, double Q, double R)
{
    array<double>^ signal;
    System::Windows::Forms::DataVisualization::Charting::Chart^ targetChart;
    double t_start, t_end, step;

    if (isShip)
    {
        targetChart = chart1;
        t_start = 0.0; t_end = 100.0; step = 0.1;
        List<double>^ tempList = gcnew List<double>();
        for (double t = t_start; t <= t_end; t += step)
            tempList->Add(ShipModel(t));
        signal = tempList->ToArray();
    }
    else
    {
        targetChart = chart2;
        t_start = 0.0; t_end = 50.0; step = 0.05;
        List<double>^ tempList = gcnew List<double>();
        for (double t = t_start; t <= t_end; t += step)
            tempList->Add(TrainModel(t));
        signal = tempList->ToArray();
    }

    String^ kalmanSeriesName = "Kalman_Predictions";
    if (targetChart->Series->IndexOf(kalmanSeriesName) == -1)
    {
        targetChart->Series->Add(kalmanSeriesName);
        targetChart->Series[kalmanSeriesName]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
        targetChart->Series[kalmanSeriesName]->BorderWidth = 2;
        targetChart->Series[kalmanSeriesName]->Color = System::Drawing::Color::Orange;
    }
    else
        targetChart->Series[kalmanSeriesName]->Points->Clear();

    double A[2][2] = { {1.0, step}, {0.0, 1.0} };
    double H[1][2] = { {1.0, 0.0} };
    double x[2] = { signal[0], 0.0 };
    double P[2][2] = { {Q, 0.0}, {0.0, Q} };
    double Q_matrix[2][2] = { {Q, 0.0}, {0.0, Q} };
    double R_matrix[1][1] = { {R} };

    int n = signal->Length;
    array<double>^ filtered = gcnew array<double>(n);
    double currentTime = t_start;

    for (int i = 0; i < n; i++)
    {
        double measurement = signal[i];

        double x_pred[2];
        x_pred[0] = A[0][0] * x[0] + A[0][1] * x[1];
        x_pred[1] = A[1][0] * x[0] + A[1][1] * x[1];

        double P_pred[2][2];
        P_pred[0][0] = A[0][0] * P[0][0] * A[0][0] + A[0][0] * P[0][1] * A[0][1] +
            A[0][1] * P[1][0] * A[0][0] + A[0][1] * P[1][1] * A[0][1] + Q_matrix[0][0];
        P_pred[0][1] = A[0][0] * P[0][0] * A[1][0] + A[0][0] * P[0][1] * A[1][1] +
            A[0][1] * P[1][0] * A[1][0] + A[0][1] * P[1][1] * A[1][1] + Q_matrix[0][1];
        P_pred[1][0] = A[1][0] * P[0][0] * A[0][0] + A[1][0] * P[0][1] * A[0][1] +
            A[1][1] * P[1][0] * A[0][0] + A[1][1] * P[1][1] * A[0][1] + Q_matrix[1][0];
        P_pred[1][1] = A[1][0] * P[0][0] * A[1][0] + A[1][0] * P[0][1] * A[1][1] +
            A[1][1] * P[1][0] * A[1][0] + A[1][1] * P[1][1] * A[1][1] + Q_matrix[1][1];

        double S = H[0][0] * P_pred[0][0] * H[0][0] + H[0][0] * P_pred[0][1] * H[0][0] +
            H[0][0] * P_pred[1][0] * H[0][0] + H[0][0] * P_pred[1][1] * H[0][0] + R_matrix[0][0];

        double K[2][1];
        K[0][0] = (P_pred[0][0] * H[0][0] + P_pred[0][1] * H[0][0]) / S;
        K[1][0] = (P_pred[1][0] * H[0][0] + P_pred[1][1] * H[0][0]) / S;

        double innovation = measurement - (H[0][0] * x_pred[0] + H[0][1] * x_pred[1]);
        x[0] = x_pred[0] + K[0][0] * innovation;
        x[1] = x_pred[1] + K[1][0] * innovation;

        double I_KH[2][2];
        I_KH[0][0] = 1.0 - K[0][0] * H[0][0];
        I_KH[0][1] = 0.0 - K[0][0] * H[0][1];
        I_KH[1][0] = 0.0 - K[1][0] * H[0][0];
        I_KH[1][1] = 1.0 - K[1][0] * H[0][1];

        P[0][0] = I_KH[0][0] * P_pred[0][0] + I_KH[0][1] * P_pred[1][0];
        P[0][1] = I_KH[0][0] * P_pred[0][1] + I_KH[0][1] * P_pred[1][1];
        P[1][0] = I_KH[1][0] * P_pred[0][0] + I_KH[1][1] * P_pred[1][0];
        P[1][1] = I_KH[1][0] * P_pred[0][1] + I_KH[1][1] * P_pred[1][1];

        filtered[i] = x[0];
        currentTime = t_start + i * step;
        targetChart->Series[kalmanSeriesName]->Points->AddXY(currentTime, x[0]);
    }

    targetChart->Titles->Clear();
    String^ titleText = isShip ?
        String::Format("Корабль (Калман, Q={0:F0}, R={1:F0})", Q, R) :
        String::Format("Поезд (Калман, Q={0:F0}, R={1:F0})", Q, R);
    targetChart->Titles->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Title(titleText));

    if (targetChart->Legends->Count == 0)
        targetChart->Legends->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
    targetChart->Series["Series1"]->LegendText = "Реальный сигнал";
    targetChart->Series[kalmanSeriesName]->LegendText = String::Format("Калман (Q={0:F0}, R={1:F0})", Q, R);

    ShowErrorWithSKO(signal, filtered, String::Format("Фильтр Калмана (Q={0:F0}, R={1:F0})", Q, R), isShip);
}

// Построение графика корабля
void Motioncompensation::MyForm::BuildShipGraph()
{
    // Сбрасываем статические переменные модели
    ResetShipModel();

    chart1->Series["Series1"]->Points->Clear();
    if (chart1->Series->IndexOf("AR_Predictions") != -1)
        chart1->Series["AR_Predictions"]->Points->Clear();
    if (chart1->Series->IndexOf("Kalman_Predictions") != -1)
        chart1->Series["Kalman_Predictions"]->Points->Clear();

    for (double t = 0.0; t <= 100.0; t += 0.1)
        chart1->Series["Series1"]->Points->AddXY(t, ShipModel(t));

    chart1->Titles->Clear();
    chart1->Titles->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Title("Модель движения корабля"));
    if (chart1->Legends->Count > 0) chart1->Legends->Clear();
    chart1->Series["Series1"]->LegendText = "Реальный сигнал";
}

// Построение графика поезда
void Motioncompensation::MyForm::BuildTrainGraph()
{
    // Сбрасываем статические переменные модели
    ResetTrainModel();

    chart2->Series["Series1"]->Points->Clear();
    if (chart2->Series->IndexOf("AR_Predictions") != -1)
        chart2->Series["AR_Predictions"]->Points->Clear();
    if (chart2->Series->IndexOf("Kalman_Predictions") != -1)
        chart2->Series["Kalman_Predictions"]->Points->Clear();

    for (double t = 0.0; t <= 50.0; t += 0.05)
        chart2->Series["Series1"]->Points->AddXY(t, TrainModel(t));

    chart2->Titles->Clear();
    chart2->Titles->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Title("Модель движения поезда"));
    if (chart2->Legends->Count > 0) chart2->Legends->Clear();
    chart2->Series["Series1"]->LegendText = "Реальный сигнал";
}

// Очистка графиков
void Motioncompensation::MyForm::ClearGraphs()
{
    chart1->Series["Series1"]->Points->Clear();
    chart2->Series["Series1"]->Points->Clear();
    if (chart1->Series->IndexOf("AR_Predictions") != -1)
        chart1->Series["AR_Predictions"]->Points->Clear();
    if (chart1->Series->IndexOf("Kalman_Predictions") != -1)
        chart1->Series["Kalman_Predictions"]->Points->Clear();
    if (chart2->Series->IndexOf("AR_Predictions") != -1)
        chart2->Series["AR_Predictions"]->Points->Clear();
    if (chart2->Series->IndexOf("Kalman_Predictions") != -1)
        chart2->Series["Kalman_Predictions"]->Points->Clear();

    chart1->Titles->Clear();
    chart1->Titles->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Title("Модель движения корабля"));
    chart2->Titles->Clear();
    chart2->Titles->Add(gcnew System::Windows::Forms::DataVisualization::Charting::Title("Модель движения поезда"));

    if (chart1->Legends->Count > 0) chart1->Legends->Clear();
    if (chart2->Legends->Count > 0) chart2->Legends->Clear();
}

// Обработчик ползунка амплитуды
void Motioncompensation::MyForm::trackBarAmplitude_Scroll(System::Object^ sender, System::EventArgs^ e)
{
    AmplitudeVariation = (double)trackBarAmplitude->Value / 100.0;
    labelAmplitudeValue->Text = String::Format("Разброс: {0:F0}%", AmplitudeVariation * 100);
}

// Обработчики кнопок
void Motioncompensation::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    // Автоматически сбрасываем модели перед построением
    BuildShipGraph();
    BuildTrainGraph();
}

void Motioncompensation::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
    ClearGraphs();
}

void Motioncompensation::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
    int order = Convert::ToInt32(numericOrderShip->Value);
    PredictWithAR(order, true);
}

void Motioncompensation::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
    int order = Convert::ToInt32(numericOrderTrain->Value);
    PredictWithAR(order, false);
}

void Motioncompensation::MyForm::button5_Click(System::Object^ sender, System::EventArgs^ e)
{
    double Q = Convert::ToDouble(numericKalmanQ->Value);
    double R = Convert::ToDouble(numericKalmanR->Value);
    PredictWithKalman(true, Q, R);
}

void Motioncompensation::MyForm::button6_Click(System::Object^ sender, System::EventArgs^ e)
{
    double Q = Convert::ToDouble(numericKalmanQ->Value);
    double R = Convert::ToDouble(numericKalmanR->Value);
    PredictWithKalman(false, Q, R);
}