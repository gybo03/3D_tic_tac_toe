#include "Cube_Node.hpp"
#include <initializer_list>
#include <memory>

class Tree {
public:
  std::shared_ptr<Cube_Node> root;
  Tree(char, char, char = 0, bool = true);
  Tree(Cube &);
  ~Tree() = default;
  void extend_Tree(int, std::shared_ptr<Cube_Node> &);
  void printPath(std::initializer_list<int>);
  std::pair<int, float> min_max(int, std::shared_ptr<Cube_Node> &, float, float,
                                bool);
  void move_root(int);
};
