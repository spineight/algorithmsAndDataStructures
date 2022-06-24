#pragma once
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

#define show_vars(args...) { \
  std::string vars_names = #args; \
  std::replace(begin(vars_names), end(vars_names), ',', ' ');\
  std::stringstream ss(vars_names);\
  std::istream_iterator<std::string> it(ss);\
  _show_vars(it, args);\
}

void _show_vars(std::istream_iterator<std::string>& it) {
  std::cout << "!\n"; // just for fun
}

template<typename ... ArgsT, typename ValT>
void _show_vars(std::istream_iterator<std::string>& it, const std::vector<ValT>& val, ArgsT ...args) {
  std::cout << *it++ << ":";
  for(auto& v : val) std::cout << v << ",";
  std::cout << '\n';
  _show_vars(it, args ...);
}

template<typename ... ArgsT, typename ValT>
void _show_vars(std::istream_iterator<std::string>& it, const ValT& val, ArgsT ...args) {
  std::cout << *it++ << ":" << val << '\n';
  _show_vars(it, args ...);
}


#include <adjacency_lists.hpp>
#include <dfs.hpp>
#include <connected_components.hpp>
#include <sstream>
#include <string>

void show_adjacency_lists() {
  lec4_graph_theory::adjacency_lists::Graph dg;
  std::string in = "5 5 "
                   "5 1     1 2     2 3     3 4    4 5";
  std::stringstream ss(in);
  ss >> dg;
  std::cout << dg << '\n';


  lec4_graph_theory::adjacency_lists::Graph dg1;
  std::string in1 = "5 4 "
                   "1 2     2 3     1 4     1 5";
  std::stringstream ss1(in1);
  ss1 >> dg1;
  std::cout << dg1 << '\n';
}

void show_dfs() {
  std::cout << "dfs 1\n";
  lec4_graph_theory::dfs::Graph g;
  g.add(1,2);
  g.add(1,3);
  g.add(2,4);
  g.add(2,5);
  g.add(3,6);
  g.add(3,7);
  std::cout << g << "\n\n\n";
  g.dfs(1);
  std::cout << "dfs 2 \n";
  g.dfs(2);
}

void show_connected_components() {
  std::cout << "connected components\n";
  lec4_graph_theory::connected_components::Graph g;
  g.add(1,2);
  g.add(2,1);

  g.add(2,3);
  g.add(3,2);

  g.add(3,4);
  g.add(4,3);

  g.add(4,1);
  g.add(1,4);

  g.add(5,6);
  g.add(6,5);

  g.add(7,7);

  std::cout << "Components:" <<  g.find_components() << '\n';
}

int main() {
  show_adjacency_lists();
  show_dfs();
  show_connected_components();
  return 0;
}