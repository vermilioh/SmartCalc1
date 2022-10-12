#include "x_window.h"
#include "ui_x_window.h"

X_window::X_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::X_window)
{
    ui->setupUi(this);
}

X_window::~X_window()
{
    delete ui;
}




void X_window::on_go_button_clicked()
{
    emit signalX_window(ui->lineEdit->text());
    close();
}

