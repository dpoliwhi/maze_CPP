#ifndef PLOT_H
#define PLOT_H

#include <QDialog>
#include <QVector>
#include "../qcustomplot.h"

namespace Ui {
class Plot;
}

namespace s21 {
class Plot : public QDialog
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);
    explicit Plot(int xaxis_ot, int xaxis_do, int yaxis_ot, int yaxis_do, std::vector<double> x, std::vector<double> y, QWidget *parent = nullptr);
    ~Plot();

private:
    Ui::Plot *ui;
};

}
#endif // PLOT_H
