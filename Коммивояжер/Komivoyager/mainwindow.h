#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>    // библиотека необходимая для отрисовки графических объектов
#include<QMessageBox>  // библиотека для вывода сообщений в новом окне


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent*) override;   // метод рисующий графические объекты
private slots:
    void on_createNode_clicked();   //  метод, проверяющий введённое количество узлов и выполняющий их отрисовку

    void on_build_clicked();     //  метод, который строит связи между узлами

    void Find_min();   // метод для нахождения минимального элемента в строках и столбцах

    void Find_null(int i);   //  метод, заполняющий двумерный массив значениями из таблицы, выполняющий редукция строк и столбцов и оценку элементов

    void on_doWork_clicked();    // метод, выполняющий вычислительные операции, поиск оптимального пути

    void on_createNode_pressed();   //   метод, выполняющий операции при нажатии на кнопку createNode

    void on_createNode_released();  //  метод, выполняющий операции при отпусании кнопки  createNode

    void on_build_pressed();   //  метод, выполняющий операции при нажатии на кнопку build

    void on_build_released();   //  метод, выполняющий операции при отпускании кнопки build

    void on_doWork_pressed();   //  метод, выполняющий операции при нажатии на кнопку doWork

    void on_doWork_released();   //  метод, выполняющий операции при отпускании кнопки doWork

    void Clear();   // метод для очищения матрицы смежности
};
#endif // MAINWINDOW_H
