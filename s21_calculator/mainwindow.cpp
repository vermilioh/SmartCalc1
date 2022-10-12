#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "x_window.h"
#include "graph.h"

double num_first;
int flag_x =0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_plus,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_minus,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_mult,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_divide,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_dot,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_l_br,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_r_br,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_mod,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_pow,SIGNAL(clicked()), this,SLOT(digits_numbers()));

    connect(ui->pushButton_sin,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_asin,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_cos,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_acos,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_tan,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_atan,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_log,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_ln,SIGNAL(clicked()), this,SLOT(trigonometry()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()), this,SLOT(trigonometry()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
QPushButton *button = (QPushButton *)sender();
QString new_label = ui->label->text() + button->text();
ui->label->setText(new_label);
}

void MainWindow::trigonometry()
{
QPushButton *button = (QPushButton *)sender();
QString new_label = ui->label->text() + button->text()+'(';
ui->label->setText(new_label);
}

void MainWindow::on_pushButton_equal_clicked()
{

if(flag_x ==1){
    x_window = new X_window;
    x_window->show();
    flag_x =0;
   connect(x_window, &X_window::signalX_window, this, &MainWindow::slotX_window);
}else{
    QString label = ui->label->text();
    QByteArray pointer = label.toLocal8Bit();
    char * str = pointer.data();
    if(s21_validation(str) == 0){
        double res = s21_parser(str);
        QString new_label = QString::number(res, 'g', 20);
        ui->label->setText(new_label);
    }else{
        ui->label->setText("Wrong input!");

    }
}



}


void MainWindow::on_pushButton_ac_clicked()
{
    ui->label->clear();
}


void MainWindow::on_pushButton_C_clicked()
{
     QString new_label =  ui->label->text();
     new_label.chop(1);
     ui->label->setText(new_label);

}


void MainWindow::on_pushButton_x_clicked()
{
  QString new_label =  ui->label->text() + 'x';
  ui->label->setText(new_label);
  flag_x =1;
}



void MainWindow::slotX_window(QString a)
{
   QString str = ui->label->text();
   str.replace('x', a);
   ui->label->setText(str);
}


void MainWindow::on_pushButton_graph_clicked()
{
graph = new Graph(nullptr, ui->label->text());
graph->show();

}

