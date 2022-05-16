#include "calculator.h"

#include "ui_calculator.h"

namespace s21 {
calculator::calculator(controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::calculator), cntr(c) {
  ui->setupUi(this);
  sub_x = new Substitute_x(c);
  setFixedSize(size());
  buttons();
}

void calculator::buttons() {
  connect(sub_x, &Substitute_x::signalForm, this, &calculator::slotForm);

  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(click_digits()));
  connect(ui->pushButton_backspace, SIGNAL(clicked()), this, SLOT(click_backspace()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(click_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(click_operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(click_operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(click_divide()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(click_clear()));
  connect(ui->pushButton_brace_open, SIGNAL(clicked()), this, SLOT(click_parentheses_dot_x()));
  connect(ui->pushButton_brace_close, SIGNAL(clicked()), this, SLOT(click_parentheses_dot_x()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(click_parentheses_dot_x()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(click_parentheses_dot_x()));
  connect(ui->pushButton_pi, SIGNAL(clicked()), this, SLOT(click_pi()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(click_functions()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(click_pow()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(click_mod()));
  connect(ui->pushButton_unary_sign, SIGNAL(clicked()), this, SLOT(click_set_sign()));
  connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(quit()));
  connect(ui->pushButton_calculate, SIGNAL(clicked()), this, SLOT(calc()));
}

calculator::~calculator() { delete ui; }

void calculator::click_digits() {
  QPushButton *button_digit = (QPushButton *)sender();
  ui->lineEdit->insert(button_digit->text());
}

void calculator::click_backspace() { ui->lineEdit->backspace(); }

void calculator::click_operations() {
  QPushButton *button_digit = (QPushButton *)sender();
  ui->lineEdit->insert(button_digit->text());
}

void calculator::click_divide() { ui->lineEdit->insert("/"); }

void calculator::click_clear() {
  ui->lineEdit->clear();
  cntr->clear_containers();
}

void calculator::click_parentheses_dot_x() {
  QPushButton *button_digit = (QPushButton *)sender();
  ui->lineEdit->insert(button_digit->text());
}

void calculator::click_pi() { ui->lineEdit->insert("3.141593"); }

void calculator::click_functions() {
  QPushButton *button_digit = (QPushButton *)sender();
  ui->lineEdit->insert(button_digit->text());
  ui->lineEdit->insert("(");
}

void calculator::click_pow() { ui->lineEdit->insert("^"); }

void calculator::click_mod() { ui->lineEdit->insert("%"); }

void calculator::click_set_sign() {
  QString qstr = ui->lineEdit->text();
  std::string str = qstr.toStdString();
  int len = str.length(), t = 0, k = 0;
  for (int i = len - 1; i >= 0; i--) {
    if (str[len - 1] == ')') {
      for (int j = len - 2; j >= 0; j--) {
        if ((str[j] >= 48 && str[j] <= 57) || str[j] == 46)
          k = j - 1;
        else
          break;
      }
    }
    if ((str[i] >= 48 && str[i] <= 57) || str[i] == 46)
      t = i;
    else
      break;
  }
  if (!k) {
    if (t > 1) {
      str.insert(t, "(-");
      str.push_back(')');
    } else if (t == 0) {
      str.insert(t, "-");
    } else if (t == 1 && (str[0] == '-' || str[0] == '+')) {
      if (str[0] == '+')
        str[0] = '-';
      else if (str[0] == '-')
        str[0] = '+';
    }
  } else {
    if (str[k] == '-')
      str[k] = '+';
    else if (str[k] == '+')
      str[k] = '-';
  }
  ui->lineEdit->clear();
  const char *to_lineEdit = str.c_str();
  QString to_lineEdit_qstr;
  to_lineEdit_qstr.append(to_lineEdit);
  ui->lineEdit->insert(to_lineEdit_qstr);
}

void calculator::quit() { QApplication::exit(); }

void calculator::calc() {
  QString qstr = ui->lineEdit->text();
  std::string in = qstr.toStdString();
  if (in.find("x") == (unsigned long)-1) {
    if (in.length()) {
      ui->lineEdit_2->clear();
      ui->lineEdit_2->insert(qstr);
      in = cntr->calc_expression(in, "nox");
      const char *to_lineEdit = in.c_str();
      ui->lineEdit->clear();
      qstr.clear();
      qstr.append(to_lineEdit);
      ui->lineEdit->insert(qstr);
    }
  } else {
    sub_x->set_strin(in);
    sub_x->exec();
  }
}

void calculator::slotForm(QString a) {
  QString qstr_old = ui->lineEdit->text();
  std::string str_old = qstr_old.toStdString();
  std::string x = a.toStdString();
  if (x.length()) {
    ui->lineEdit_2->clear();
    ui->lineEdit_2->insert(qstr_old);
    ui->lineEdit_2->insert(" (x=");
    ui->lineEdit_2->insert(a);
    ui->lineEdit_2->insert(")");
    std::string out;
    out = cntr->calc_expression(str_old, x);
    const char *to_lineEdit = out.c_str();
    ui->lineEdit->clear();
    qstr_old.clear();
    qstr_old.append(to_lineEdit);
    ui->lineEdit->insert(qstr_old);
  }
}
}  // namespace s21
