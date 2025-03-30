#include "Cube.hpp"
#include <memory>
#include <tuple>
#include <vector>

class Cube_Node: public std::enable_shared_from_this<Cube_Node>
{
    private:

        template<typename T> using shptr = std::shared_ptr<T>;
        std::weak_ptr<Cube_Node> parent;
        std::vector<shptr<Cube_Node>> children;
    public:

        /*Cube_Node ();*/
        shptr<Cube> cube;
        Cube_Node (Cube&);
        Cube_Node (char, char, char = 0, bool = true);
        Cube_Node (Cube&, std::weak_ptr<Cube_Node>);
        Cube_Node (Cube_Node&&) = default;
        Cube_Node (const Cube_Node&) = default;
        Cube_Node& operator= (Cube_Node&&) = default;
        Cube_Node& operator= (const Cube_Node&) = default;
        shptr<Cube_Node>& operator[] (const int);
        ~Cube_Node () = default;
        void generate_children ();
        void add_child (Cube&);
        void print ();
        void print_children ();
        std::vector<std::shared_ptr<Cube_Node>>::iterator begin ();
        std::vector<std::shared_ptr<Cube_Node>>::iterator end ();
};
