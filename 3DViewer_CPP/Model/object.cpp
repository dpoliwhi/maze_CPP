#include "object.h"

namespace s21 {

Object::Object() {
  V.rows = 0;
  V.count = 0;
  F.rows = 0;
  F.count = 0;
}

std::vector<double> Object::parsingLineVertexes(std::string line) {
  std::vector<double> data;
  std::string buffer;
  std::string::iterator iter(line.begin());
  // for (int i = 0; i < line.size(); i++) {
  while (iter != line.end()) {
    if ((isdigit(*iter) != 0) || *iter == '-' || *iter == '.') {
      buffer.push_back(*iter);
      if ((iter + 1) == line.end() || ((iter + 1) != line.end() && *(iter + 1) == ' ')) {
        data.push_back(atof(buffer.c_str()));
        extremum.max = std::max(data.back(), extremum.max);
        extremum.min = std::min(data.back(), extremum.min);
        buffer.clear();
      }
    }
    ++iter;
  }
  return data;
}

std::vector<int> Object::parsingLineFaces(std::string line) {
  std::vector<int> data;
  std::string buffer;
  std::string::iterator iter(line.begin());
  while (iter != line.end()) {
    if (isdigit(*iter) != 0) {
      buffer.push_back(*iter);
      if ((iter + 1) == line.end() ||
          ((iter + 1) != line.end() && (*(iter + 1) == ' ' || *(iter + 1) == '/'))) {
        if (data.size() != 0 && data.size() % 2 == 0) {
          data.push_back(data.back());
        }
        data.push_back(atof(buffer.c_str()));
        buffer.clear();
        if ((iter + 1) != line.end() && *(iter + 1) == '/') {
          while (*(iter + 1) != ' ' && (iter + 1) != line.end()) {
            ++iter;
          }
        }
      }
    }
    ++iter;
  }
  data.push_back(data.back());
  data.push_back(data.front());
  return data;
}

std::pair<double, double> Object::getExtremum() {
  return std::pair<double, double>{extremum.min, extremum.max};
}

void Object::openFile(std::string fileName) {
  cleanData();
  std::ifstream file(fileName);
  std::string line;
  while (getline(file, line)) {
    if (*line.begin() == 'v' && *(line.begin() + 1) == ' ') {
      V.data.push_back(parsingLineVertexes(line));
      V.rows++;
      V.count += V.data[V.rows - 1].size();
    } else if (*line.begin() == 'f') {
      F.data.push_back(parsingLineFaces(line));
      F.rows++;
      F.count += F.data[F.rows - 1].size() / 2;
    }
  }
  file.close();
}

void Object::cleanData() {
  for (size_t i = 0; i < V.data.size(); i++) {
    V.data[i].clear();
  }
  V.data.clear();
  V.count = 0;
  V.rows = 0;
  for (size_t i = 0; i < F.data.size(); i++) {
    F.data[i].clear();
  }
  F.data.clear();
  F.count = 0;
  F.rows = 0;
  extremum = {0, 0};
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> Object::getVandF() {
  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> toDraw;
  toDraw.first = V.data;
  toDraw.second = F.data;
  return toDraw;
}

std::pair<int, int> Object::getCountVandF() { return std::pair<int, int>{V.rows, F.count}; }

std::pair<int, int> Object::getRowsVandF() { return std::pair<int, int>{V.rows, F.rows}; }

}  // namespace s21
