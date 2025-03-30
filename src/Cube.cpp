#include "Cube.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <tuple>

Cube::Cube (char len, char num_of_players, char curr_player, bool grav):
    len{ len }, num_of_players{ num_of_players }, curr_player{ curr_player }, grav{ grav }
{
    cube.resize (boost::extents[len][len][len]);
}

float
Cube::go_thru_1D_vector (char v, char player)
{
    char axis = v / (len * len);
    char side = v % (len * len); // deduce which side to select
    char i = side % len;         // from side deduce row
    char j = side / len;         // from side deduce column
    char players_chips = 0;
    for (int k = 0; k < len; ++k) {
        switch (axis) {
            case 0:
                if (cube[k][i][j] == player) players_chips++;
                else if (cube[k][i][j] != 0) return 0;
                break;
            case 1:
                if (cube[j][k][i] == player) players_chips++;
                else if (cube[j][k][i] != 0) return 0;
                break;
            case 2:
                if (cube[i][j][k] == player) players_chips++;
                else if (cube[i][j][k] != 0) return 0;
                break;
        }
    }
    if (players_chips == len && winner == 0) winner = player;
    return pow (10, players_chips - 1);
}

float
Cube::go_thru_2D_vector (char v, char player)
{
    char axis = v / (2 * len);
    char side = v % (2 * len); // on one side there are 2*len 2D vectors
    char i = side % len;       // this will determine which one of len diagonals is chosen
    bool up = side / len;      // this will determine in which direction the ith
                               // diagonal is going
    char players_chips = 0;
    for (char j = 0; j < len; ++j) {
        char down = up ? j : len - 1 - j;
        switch (axis) {
            case 0:
                if (cube[i][j][down] == player) players_chips++;
                else if (cube[i][j][down] != 0) return 0;
                break;
            case 1:
                if (cube[down][i][j] == player) players_chips++;
                else if (cube[down][i][j] != 0) return 0;
                break;
            case 2:
                if (cube[j][down][i] == player) players_chips++;
                else if (cube[j][down][i] != 0) return 0;
                break;
        }
    }
    if (players_chips == len && winner == 0) winner = player;
    return pow (10, players_chips - 1);
}

float
Cube::go_thru_3D_vector (char i, char player)
{
    char players_chips = 0;
    for (char j = 0; j != len; ++j) {
        switch (i) {
            case 0:
                if (cube[j][j][j] == player) players_chips++;
                else if (cube[j][j][j] != 0) return 0;
                break;
            case 1:
                if (cube[len - 1 - j][j][j] == player) players_chips++;
                else if (cube[len - 1 - j][j][j] != 0) return 0;
                break;
            case 2:
                if (cube[j][len - 1 - j][j] == player) players_chips++;
                else if (cube[j][len - 1 - j][j] != 0) return 0;
                break;
            case 3:
                if (cube[j][j][len - 1 - j] == player) players_chips++;
                else if (cube[j][j][len - 1 - j] != 0) return 0;
                break;
        }
    }
    if (players_chips == len && winner == 0) winner = player;
    return pow (10, players_chips - 1);
}

float
Cube::calculate_winning_scalar (char player)
{
    float sum = 0;
    char i = 0;
    if (winner == player) return std::numeric_limits<float>::max ();
    for (i = 0; i < 3 * len * len && winner == 0; ++i)
        sum += std::pow (go_thru_1D_vector (i, player), 2);
    for (i = 0; i < 6 * len && winner == 0; ++i)
        sum += std::pow (go_thru_2D_vector (i, player), 2);
    for (i = 0; i < 4 && winner == 0; ++i)
        sum += std::pow (go_thru_3D_vector (i, player), 2);
    if (winner == player) return std::numeric_limits<float>::max ();
    return std::sqrt (sum);
}

void
Cube::print () const
{
    for (int8_t i = len - 1; i >= 0; --i) {
        for (int8_t j = len - 1; j >= 0; --j) {
            for (int8_t k = 0; k < len; ++k)
                if (move == std::make_tuple (i, j, k))
                    std::cout << " <" << static_cast<int> (cube[i][j][k]) << "> ";
                else std::cout << "  " << static_cast<int> (cube[i][j][k]) << "  ";
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n";
}

bool
Cube::grav_mech (char j, char k)
{
    char i = len;
    while (i > 0 && cube[i - 1][j][k] == 0) i--;
    return (i < len)
               ? (cube[i][j][k] = curr_player, move = std::make_tuple (i, j, k), true)
               : false;
}

bool
Cube::play_a_move (char i, char j, char k)
{
    if (grav) return grav_mech (j, k);
    return (cube[i][j][k] == 0)
               ? (cube[i][j][k] = curr_player, move = std::make_tuple (i, j, k), true)
               : false;
}

void
Cube::increment_player ()
{
    curr_player = (curr_player % num_of_players) + 1;
}
