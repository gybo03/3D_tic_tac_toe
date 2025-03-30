#include "/usr/include/boost/multi_array.hpp"
#include <cmath>
#include <tuple>

class Cube
{
    private:

        boost::multi_array<char, 3> cube;
        char num_of_players;
        bool grav_mech (char, char);
        float go_thru_1D_vector (char, char);
        float go_thru_2D_vector (char, char);
        float go_thru_3D_vector (char, char);
    public:

        bool grav;
        char len;
        char winner = 0;
        char curr_player;
        std::tuple<char, char, char> move;
        Cube (char, char, char = 0, bool = true);
        Cube (Cube&&) = default;      // move
        Cube (const Cube&) = default; // copy
        Cube (Cube&) = default;       // copy
        Cube& operator= (Cube&&) = default;
        Cube& operator= (const Cube&) = default;
        ~Cube () = default;
        bool play_a_move (char, char, char);
        void print () const;
        float calculate_winning_scalar (char = 1);
        void increment_player ();
};
