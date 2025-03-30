#include "../inc/Tree.hpp"
#include <algorithm>
#include <execution>
#include <initializer_list>
#include <limits>
#include <memory>
#include <utility>

Tree::Tree (Cube& cube): root (std::make_shared<Cube_Node> (cube)) {}

Tree::Tree (char len, char num_of_players, char curr_player, bool grav):
    root{ std::make_shared<Cube_Node> (len, num_of_players, curr_player,
                                       grav) }
{
}

void
Tree::extend_Tree (int depth, std::shared_ptr<Cube_Node>& parent)
{
    if (depth == 0) return;
    if (parent->begin () == parent->end ()) parent->generate_children ();
    for (auto child: *parent) extend_Tree (depth - 1, child);
}

void
Tree::printPath (std::initializer_list<int> path)
{
    std::shared_ptr<Cube_Node> curr = root;
    for (auto i: path) {
        (*curr)[i]->print ();
        curr = (*curr)[i];
    }
}

bool
compare_by_second (const std::pair<int, float>& a,
                   const std::pair<int, float>& b)
{
    return a.second < b.second;
}

std::pair<int, float>
Tree::min_max (int depth, std::shared_ptr<Cube_Node>& parent, float alfa,
               float beta, bool should_maximize)
{
    if (depth == 0)
        return std::make_pair (0,
                               parent->cube->calculate_winning_scalar (1) -
                                   parent->cube->calculate_winning_scalar (2));
    else parent->generate_children ();
    if (should_maximize) {
        std::pair<int, float> i_max_eval =
            std::make_pair (0, -std::numeric_limits<float>::max ());
        int i = 0;
        for (auto child: *parent) {
            std::pair<int, float> eval = std::make_pair (
                i++, min_max (depth - 1, child, alfa, beta, false).second);
            i_max_eval = std::max (i_max_eval, eval, compare_by_second);
            alfa = std::max (alfa, eval.second);
            if (beta <= alfa) break;
        }
        return i_max_eval;
    } else {
        std::pair<int, float> i_min_eval =
            std::make_pair (0, std::numeric_limits<float>::max ());
        int i = 0;
        for (auto child: *parent) {
            std::pair<int, float> eval = std::make_pair (
                i++, min_max (depth - 1, child, alfa, beta, true).second);
            i_min_eval = std::min (i_min_eval, eval, compare_by_second);
            beta = std::min (beta, eval.second);
            if (beta <= alfa) break;
        }
        return i_min_eval;
    }
}

void
Tree::move_root (int i)
{
    root = (*root)[i];
}
