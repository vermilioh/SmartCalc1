#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
 #include <QDialog>

#include <QMessageBox>

extern "C" {
#include "../s21_smart_calc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    Graph(QWidget *parent, QString str_out);
    ~Graph();
double x_step, x_start, x_end, y_start, y_end, X;
QVector <double> x,y;
QString str;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Graph *ui;

};

#endif // GRAPH_H
