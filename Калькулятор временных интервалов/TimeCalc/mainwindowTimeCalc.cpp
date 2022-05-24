#include "mainwindowTimeCalc.h"
#include "ui_mainwindowTimeCalc.h"
#include<QString>
#include<QMessageBox> // подключение библиотеки QMessageBox для вывода сообщений в новом окне
bool f =false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushHour->hide();  //изначальное сокрытие некоторых кнопок
    ui->pushMinute->hide();
    ui->pushSeconds->hide();
    ui->lineEdit_8->hide(); // изначальное сокрытие поля ввода
    ui->label_9->hide();    //изначальное сокрытие строки с сообщением
    QPixmap map(":/img/img/wood61.jpg");   // подготовка изображения для установки на задний фон
    map=map.scaled(this->size(),Qt::IgnoreAspectRatio);  //установление размеров калькулятора соответствующих размерам изображения
    QPalette pal;
    pal.setBrush(QPalette::Window,map);  //установка изображения на задний фон
    this->setPalette(pal);
}
class Time
{

public:
    double hour;
    double min;
    double sec;
};
Time t1;
Time t2;
Time t3;

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{

    if(f==false){  // сокрытие полей ввода второго интервала и показывание новых кнопок при первом нажатии, обратное выполняется при повторном нажатии
    ui->label_9->show(); //показывание строки с сообщением
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_8->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->pushHour->show();  // показывание некоторых кнопок
    ui->pushMinute->show();
    ui->pushSeconds->show();
    ui->label->setText("Перевести в ");  //установка текста с сообщением
    ui->lineEdit_7->setText("");  //очещение поля "Результат"
    f=true;
    }
    else
    {
    ui->label_9->hide();
    ui->label->setText("");
    ui->lineEdit_4->show();
    ui->lineEdit_5->show();
    ui->lineEdit_6->show();
    ui->lineEdit_8->hide();
    ui->label_6->show();
    ui->label_7->show();
    ui->label_8->show();
    ui->pushHour->hide();
    ui->pushMinute->hide();
    ui->pushSeconds->hide();
    ui->lineEdit_7->setText("");
    f=false;
    }
}


void MainWindow::on_pushPlus_clicked() //установка в строку с сообщением знака "+"
{
    ui->label->setText("+");
    ui->label_6->show();
    ui->label_7->show();
    ui->label_8->show();
    ui->lineEdit_4->show();
    ui->lineEdit_5->show();
    ui->lineEdit_6->show();
    ui->lineEdit_8->hide();
    ui->lineEdit_7->setText("");
}

void MainWindow::on_pushMinus_clicked()  //установка в строку с сообщением знака "-"
{
    ui->label->setText("-");
    ui->label_6->show();
    ui->label_7->show();
    ui->label_8->show();
    ui->lineEdit_8->hide();
    ui->lineEdit_4->show();
    ui->lineEdit_5->show();
    ui->lineEdit_6->show();
    ui->lineEdit_7->setText("");
}

void MainWindow::on_pushMult_clicked()  //установка в строку с сообщением знака "*"
{
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label->setText("*");
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_8->show();
    ui->label->show();
    ui->lineEdit_7->setText("");
}

void MainWindow::on_pushDiv_clicked()  //установка в строку с сообщением знака "/"
{
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label->setText("/");
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_8->show();
    ui->label->show();
    ui->lineEdit_7->setText("");
}

void MainWindow::on_pushResult_clicked()
{
    if(ui->label->text()=="")
    {
        QMessageBox::warning(this,"Предупреждение","Выберите необходимую операцию!"); // вывод сообщения об ошибке, если не выбрана операция
    }

    QString res;

    //ниже показано приведение первого временного интервала к правильным временным интервалам

     t1.sec = t1.sec + ui->lineEdit_3->text().toDouble();
     if(t1.sec>59)
     {
         int c;
         c=t1.sec/60;
         t1.min+=c;
         t1.sec=t1.sec-c*60;

     }
     t1.min = t1.min + ui->lineEdit_2->text().toDouble();
     if(t1.min>59)
     {
         int c;
         c=t1.min/60;
         t1.hour+=c;
         t1.min=t1.min-c*60;

     }
     t1.hour = t1.hour + ui->lineEdit->text().toDouble();

     //ниже показано приведение второго временного интервала к правильным временным интервалам

     t2.sec = t2.sec + ui->lineEdit_6->text().toDouble();
     if(t2.sec>59)
     {
         int c;
         c=t2.sec/60;
         t2.min+=c;
         t2.sec=t2.sec-c*60;

     }
     t2.min = t2.min + ui->lineEdit_5->text().toDouble();
     if(t2.min>59)
     {
         int c;
         c=t2.min/60;
         t2.hour+=c;
         t2.min=t2.min-c*60;

     }
     t2.hour = t2.hour + ui->lineEdit_4->text().toDouble();


     // выполнение операций, если выбран знак "+"

    if(ui->label->text()=="+")
    {

       ui->pushHour->hide();
       ui->pushMinute->hide();
       ui->pushSeconds->hide();

         t3.sec= t1.sec + t2.sec;
         if(t3.sec>59)
         {
             int c;
             c=t3.sec/60;
             t3.min+=c;
             t3.sec=t3.sec-c*60;

         }

         t3.min= t1.min + t2.min;
         if(t3.min>59)
         {
             int c;
             c=t3.min/60;
             t3.hour+=c;
             t3.min=t3.min-c*60;

         }

         t3.hour= t1.hour + t2.hour;
         QString h3,m3,s3;
         h3 = QString::number(t3.hour);
         m3 = QString::number(t3.min);
         s3 = QString::number(t3.sec);
         res = h3 + " : " + m3 +" : " + s3;
        ui->lineEdit_7->setText(res);
        t1.sec = 0;
        t1.min = 0;
        t1.hour = 0;
        t2.sec = 0;
        t2.min = 0;
        t2.hour = 0;
    }

    else

    {
        // выполнение операций, если выбран знак "-"

        if(ui->label->text()=="-")
        {
            ui->pushHour->hide();
            ui->pushMinute->hide();
            ui->pushSeconds->hide();

            if(t1.sec<t2.sec)
            {
                t1.min-=1;
                t1.sec+=60;
            }
             t3.sec= t1.sec - t2.sec;
             if(t1.min<t2.min)
             {
                 t1.hour-=1;
                 t1.min+=60;
             }
             t3.min = t1.min-t2.min;

             t3.hour = t1.hour-t2.hour;
             QString h3,m3,s3;
             h3 = QString::number(t3.hour);
             m3 = QString::number(t3.min);
             s3 = QString::number(t3.sec);
             res = h3 + " : " + m3 +" : " + s3;
            ui->lineEdit_7->setText(res);
            t1.sec = 0;
            t1.min = 0;
            t1.hour = 0;
            t2.sec = 0;
            t2.min = 0;
            t2.hour = 0;
        }
        else
        {
            // выполнение операций, если выбран знак "*"

            if(ui->label->text()=="*")
            {
                ui->pushHour->hide();
                ui->pushMinute->hide();
                ui->pushSeconds->hide();
                t1.sec = t1.sec * ui->lineEdit_8->text().toDouble();
                t1.min = t1.min * ui->lineEdit_8->text().toDouble();
                t1.hour = t1.hour * ui->lineEdit_8->text().toDouble();

                if(t1.sec>59)
                {
                    int c;
                    c=t1.sec/60;
                    t1.min+=c;
                    t1.sec=t1.sec-c*60;

                }
                if(t1.min>59)
                {
                    int c;
                    c=t1.min/60;
                    t1.hour+=c;
                    t1.min=t1.min-c*60;

                }
                QString h3,m3,s3;
                h3 = QString::number(t1.hour);
                m3 = QString::number(t1.min);
                s3 = QString::number(t1.sec);
                res = h3 + " : " + m3 +" : " + s3;
               ui->lineEdit_7->setText(res);
               t1.hour=0;
               t1.min=0;
               t1.sec=0;
            }
            else
            {
                // выполнение операций, если выбран знак "/"

                if(ui->label->text()=="/")
                {
                    if(ui->lineEdit_8->text()=="0")
                    {
                        ui->lineEdit_7->setText("Нельзя делить на 0!");  //вывод сообщения об ошибке, если пользователь попробует поделить интервал на 0
                    }
                   else
                    {

                    ui->pushHour->hide();
                    ui->pushMinute->hide();
                    ui->pushSeconds->hide();
                    t1.sec = t1.sec / ui->lineEdit_8->text().toDouble();
                    t1.min = t1.min / ui->lineEdit_8->text().toDouble();
                    t1.hour = t1.hour / ui->lineEdit_8->text().toDouble();

                    if(t1.sec>59)
                    {
                        int c;
                        c=t1.sec/60;
                        t1.min+=c;
                        t1.sec=t1.sec-c*60;

                    }
                    if(t1.min>59)
                    {
                        int c;
                        c=t1.min/60;
                        t1.hour+=c;
                        t1.min=t1.min-c*60;

                    }
                    QString h3,m3,s3;
                    h3 = QString::number(t1.hour);
                    m3 = QString::number(t1.min);
                    s3 = QString::number(t1.sec);
                    res = h3 + " : " + m3 +" : " + s3;  // вывод временных интервалов через двоеточие
                   ui->lineEdit_7->setText(res);
                   t1.hour=0;
                   t1.min=0;
                   t1.sec=0;
                    }
                }
            }
        }

    }
}


void MainWindow::on_pushClear_clicked()  //очищение всех полей ввода
{
    if(f==false)
    {
    ui->label->setText("");
    }
    ui->label_9->setText("");
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");
    t1.hour=0;
    t1.min=0;
    t1.sec=0;
    t2.hour=0;
    t2.min=0;
    t2.sec=0;
    t3.hour=0;
    t3.min=0;
    t3.sec=0;
}



void MainWindow::on_pushHour_clicked()  // преобразование интервала в часы
{
   double h,m,s;
   QString hour;
   ui->label_9->setText("Часы");
   t1.sec = t1.sec + ui->lineEdit_3->text().toDouble();
   if(t1.sec>59)
   {
       int c;
       c=t1.sec/60;
       t1.min+=c;
       t1.sec=t1.sec-c*60;

   }
   t1.min = t1.min + ui->lineEdit_2->text().toDouble();
   if(t1.min>59)
   {
       int c;
       c=t1.min/60;
       t1.hour+=c;
       t1.min=t1.min-c*60;

   }
   t1.hour = t1.hour + ui->lineEdit->text().toDouble();

   s = t1.sec*(1/60.0);
   m = t1.min+s;
   h = m *(1/60.0);
   h =t1.hour+h;
   hour=QString::number(h);
   ui->lineEdit_7->setText(hour);
   t1.sec = 0;
   t1.min = 0;
   t1.hour = 0;
}


void MainWindow::on_pushMinute_clicked()   // преобразование интервала в минуты
{

    double h,m,s;
    QString minute;
    ui->label_9->setText("Минуты");
    t1.sec = t1.sec + ui->lineEdit_3->text().toDouble();
    if(t1.sec>59)
    {
        int c;
        c=t1.sec/60;
        t1.min+=c;
        t1.sec=t1.sec-c*60;

    }
    t1.min = t1.min + ui->lineEdit_2->text().toDouble();
    if(t1.min>59)
    {
        int c;
        c=t1.min/60;
        t1.hour+=c;
        t1.min=t1.min-c*60;

    }
    t1.hour = t1.hour + ui->lineEdit->text().toDouble();

    s = t1.sec*(1/60.0);
    h=t1.hour*60.0;
    m = t1.min+s+h;
    minute=QString::number(m);
    ui->lineEdit_7->setText(minute);
    t1.sec = 0;
    t1.min = 0;
    t1.hour = 0;
}



void MainWindow::on_pushSeconds_clicked()   // преобразование интервала в секунды
{
    double h,m,s;
    QString second;
    ui->label_9->setText("Секунды");
    t1.sec = t1.sec + ui->lineEdit_3->text().toDouble();
    if(t1.sec>59)
    {
        int c;
        c=t1.sec/60;
        t1.min+=c;
        t1.sec=t1.sec-c*60;

    }
    t1.min = t1.min + ui->lineEdit_2->text().toDouble();
    if(t1.min>59)
    {
        int c;
        c=t1.min/60;
        t1.hour+=c;
        t1.min=t1.min-c*60;

    }
    t1.hour = t1.hour + ui->lineEdit->text().toDouble();


    h=t1.hour*60.0;
    t1.min+=h;
    m = t1.min*60.0;
    s=m+t1.sec;
    second=QString::number(s);
    ui->lineEdit_7->setText(second);
    t1.sec = 0;
    t1.min = 0;
    t1.hour = 0;
}








void MainWindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("  color: white;  border-image: url(:/img/img/wood71.png) 3 10 3 10; border-top: 3px transparent; border-bottom: 3px transparent; border-right: 10px transparent;border-left: 10px transparent; border-style: outset;border-width: 2px;border-radius: 1px;");
}


void MainWindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet("  color: black;  border-image: url(:/img/img/wood71.png) 3 10 3 10; border-top: 3px transparent; border-bottom: 3px transparent; border-right: 10px transparent;border-left: 10px transparent; border-style: outset;border-width: 2px;border-radius: 1px;");
}


void MainWindow::on_pushClear_pressed()
{
    ui->pushClear->setStyleSheet("  color: white;  border-image: url(:/img/img/wood71.png) 3 10 3 10; border-top: 3px transparent; border-bottom: 3px transparent; border-right: 10px transparent;border-left: 10px transparent; border-style: outset;border-width: 2px;border-radius: 1px;");

}


void MainWindow::on_pushClear_released()
{
     ui->pushClear->setStyleSheet("  color: black;  border-image: url(:/img/img/wood71.png) 3 10 3 10; border-top: 3px transparent; border-bottom: 3px transparent; border-right: 10px transparent;border-left: 10px transparent; border-style: outset;border-width: 2px;border-radius: 1px;");
}


void MainWindow::on_pushResult_pressed()
{
    ui->pushResult->setStyleSheet("  color: white;  border-image: url(:/img/img/wood71.png) 3 10 3 10; border-top: 3px transparent; border-bottom: 3px transparent; border-right: 10px transparent;border-left: 10px transparent; border-style: outset;border-width: 2px;border-radius: 1px;");
}


void MainWindow::on_pushResult_released()
{
     ui->pushResult->setStyleSheet("  color: black;  border-image: url(:/img/img/wood71.png) 3 10 3 10; border-top: 3px transparent; border-bottom: 3px transparent; border-right: 10px transparent;border-left: 10px transparent; border-style: outset;border-width: 2px;border-radius: 1px;");
}

