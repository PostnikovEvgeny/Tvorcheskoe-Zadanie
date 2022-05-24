#ifndef MAINWINDOWTIMECALC_H
#define MAINWINDOWTIMECALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();  // метод, выполняющий операции при нажатии на кнопку "Преобразование интервала"

    void on_pushPlus_clicked();   // метод, выполняющий операции при нажатии на кнопку "+"

    void on_pushMinus_clicked();   // метод, выполняющий операции при нажатии на кнопку "-"

    void on_pushResult_clicked();  // метод, выполняющий операции при нажатии на кнопку "Вычислить"

    void on_pushClear_clicked();  // метод, выполняющий операции при нажатии на кнопку "Очистить"

    void on_pushHour_clicked();  // метод, выполняющий операции при нажатии на кнопку "Часы"

    void on_pushMinute_clicked();  // метод, выполняющий операции при нажатии на кнопку "Минуты"

    void on_pushSeconds_clicked(); // метод, выполняющий операции при нажатии на кнопку "Секунды"

    void on_pushMult_clicked(); // метод, выполняющий операции при нажатии на кнопку "*"

    void on_pushDiv_clicked();  // метод, выполняющий операции при нажатии на кнопку "/"

    void on_pushButton_pressed();  // метод, устанавливающий стиль при нажатии на кнопку "Преобразование интервала"

    void on_pushButton_released();  // метод, устанавливающий стиль при отпускании кнопки "Преобразование интервала"

    void on_pushClear_pressed();  // метод, устанавливающий стиль при нажатии на кнопку "Очистить"

    void on_pushClear_released();  // метод, устанавливающий стиль при отпускании кнопки "Очистить"

    void on_pushResult_pressed();  // метод, устанавливающий стиль при нажатии на кнопку "Вычислить"

    void on_pushResult_released();  // метод, устанавливающий стиль при отпускании кнопки "Вычислить"

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOWTIMECALC_H
