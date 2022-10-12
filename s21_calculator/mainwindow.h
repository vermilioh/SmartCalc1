#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "x_window.h"
#include "graph.h"
#include <QVector>

extern "C" {
#include "../s21_smart_calc.h"
}

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
    X_window *x_window;
    Graph *graph;

private slots:
    void digits_numbers();
    void on_pushButton_equal_clicked();
    void on_pushButton_ac_clicked();
    void trigonometry();
    void on_pushButton_C_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_graph_clicked();

public slots:
    void slotX_window(QString a);
};
#endif // MAINWINDOW_H
