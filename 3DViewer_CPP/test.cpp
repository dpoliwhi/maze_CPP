#include <gtest/gtest.h>

#include "Controller/facade.h"

double check_create_v[] = {0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0,
                           0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0};

int check_create_f[] = {1, 2, 2, 3, 3, 4, 4, 1, 8, 7, 7, 6, 6, 5, 5, 8, 4, 3, 3, 7, 7, 8, 8, 4,
                        5, 1, 1, 4, 4, 8, 8, 5, 5, 6, 6, 2, 2, 1, 1, 5, 2, 6, 6, 7, 7, 3, 3, 2};

double check_closer_3_7[] = {0.0, 3.7, 3.7, 0.0, 0.0, 3.7, 3.7, 0.0, 3.7, 3.7, 3.7, 3.7,
                             0.0, 3.7, 0.0, 0.0, 0.0, 0.0, 3.7, 0.0, 0.0, 3.7, 3.7, 0.0};

double check_farther_2_5[] = {0.0, 0.4, 0.4, 0.0, 0.0, 0.4, 0.4, 0.0, 0.4, 0.4, 0.4, 0.4,
                              0.0, 0.4, 0.0, 0.0, 0.0, 0.0, 0.4, 0.0, 0.0, 0.4, 0.4, 0.0};

double check_movex_5_5[] = {5.5, 1.0, 1.0, 5.5, 0.0, 1.0, 6.5, 0.0, 1.0, 6.5, 1.0, 1.0,
                            5.5, 1.0, 0.0, 5.5, 0.0, 0.0, 6.5, 0.0, 0.0, 6.5, 1.0, 0.0};

double check_movex_1_35[] = {6.85, 1.0, 1.0, 6.85, 0.0, 1.0, 7.85, 0.0, 1.0, 7.85, 1.0, 1.0,
                             6.85, 1.0, 0.0, 6.85, 0.0, 0.0, 7.85, 0.0, 0.0, 7.85, 1.0, 0.0};

double check_movey_5_5[] = {0.0, 6.5, 1.0, 0.0, 5.5, 1.0, 1.0, 5.5, 1.0, 1.0, 6.5, 1.0,
                            0.0, 6.5, 0.0, 0.0, 5.5, 0.0, 1.0, 5.5, 0.0, 1.0, 6.5, 0.0};

double check_movey_1_35[] = {0.0, 7.85, 1.0, 0.0, 6.85, 1.0, 1.0, 6.85, 1.0, 1.0, 7.85, 1.0,
                             0.0, 7.85, 0.0, 0.0, 6.85, 0.0, 1.0, 6.85, 0.0, 1.0, 7.85, 0.0};

double check_movez_5_5[] = {0.0, 1.0, 6.5, 0.0, 0.0, 6.5, 1.0, 0.0, 6.5, 1.0, 1.0, 6.5,
                            0.0, 1.0, 5.5, 0.0, 0.0, 5.5, 1.0, 0.0, 5.5, 1.0, 1.0, 5.5};

double check_movez_1_35[] = {0.0, 1.0, 7.85, 0.0, 0.0, 7.85, 1.0, 0.0, 7.85, 1.0, 1.0, 7.85,
                             0.0, 1.0, 6.85, 0.0, 0.0, 6.85, 1.0, 0.0, 6.85, 1.0, 1.0, 6.85};

double check_rotatex_5_5[] = {0.0, 1.414210, 0.003129, 0.0, 0.705540, 0.708670,  1.0, 0.705540, 0.708670,
                              1.0, 1.414210, 0.003129, 0.0, 0.708670, -0.705540, 0.0, 0.0,      0.0,
                              1.0, 0.0,      0.0,      1.0, 0.708670, -0.705540};

double check_rotatex_1_35[] = {0.0, 0.306668, 1.380563, 0.0, -0.536948, 0.843616, 1.0, -0.536948, 0.843616,
                               1.0, 0.306668, 1.380563, 0.0, 0.843616,  0.536948, 0.0, 0.0,       0.0,
                               1.0, 0.0,      0.0,      1.0, 0.843616,  0.536948};

double check_rotatey_5_5[] = {-0.705540, 1.0, 0.708670, -0.705540, 0.0, 0.708670, 0.003129, 0.0, 1.414210,
                              0.003129,  1.0, 1.414210, 0.0,       1.0, 0.0,      0.0,      0.0, 0.0,
                              0.708670,  0.0, 0.705540, 0.708670,  1.0, 0.705540};

double check_rotatey_1_35[] = {0.536948, 1.0, 0.843616,  0.536948, 0.0, 0.843616, 1.380563, 0.0, 0.306668,
                               1.380563, 1.0, 0.306668,  0.0,      1.0, 0.0,      0.0,      0.0, 0.0,
                               0.843616, 0.0, -0.536948, 0.843616, 1.0, -0.536948};

double check_rotatez_5_5[] = {0.705540, 0.708670,  1.0, 0.0,      0.0,      1.0, 0.708670, -0.705540, 1.0,
                              1.414210, 0.003129,  1.0, 0.705540, 0.708670, 0.0, 0.0,      0.0,       0.0,
                              0.708670, -0.705540, 0.0, 1.414210, 0.003129, 0.0};

double check_rotatez_1_35[] = {-0.536948, 0.843616, 1.0, 0.0,       0.0,      1.0, 0.843616, 0.536948, 1.0,
                               0.306668,  1.380563, 1.0, -0.536948, 0.843616, 0.0, 0.0,      0.0,      0.0,
                               0.843616,  0.536948, 0.0, 0.306668,  1.380563, 0.0};

std::string fileName = "Objects/CUB.obj";
std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> pairObject;

//  create
TEST(test_s21_3DViewer, create) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.openFile(fileName);
  ASSERT_EQ(object.getRowsVertexesAndFaces().first, 8);
  ASSERT_EQ(object.getRowsVertexesAndFaces().second, 6);
  std::vector<std::vector<double>> V = pairObject.first;
  std::vector<std::vector<int>> F = pairObject.second;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_create_v[k++]);
    }
  }
  k = 0;
  for (size_t i = 0; i < F.size(); i++) {
    for (size_t j = 0; j < F[i].size(); j++) {
      ASSERT_EQ(F[i][j], check_create_f[k++]);
    }
  }
}

//  closer
TEST(test_s21_3DViewer, scale_plus) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'S', 'X', 3.7);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_closer_3_7[k++]);
    }
  }
}

//  farther
TEST(test_s21_3DViewer, scale_minus) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'S', 'Y', 2.5);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_farther_2_5[k++]);
    }
  }
}

//  move_x
TEST(test_s21_3DViewer, move_x) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'M', 'X', 5.5);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_movex_5_5[k++]);
    }
  }
  pairObject = object.actionsWithObject("notNew", 'M', 'X', 1.35);
  V = pairObject.first;
  k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_movex_1_35[k++]);
    }
  }
}

//  move_y
TEST(test_s21_3DViewer, move_y) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'M', 'Y', 5.5);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_movey_5_5[k++]);
    }
  }
  pairObject = object.actionsWithObject("notNew", 'M', 'Y', 1.35);
  V = pairObject.first;
  k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_movey_1_35[k++]);
    }
  }
}

//  move_z
TEST(test_s21_3DViewer, move_z) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'M', 'Z', 5.5);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_movez_5_5[k++]);
    }
  }
  pairObject = object.actionsWithObject("notNew", 'M', 'Z', 1.35);
  V = pairObject.first;
  k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(V[i][j], check_movez_1_35[k++]);
    }
  }
}

//  rotate_x
TEST(test_s21_3DViewer, rotate_x) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'R', 'X', 5.5);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_LE(fabs(V[i][j] - check_rotatex_5_5[k++]), 1e-6);
    }
  }
  pairObject = object.actionsWithObject("notNew", 'R', 'X', 1.35);
  V = pairObject.first;
  k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_LE(fabs(V[i][j] - check_rotatex_1_35[k++]), 1e-6);
    }
  }
}

//  rotate_y
TEST(test_s21_3DViewer, rotate_y) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'R', 'Y', 5.5);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_LE(fabs(V[i][j] - check_rotatey_5_5[k++]), 1e-6);
    }
  }
  pairObject = object.actionsWithObject("notNew", 'R', 'Y', 1.35);
  V = pairObject.first;
  k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_LE(fabs(V[i][j] - check_rotatey_1_35[k++]), 1e-6);
    }
  }
}

//  rotate_z
TEST(test_s21_3DViewer, rotate_z) {
  s21::Interface inter;
  s21::Facade object(&inter);
  pairObject = object.actionsWithObject(fileName, 'R', 'Z', 5.5);
  std::vector<std::vector<double>> V = pairObject.first;
  int k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_LE(fabs(V[i][j] - check_rotatez_5_5[k++]), 1e-6);
    }
  }
  pairObject = object.actionsWithObject("notNew", 'R', 'Z', 1.35);
  V = pairObject.first;
  k = 0;
  for (size_t i = 0; i < V.size(); i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_LE(fabs(V[i][j] - check_rotatez_1_35[k++]), 1e-6);
    }
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
