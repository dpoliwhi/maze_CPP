#ifndef DIALOG_PLOT_H
#define DIALOG_PLOT_H

#include <QDialog>
#include "../Controller/s21_controller.h"
//#include "calculator.h"


namespace Ui {
class Dialog_plot;
}

namespace s21 {
class Dialog_plot : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_plot(controller *c, std::string in, QWidget *parent = nullptr);
    ~Dialog_plot();
    void set_strin(std::string in) {strin = in;}

private:
    Ui::Dialog_plot *ui;
    controller *cntr;
    std::string strin;

private slots:
    void on_pushButton_clicked();
};
}
#endif // DIALOG_PLOT_H
