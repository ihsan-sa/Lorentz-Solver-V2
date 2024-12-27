#ifndef SPACE_HPP
#define SPACE_HPP

#include "object.hpp"
#include <vector>
#include <initializer_list>

class Space;

class Space : public Object{
    std::vector<Object*> p_objects_;
    std::vector<Particle*> p_particles_;
public:
    Space(std::initializer_list<Object *> p_objects);
    void add(std::initializer_list<Object *> p_objects);
    ~Space();

    void print() const override;

    bool is_particle() const override; //returns true if it is a particle
    Vector e_field(Vector const &pos) const override; //returns the electric field vector at a point due to that object
    Vector b_field(Vector const &pos) const override; //returns the magnetic field vector at a point due to that object

    friend std::ostream &operator<<(std::ostream &out, Space const &rhs);

    void simulate(long double const t, long double const dt) const;

};

#endif