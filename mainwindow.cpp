#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
int count,increm,xcenter,ycenter;
double gradus = 360;
int mid_arg,mid_func;
int ways[9][9];
int way[9];
int str_min[9],clm_min[9];
int t=0;
int optimal[9][2];


class Node
{
public:
    int x,y;
};
Node *uzel;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->doWork->hide(); // изначальное скрытие необходимых кнопок с помощью метода hide()
    ui->build->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
  if(t)
   {
    int  otstup;
    gradus/=count;
    increm=gradus;
    gradus=0;
   QPainter painter;  //создание объекта класса QPainter, который будет отрисовывать узлы, линии между ними, фон и цвет объектов
   QPen pen;   // объект класса QPen отрисовывает линии
   QBrush brush;  // объект класса QBrush устанавливает заливку для узлов
   QString str;
   QFont font;  // объект класса QFont устанавливает размер для номера узла
   pen.setColor(Qt::black);  // установка цвета линии
   pen.setWidth(5);   // установка ширины линии окружности
   pen.setStyle(Qt::SolidLine);  // установка стиля линии окружности
   font.setPointSize(17);   //установка размера шрифта для названия узла
   brush.setStyle(Qt::SolidPattern); //установка стиля заливки узла
   brush.setColor(Qt::blue);  // установка цвета заливки узла
   painter.begin(this);  //необходимый метод begin() для начала отрисовки объектов
   painter.setPen(pen);  //установка линий окружности
   painter.setFont(font);  //установка шрифта
   painter.setBrush(brush);  //установка заливки
   for(int i=0;i<count;i++)
   {
      otstup=-10;
      if(gradus>180) otstup = 130;
      str=QString::number(i+1);
       uzel[i].x=xcenter+(150*cos(gradus/57));  // определение координаты x для узла
       uzel[i].y=ycenter+(150*-sin(gradus/57));  // определение координаты y для узла
       painter.drawEllipse(uzel[i].x,uzel[i].y,90,90);  // отрисовки узла
      painter.drawText(uzel[i].x+48,uzel[i].y+otstup,str);  // установка текста(номера узла)
      gradus+=increm;
   }
   if(t>1)
   {
       for(int i=0;i<count;i++)
       {
           for(int j=0;j<count;j++)
           {
               if(ways[i][j]<1000 && ways[i][j]>0)
               {
                   pen.setStyle(Qt::SolidLine);  //установка стиля линии
                   pen.setWidth(3);  // установка ширины линии
                   painter.setPen(pen); //установка линии
                   painter.drawLine(uzel[i].x+50,uzel[i].y+50,uzel[j].x+50,uzel[j].y+50);  // отрисовка линии

               }
           }
       }
   }
   if(t==3)
   {
       pen.setStyle(Qt::SolidLine);
       pen.setWidth(5);
       pen.setColor(Qt::green);  //установка цвета линии
       painter.setPen(pen);
       for(int i=1;i<count+1;i++)
       {
           painter.drawLine(uzel[way[i-1]].x+50,uzel[way[i-1]].y+50,uzel[way[i]].x+50,uzel[way[i]].y+50);
       }
   }

   painter.end();  // необходимый метод end() для прекращения отрисовки
  }
}


void MainWindow:: Clear()
{
    QString str;
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<10;j++)
        {
            str="l"+QString::number(i) + QString::number(j);  //присваивание переменной str номер поля ввода
            if(i != j)
           {

               this->findChild<QLineEdit*>(str)->setText("");  // нахождение нужного поля ввода и его очищение
           }
        }
    }
}


void MainWindow::on_createNode_clicked()
{
    Clear();
    if(ui->quantitylabel->text().toInt()<3||ui->quantitylabel->text().toInt()>9)
    {
        ui->quantitylabel->setText("");  // очищение поля ввода, в котором записывается количество узлов
        t = 0;
        this->repaint();    //вызов метода repaint() для активирования функции paintEvent и начала отрисовки объектов
        ui->doWork->hide();
        ui->build->hide();
        QMessageBox::warning(this,"Предупрежение","Количество городов должно быть не менее 3 и не более 9");  // вывод окна с предупреждением о неверном введённом значении

    }
    else
    {
        ui->doWork->show();  //показывание необходимых кнопок с помощью метода show()
        ui->build->show();
        count=ui->quantitylabel->text().toInt();  //переменная типа string приводится к типу int
        uzel = new Node[count];   //создание массива узлов
        xcenter = 800;    // установка изначальных координат первого узла
        ycenter = 300;
        t=1;
        this->repaint();
    }
}



void MainWindow::on_build_clicked()
{
    QString searcher,buffer;
    for(int i=0;i<count;i++)  // присваивание элементам массива значения из таблицы смежности
    {
        for(int j=0;j<count;j++)
        {
            if(i != j){
            searcher ="l"+QString::number(i+1) + QString::number(j+1);
            buffer = this->findChild<QLineEdit*>(searcher)->text();
            if(!buffer.length())
            {
                buffer = QString::number(INT32_MAX); //установление максимального значения переменной buffer
            }
            ways[i][j] = buffer.toInt();
            }
            if(i == j)
            {
                ways[i][j] = -1;
            }
        }
    }
t=2;
this->repaint();
}


void MainWindow::Find_null(int num)
{
    int min_in_str=INT32_MAX;
    int min_in_clm=INT32_MAX;
    int max_rank_null =0;
    int max_i=100,max_j=100;

    for(int i=0;i<count;i++) // поиск и оценка нулевых элементов
    {
        for(int j=0;j<count;j++)
        {
            if(ways[i][j]==0 && i!=j)
            {
                for(int k=0;k<count;k++)
                {
                    if(ways[k][j]>-1 && ways[k][j] < min_in_clm && k!=j && k!=i)
                    {
                        min_in_clm=ways[k][j];
                    }
                    if(ways[i][k]>-1 && ways[i][k]<min_in_str && i!=k && k!=j)
                    {
                        min_in_str=ways[i][k];
                    }
                }
                if(min_in_str>1000)
                    min_in_str=0;
                if(min_in_clm>1000)
                    min_in_clm=0;
                if(min_in_str>-1 && min_in_clm >-1 && i!=j && max_rank_null <= (min_in_str+min_in_clm))
                {
                    max_rank_null = min_in_str + min_in_clm;
                    max_i=i;
                    max_j=j;
                }
            }
        }
    }
    optimal[num][0]=max_i;
    optimal[num][1]=max_j;

    for(int z=0;z<count;z++)  // элементы, имеющие высокую оценку и находящиеся на строке и столбце нулегого элемента превращаются в -1
    {
        ways[max_i][z]=-1;
        ways[z][max_j]=-1;
    }
    ways[max_j][max_i]=-1;

}

void MainWindow::Find_min()
{
    for(int i=0;i<count;i++)
    {
        str_min[i]=INT32_MAX;
        clm_min[i]=INT32_MAX;
    }
    for(int i=0;i<count;i++)  //редукция строк
    {
        for(int j=0;j<count;j++)
        {
            if(i!=j && ways[i][j]>-1 && ways[i][j]<str_min[i])
            {
                str_min[i]=ways[i][j];
            }
        }
                for(int j=0;j<count;j++)
                {
                    if(i!=j && str_min[i]>0 && str_min[i]<1000)
                    {
                        ways[i][j] -= str_min[i];
                    }
                }
       }
    for(int j=0;j<count;j++)  //редукция столбцов
    {
        for(int i=0;i<count;i++)
        {
            if(i!=j && ways[i][j]>-1 && ways[i][j]<clm_min[j])
            {
                clm_min[j]=ways[i][j];
            }
        }
        for(int i=0;i<count;i++)
        {
            if(i!=j && clm_min[j]>0 && clm_min[j]<1000)
            {
                ways[i][j] -= clm_min[j];
            }
        }
    }
}


void MainWindow::on_doWork_clicked()
        {
           QString searcher,buffer;
           QString dialog;
           for(int i=0;i<count;i++)
           {
               Find_min();
               Find_null(i);
           }
           for(int i=0;i<count;i++) // инициализация массива после его изменения
           {
               for(int j=0;j<count;j++)
               {
                   if(i != j)
                   {
                       searcher = "l"+QString::number(i+1) + QString::number(j+1);
                       buffer = this->findChild<QLineEdit*>(searcher)->text();
                       if(!buffer.length())
                       {
                           buffer = QString::number(INT32_MAX);
                       }
                           ways[i][j] = buffer.toInt();
                   }
                   else
                   {
                       ways[i][j]=-1;
                   }
               }
           }
           dialog += "\nОптимальный путь: " + QString::number(optimal[0][0]+1) + " -> " + QString::number(optimal[0][1] + 1); // нахождение оптимального пути и вывод его в новое окно
           int point = optimal[0][1], summ = ways[optimal[0][0]][optimal[0][1]];

           way[0] = optimal[0][0];
           way[1] = optimal[0][1];
           int c = 1;
           while( c < count)
           {
               for(int i=1;i<count;i++)
               {
                   if(optimal[i][0] == point && optimal[i][0]!=optimal[i][1])
                   {
                       way[c+1] = point = optimal[i][1];
                       dialog += " -> " + QString::number(optimal[i][1]+1);
                       summ += ways[optimal[i][0]][optimal[i][1]];
                       optimal[i][0] = -1;
                       optimal[i][1] = -1;
                       break;
                   }
               }
               c++;
           }
           t=3;
           this->repaint();
           dialog += "\nПродолжительность: "+QString::number(summ);
           QMessageBox::information(this,"Результат",dialog);

        }

void MainWindow::on_createNode_pressed() //ниже представлены методы, меняющие стили для соответствующих кнопок
{
    ui->createNode->setStyleSheet("color: rgb(100, 100, 250); background-color: rgb(0, 230, 0);border-style: outset;border-width: 2px;border-radius: 10px; border-color: beige;font: bold 14px;");
}


void MainWindow::on_createNode_released()
{
    ui->createNode->setStyleSheet("color: rgb(200, 61, 33); background-color: rgb(0, 255, 0);border-style: outset;border-width: 2px;border-radius: 10px; border-color: beige;font: bold 14px;");
}


void MainWindow::on_build_pressed()
{
    ui->build->setStyleSheet("color: rgb(100, 100, 250); background-color: rgb(0, 230, 0);border-style: outset;border-width: 2px;border-radius: 10px; border-color: beige;font: bold 14px;");
}


void MainWindow::on_build_released()
{
    ui->build->setStyleSheet("color: rgb(200, 61, 33); background-color: rgb(0, 255, 0);border-style: outset;border-width: 2px;border-radius: 10px; border-color: beige;font: bold 14px;");
}


void MainWindow::on_doWork_pressed()
{
    ui->doWork->setStyleSheet("color: rgb(100, 100, 250); background-color: rgb(0, 230, 0);border-style: outset;border-width: 2px;border-radius: 10px; border-color: beige;font: bold 14px;");
}


void MainWindow::on_doWork_released()
{
    ui->doWork->setStyleSheet("color: rgb(200, 61, 33); background-color: rgb(0, 255, 0);border-style: outset;border-width: 2px;border-radius: 10px; border-color: beige;font: bold 14px;");
}

