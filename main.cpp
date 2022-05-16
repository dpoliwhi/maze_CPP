#include <iostream>
#include <map>
#include <set>
#include <utility>

// #include "s21_rbtree.h"c
#include "s21_BinaryTree.h"

int main(void) {
  std::pair<int, int> pair_one = std::make_pair(44, 44);
  std::pair<int, int> pair_two = std::make_pair(33, 303);
  std::pair<int, int> pair_three = std::make_pair(77, 7777);

  s21::BinaryTree<int, int> one{{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  // s21::associative_container<int, int> one;
  s21::BinaryTree<int, int> two(one);
  // two = one;
  // s21::associative_container<int, int>::iterator iter;
  // std::pair<s21::associative_container<int, int>::iterator, bool> ins;
  // ins = one.insert_data_AC({11, 111});
  // ins.second ? std::cout << "TRUE\n" : std::cout << "FALSE\n";
  // iter = ins.first;
  // std::pair<int, int> ins_pair;
  // ins_pair = *iter;
  // std::cout << ins_pair.first << " : " << ins_pair.second << std::endl;
  // --iter;
  // --iter;
  // std::cout << ins_pair.first << " : " << ins_pair.second << std::endl;
  // one.print_tree();

  std::set<int> one_set{12, 112, 14, 15, 86};
  one_set.insert(88);

// // two.merge(one);
// std::cout<< "container one\n\n";
// one.print_tree();
// std::cout<< "container two\n\n";
// two.print_tree();

// s21::associative_container<int, int> two {pair_one,pair_two, pair_three};
// s21::associative_container<int, int> two;
// two = std::move(one);
// two = one;

// std::pair<typename s21::RedBlackTree<int, int>::Node, bool> find_node;
// find_node = one.find_by_key(33);
// find_node.second ? std::cout << "TRUE\n" : std::cout << "FALSE\n";
// std::cout << find_node.first->data.second << std::endl;

// one.insert_data_AC(pair_one);
// one.insert_data_AC(pair_two);
// std::pair<s21::associative_container<int, int>::iterator, bool> ins(one.insert_data_AC(pair_three));

// ins.second ? std::cout << "TRUE\n" : std::cout << "FALSE\n";
// std::cout << ins.second << std::endl;
// std::cout<< "container one\n";

// one.contains(12) ? std::cout << "TRUE\n" : std::cout << "FALSE\n";

// one.clear();
// one.empty() ? std::cout << "TRUE\n" : std::cout << "FALSE\n";
// two.empty() ? std::cout << "TRUE\n" : std::cout << "FALSE\n";
// std::cout<< "container two\n";
// s21::associative_container<int, int>::iterator itertwo(two.begin());
// ++itertwo;
// std::cout << itertwo._node->data.first << std::endl;

// std::pair<int, int> iter_data = *iter;
// std::cout << iter_data.second << std::endl;

// s21::RedBlackTree<int, int> one;
//   std::pair<int, int> pair_one = std::make_pair(44, 44);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(33, 33);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(77, 77);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(88, 88);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(99, 99);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(22, 222);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(11, 11);
//   one.insert_data(pair_one);
// pair_one = std::make_pair(5, 5);
// one.insert_data(pair_one);
// pair_one = std::make_pair(8, 8);
// one.insert_data(pair_one);
// pair_one = std::make_pair(8, 10);

// std::map <int,int> myFirstMap = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};

// ///вывод явно инициализированной map на экран
// for (auto it = myFirstMap.begin(); it != myFirstMap.end(); ++it)
// {
//     std::cout << it->first << " : " << it->second << std::endl;
// }

// return 0;
}
