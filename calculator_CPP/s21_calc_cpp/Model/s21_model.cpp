#include "s21_model.h"

namespace s21 {

void model::polish_helper_case_1(std::string data, std::stack<std::string> *buf) {
  vec_polish.push_back(buf->top());
  buf->pop();
  buf->push(data);
}

void model::polish_helper_case_2(std::stack<std::string> *buf) {
  vec_polish.push_back(buf->top());
  buf->pop();
}

void model::polish_natation() {
  std::stack<std::string> buf;
  for (size_t i = 0; i < vec_s.size(); i++) {
    std::string data = vec_s[i];
    if ((data[0] >= 48 && data[0] <= 57) || data[0] == 46 || data[0] == 120 || data[0] == 109 ||
        data[0] == 112) {
      vec_polish.push_back(data);
    } else if (memchr("cstal(", data[0], 6)) {
      buf.push(data);
    } else if (data[0] == 94) {
      buf.push(data);
    } else if (memchr("%%*+-/", data[0], 6)) {
      if (buf.size() > 0) {
        while (buf.top()[0] == 94) {
          polish_helper_case_2(&buf);
        }
        if (data == buf.top()) {
          polish_helper_case_1(data, &buf);
        } else if (memchr("%%*+-/(", buf.top()[0], 7)) {
          if (memchr("%%*/", buf.top()[0], 4)) {
            polish_helper_case_1(data, &buf);
          } else if ((memchr("+-", data[0], 2)) && (memchr("+-", buf.top()[0], 2))) {
            polish_helper_case_1(data, &buf);
          } else {
            buf.push(data);
          }
        }
      } else {
        buf.push(data);
      }
    } else if (data[0] == 41) {
      while (buf.top()[0] != 40) {
        polish_helper_case_2(&buf);
      }
      if (buf.size()) {
        buf.pop();
      }
      if (buf.size() && memchr("cstal", buf.top()[0], 5)) {
        polish_helper_case_2(&buf);
      }
    }
  }
  while (buf.size()) {
    polish_helper_case_2(&buf);
  }
}

double model::calc_operations(char tok) {
  double b = stack_d.top();
  stack_d.pop();
  double a = stack_d.top();
  stack_d.pop();
  double res = 0;
  if (tok == 37) res = fmod(a, b);
  if (tok == 42) res = a * b;
  if (tok == 43) res = a + b;
  if (tok == 45) res = a - b;
  if (tok == 47) res = a / b;
  if (tok == 94) res = pow(a, b);
  return res;
}

double model::calc_functions(std::string func) {
  double a = stack_d.top();
  stack_d.pop();
  double res = 0;
  const char *tok = func.c_str();
  if (!strcmp(tok, "sin")) res = sin(a);
  if (!strcmp(tok, "cos")) res = cos(a);
  if (!strcmp(tok, "tan")) res = tan(a);
  if (!strcmp(tok, "acos")) res = acos(a);
  if (!strcmp(tok, "asin")) res = asin(a);
  if (!strcmp(tok, "atan")) res = atan(a);
  if (!strcmp(tok, "sqrt")) res = sqrt(a);
  if (!strcmp(tok, "ln")) res = log(a);
  if (!strcmp(tok, "log")) res = log10(a);
  return res;
}

double model::calculate() {
  double d;
  std::vector<std::string>::iterator in(vec_polish.begin());
  while (in != vec_polish.end()) {
    std::string tok = *in;
    if ((tok[0] >= 48 && tok[0] <= 57) || tok[0] == 46 || tok[0] == 109 || tok[0] == 112 ||
        ((tok[0] == 45 || tok[0] == 43) && (tok[1] >= 48 && tok[1] <= 57))) {
      if (tok[0] == 109) tok[0] = '-';
      if (tok[0] == 112) tok[0] = '+';
      d = std::stod(tok);
      stack_d.push(d);
    } else if (memchr("%%*+-/^", tok[0], 7)) {
      if (stack_d.size() > 1) {
        d = calc_operations(tok[0]);
        stack_d.push(d);
      } else {
        throw "Incorrect expression";
      }
    } else if (memchr("cstal", tok[0], 5)) {
      d = calc_functions(tok);
      stack_d.push(d);
    }
    ++in;
  }
  d = stack_d.top();
  return d;
}

int model::check_parentheses(std::string str) {
  int open = 0;
  for (size_t i = 0; i < str.length(); i++)
    if (str[i] == 40) open++;
  for (size_t j = 0; j < str.length(); j++)
    if (str[j] == 41) open--;
  return open;
}

std::string model::unary_sign(std::string s) {
  int len = s.length();
  if (s[0] == 43) s[0] = 'p';
  if (s[0] == 45) s[0] = 'm';
  for (int i = 1; i < len; i++) {
    if (s[i] == 40 && (s[i + 1] == 43 || s[i + 1] == 45) && (s[i + 2] >= 48 && s[i + 2] <= 57)) {
      if (s[i + 1] == 43) s[i + 1] = 'p';
      if (s[i + 1] == 45) s[i + 1] = 'm';
    }
  }
  return s;
}

void model::parsing_string(std::string strin, std::vector<std::string> *res) {
  char strout[20] = {};
  char buf = '\n';
  int i = 0, j = 0;
  while (buf != '\0') {
    buf = strin[i];
    if ((buf >= 48 && buf <= 57) || buf == 46 || buf == 101 || buf == 120 || buf == 109 || buf == 112) {
      strout[j++] = buf;  // find digit
      if (buf == 101 && (strin[i + 1] == 45 || strin[i + 1] == 43)) {
        i++;
        buf = strin[i];
        strout[j++] = buf;
      }
      if ((strin[i + 1] < 48 || strin[i + 1] > 57) && strin[i + 1] != 46 && strin[i + 1] != 101 &&
          strin[i + 1] != 120) {
        res->push_back(strout);
      }
    } else if (memchr("cstal", buf, 5)) {  // find function
      const char *scut = strin.c_str();
      scut = scut + i;
      std::vector<std::string> func = FUNC;
      for (int k = 0; k < 9; k++) {
        const char *cur_func = func[k].c_str();
        if (!memcmp(scut, cur_func, strlen(cur_func))) {
          memset(strout, '\0', j);
          memcpy(strout, scut, strlen(cur_func));
          res->push_back(strout);
          i += strlen(cur_func) - 1;
          j = strlen(cur_func) - 1;
          memset(strout, '\0', 10);
        }
      }
    } else if (buf == 37 || (buf >= 40 && buf <= 43) || buf == 45 || buf == 47 ||
               buf == 94) {  // find operation
      memset(strout, '\0', j);
      j = 0;
      strout[j] = buf;
      res->push_back(strout);
    } else if (buf != '\0') {
      throw "Incorrect expression";
    }
    i++;
  }
}

double model::s21_calc(std::string strin, std::string x) {
  strin = unary_sign(strin);
  double result = S21_NAN;
  if (check_parentheses(strin) == 0) {
    parsing_string(strin, &this->vec_s);
    polish_natation();
    if (x.compare("nox")) {
      for (size_t i = 0; i < vec_polish.size(); i++)
        if (!vec_polish[i].compare("x")) vec_polish[i] = x;
    }
    result = calculate();
  } else {
    throw "Incorrect expression";
  }
  return result;
}

std::vector<double> model::s21_calc_graph(std::string strin, std::vector<double> x) {
  strin = unary_sign(strin);
  std::vector<double> result;
  std::vector<std::string> temp_polish;
  std::string x_s;
  if (check_parentheses(strin) == 0) {
    parsing_string(strin, &this->vec_s);
    polish_natation();
    temp_polish = vec_polish;
    for (size_t i = 0; i < x.size(); i++) {
      std::ostringstream os_out;
      if (fabs(x[i] - 0) < 1e-6) {
        os_out << "0";
      } else {
        os_out << x[i];
      }
      x_s = os_out.str();
      for (size_t j = 0; j < vec_polish.size(); j++)
        if (!vec_polish[j].compare("x")) vec_polish[j] = x_s;
      result.push_back(calculate());
      vec_polish = temp_polish;
    }
  } else {
    throw "Incorrect expression";
  }
  return result;
}

}  // namespace s21
