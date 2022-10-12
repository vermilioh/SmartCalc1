#ifndef X_WINDOW_H
#define X_WINDOW_H

#include <QDialog>

namespace Ui {
class X_window;
}

class X_window : public QDialog
{
    Q_OBJECT

public:
    explicit X_window(QWidget *parent = nullptr);
    ~X_window();

private slots:

    void on_go_button_clicked();

private:
    Ui::X_window *ui;
signals:
    void signalX_window(QString a);
};

#endif // X_WINDOW_H
