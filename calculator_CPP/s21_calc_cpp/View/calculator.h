#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "../Controller/s21_controller.h"
#include "substitute_x.h"
#include "dialog_plot.h"
#include "plot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

namespace s21 {
class calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit calculator(controller *c, QWidget *parent = nullptr);
    ~calculator();

private:
    Ui::calculator *ui;
    controller *cntr;
    s21::Substitute_x *sub_x;

private slots:
    void buttons();

    void click_digits();
    void click_backspace();
    void click_operations();
    void click_divide();
    void click_clear();
    void click_parentheses_dot_x();
    void click_pi();
    void click_functions();
    void click_pow();
    void click_mod();
    void click_set_sign();
    void quit();
    void calc();
    void slotForm(QString a);
};
}
#endif // CALCULATOR_H
