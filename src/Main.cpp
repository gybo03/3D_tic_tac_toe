#include "../inc/Tree.hpp"
#include <iostream>
#include <limits>
#include <string>

int
main (int argc, char* argv[])
{
    // depth 4 grav on second player wins
    // progressive depth grav on first player wins
    /*Tree t (4, 2, 0, false);*/
    Tree t (4, 2, 0, true);
    int depth = 4;
    t.root->generate_children ();
    t.move_root (0);
    /*t.root->print ();*/
    int i = 0;
    std::string input;
    while (true) {
        std::pair<int, float> move = t.min_max (
            depth, t.root, -std::numeric_limits<float>::max (),
            /*std::numeric_limits<float>::max (), (i++ % 2) ? false : true);*/
            std::numeric_limits<float>::max (), (i++ % 2) ? true : false);
        t.move_root (move.first);
        /*std::cout << "\t" << move.second << "\n";*/
        /*t.root->print ();*/
        /*std::getline (std::cin, input);*/
        /*if (!input.empty () || t.root->cube->winner) break;*/
        if (t.root->cube->winner) break;
        /*if (i % 16 == 0) depth++;*/
    }
    /*Cube c (4, 2, 1, false);*/
    /*c.play_a_move (3, 3, 0);*/
    /*c.play_a_move (3, 2, 0);*/
    /*c.play_a_move (3, 1, 0);*/
    /*c.increment_player ();*/
    /*Tree t (c);*/
    /*t.extend_Tree (1, t.root);*/
    /*std::pair<int, float> move =*/
    /*    t.min_max (1, t.root, -std::numeric_limits<float>::max (),*/
    /*               std::numeric_limits<float>::max (), true);*/
    /*t.move_root (move.first);*/
    /*t.root->print ();*/
    /*std::cout << move.first << " " << move.second;*/
    return 0;
}
