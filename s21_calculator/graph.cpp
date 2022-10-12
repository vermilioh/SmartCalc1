#include "graph.h"
#include "ui_graph.h"


Graph::Graph(QWidget *parent, QString str_out) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    str = str_out;

}

Graph::~Graph()
{
    delete ui;
}


void Graph::on_pushButton_clicked()
{
    x_step = 0.0001;
    x_start = ui->sp_x_st->value();
    x_end = ui->sp_x_end->value();
    y_start = ui->sp_y_st->value();
    y_end= ui->sp_y_end->value();
    int error = 0;

    ui->Widget->xAxis->setRange(x_start, x_end);
    ui->Widget->yAxis->setRange(y_start, y_end);

    if(x_start >= x_end || y_start >= y_end){
        error = 1;
    }


    for (X = x_start; X <= x_end && error == 0; X += x_step) {
    x.push_back(X);
    double Y = 0;
    char tmp_x[100] = {0};
    snprintf(tmp_x, 100, "%f", X);
    QByteArray count = str.toLocal8Bit();
    count.replace("x", tmp_x);
    char * expression = count.data();
    Y = s21_parser(expression);
    y.push_back(Y);
    }
    if (error == 0) {
            ui->Widget->addGraph();
            ui->Widget->graph(0)->setLineStyle(QCPGraph::lsNone);
            ui->Widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
            ui->Widget->graph(0)->addData(x,y);
            ui->Widget->replot();
            ui->Widget->setInteraction(QCP::iRangeDrag, true);
            ui->Widget->setInteraction(QCP::iRangeZoom, true);
    }



}

