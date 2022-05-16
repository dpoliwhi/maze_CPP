#ifndef SUBSTITUTE_X_H
#define SUBSTITUTE_X_H

#include <QDialog>
#include "dialog_plot.h"
//#include "calculator.h"
#include "../Controller/s21_controller.h"

namespace Ui {
class Substitute_x;
}

namespace s21 {
class Substitute_x : public QDialog
{
    Q_OBJECT

public:
    explicit Substitute_x(s21::controller *c, QWidget *parent = nullptr);
    ~Substitute_x();
    void set_strin(std::string in) {strin = in;}

private:
    Ui::Substitute_x *ui;
    controller *cntr;
    Dialog_plot *dialog;
    std::string strin;

signals:
    void signalForm(QString a);

public slots:
    void on_calc_with_x_clicked();
private slots:
    void on_creat_graph_clicked();
};
}
#endif // SUBSTITUTE_X_H
