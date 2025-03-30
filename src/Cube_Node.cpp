#include "Cube_Node.hpp"
#include <memory>
#include <vector>

Cube_Node::Cube_Node (Cube& cube): parent (), cube (std::make_shared<Cube> (cube)) {}

Cube_Node::Cube_Node (char len, char num_of_players, char curr_player,
                      bool grav): // parent constructor
    parent (), cube{ std::make_shared<Cube> (len, num_of_players, curr_player, grav) }
{
}

Cube_Node::Cube_Node (Cube& c,
                      std::weak_ptr<Cube_Node> parent): // child constructor
    parent (parent), cube (std::make_shared<Cube> (c))
{
}

std::shared_ptr<Cube_Node>&
Cube_Node::operator[] (const int i)
{
    return children[i];
}

void
Cube_Node::add_child (Cube& child)
{
    children.emplace_back (std::make_shared<Cube_Node> (child, shared_from_this ()));
}

void
Cube_Node::generate_children ()
{
    for (int i = 0; i != ((cube->grav) ? 1 : cube->len); ++i)
        for (int j = 0; j != cube->len; ++j)
            for (int k = 0; k != cube->len; ++k) {
                /*if (!cube->game_over) {*/
                Cube new_cube (*cube);
                new_cube.increment_player ();
                if (new_cube.play_a_move (i, j, k)) add_child (new_cube);
                /*}*/
            }
}

std::vector<std::shared_ptr<Cube_Node>>::iterator
Cube_Node::begin ()
{
    return children.begin ();
}

std::vector<std::shared_ptr<Cube_Node>>::iterator
Cube_Node::end ()
{
    return children.end ();
}

void
Cube_Node::print ()
{
    cube->print ();
}

void
Cube_Node::print_children ()
{
    for (auto child: children) child->print ();
}
