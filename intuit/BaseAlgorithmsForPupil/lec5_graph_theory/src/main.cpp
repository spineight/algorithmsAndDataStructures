#include <cycle_detection.hpp>
#include <topological_sort.hpp>
#include <shortest_paths_BFS.hpp>

void show_cycle_detection_in_directed_graph() {
  std::cout << "When all graph is cycle\n";
  lec5_graph_theory::dfs::cycle_detection_in_directed_graph::Graph g;
  g.add(1,2);
  g.add(2,3);
  g.add(3,4);
  g.add(4,6);
  g.add(6,5);
  g.add(5,1);
  auto cycle = g.get_cycle();
  for(auto v : cycle) std::cout << v << "->";
  std::cout << '\n';
  std::cout << "Цикл с предпериодом\n";
  lec5_graph_theory::dfs::cycle_detection_in_directed_graph::Graph g1;
  g1.add(1,2);
  g1.add(2,3);
  g1.add(3,4);
  g1.add(4,5);
  g1.add(5,6);
  g1.add(6,7);
  g1.add(7,3);
  auto cycle1 = g1.get_cycle();
  for(auto v : cycle1) std::cout << v << "->";
  std::cout << '\n';

  std::cout << "Нет цикла\n";
  lec5_graph_theory::dfs::cycle_detection_in_directed_graph::Graph g2;
  g2.add(1,2);
  g2.add(2,1);
  g2.add(2,3);
  g2.add(3,2);
  g2.add(2,4);
  g2.add(4,2);
  auto cycle2 = g2.get_cycle();
  for(auto v : cycle2) std::cout << v << "->";
  std::cout << '\n';

}

void show_topological_sort() {
  std::cout << "topological sort\n";
  lec5_graph_theory::topological_sort::Graph g;
  g.add(1,2);
  g.add(2,3);
  g.add(3,4);
  g.add(1,5);
  g.add(5,6);
  g.add(6,4);
  auto top_order = g.top_sort();
  for(auto v : top_order) std::cout << v << "->";
  std::cout << '\n';
}

void show_shortest_paths_BFS() {
  std::cout << "shortest_paths_BFS\n";
  lec5_graph_theory::shortest_paths_BFS::Graph g;
  g.add(1,2);
  g.add(2,1);
  g.add(2,4);
  g.add(4,2);
  g.add(4,3);
  g.add(3,4);
  g.add(3,1);
  g.add(1,3);
  std::cout << g.distance(1,2) << '\n';
  g.shortest_path(1,2);

  std::cout << '\n';
  lec5_graph_theory::shortest_paths_BFS::Graph g1;
  g1.add(1,2);
  g1.add(2,1);
  g1.add(2,3);
  g1.add(3,2);
  g1.add(3,4);
  g1.add(4,3);
  g1.add(1,4);
  g1.add(4,1);
  std::cout << g1.distance(1,4) << '\n';
  g1.shortest_path(1,4);
}


int main() {
  show_cycle_detection_in_directed_graph();
  show_topological_sort();
  show_shortest_paths_BFS();
  return 0;
}