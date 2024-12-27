#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vector.hpp"


//constants etc

#define K 8.987551787e9

//class definitions

class Object; //parent class

class UEF; //uniform electric field
class UMF; //uniform magnetic field

class SPC; //static point charge

class Particle;

//class declarations

class Object{
public:
    virtual bool is_particle() const = 0; //returns true if it is a particle
    virtual Vector e_field(Vector const &pos) const = 0; //returns the electric field vector at a point due to that object
    virtual Vector b_field(Vector const &pos) const = 0; //returns the magnetic field vector at a point due to that object

    virtual void print() const = 0;
    friend std::ostream &operator<<(std::ostream &out, Object rhs);
};

class UEF : public Object{
    Vector e_field_;
public:
    UEF();
    UEF(Vector const &e_field);
    ~UEF(); //destructor

    UEF(UEF const &org); //copy constructor
    UEF(UEF &&org); //move constructor

    Vector e_field() const; //returns the e_field vector NOTE should i make the distinction between this one and the other one?

    void print() const override;
    bool is_particle() const override; //returns true if it is a particle
    Vector e_field(Vector const &pos) const override; //returns the electric field vector at a point due to that object
    Vector b_field(Vector const &pos) const override; //returns the magnetic field vector at a point due to that object

    friend std::ostream &operator<<(std::ostream &out, UEF const &rhs);
};

class UMF : public Object{
    Vector b_field_;
public:
    UMF();
    UMF(Vector const &b_field);
    ~UMF(); //destructor

    UMF(UMF const &org); //copy constructor
    UMF(UMF &&org); //move constructor

    Vector b_field() const; //returns the e_field vector NOTE should i make the distinction between this one and the other one?

    void print() const override;
    bool is_particle() const override; //returns true if it is a particle
    Vector e_field(Vector const &pos) const override; //returns the electric field vector at a point due to that object
    Vector b_field(Vector const &pos) const override; //returns the magnetic field vector at a point due to that object

    friend std::ostream &operator<<(std::ostream &out, UMF const &rhs);
};

class SPC : public Object{
    Vector pos_;
    long double q_;
public:
    SPC();
    SPC(Vector const &pos, long double const q);
    ~SPC();

    SPC(SPC const &org);
    SPC(SPC &&org);

    Vector pos() const;
    long double q() const;

    void print() const override;
    bool is_particle() const override;
    Vector e_field(Vector const &pos) const override; //returns the electric field vector at a point due to that object
    Vector b_field(Vector const &pos) const override; //returns the magnetic field vector at a point due to that object

    friend std::ostream &operator<<(std::ostream &out, SPC const &rhs);
};

class Particle : public Object{
    Vector pos_; //position
    Vector vel_; //velocity
    long double q_; //charge
    long double m_; //mass
    Vector next_pos_;
public:
    Particle();
    Particle(Vector const &pos, Vector const &vel, long double const q, long double const m);
    ~Particle();

    Particle(Particle const &org); //copy constructor
    Particle(Particle &&org); //move constructor

    Vector pos() const; //returns pos
    Vector next_pos() const;
    Vector vel() const; //returns vel
    long double q() const; //returns q
    long double m() const; //returns m

    void update_pos(); //sets pos_ to next_pos_
    void update_next_pos(Vector const &next_pos); //changes next_pos_
    void update_vel(Vector const &next_vel); //changes vel_


    void print() const override;
    bool is_particle() const override;
    Vector e_field(Vector const &pos) const override; //returns the electric field vector at a point due to that object
    Vector b_field(Vector const &pos) const override; //returns the magnetic field vector at a point due to that object

    friend std::ostream &operator<<(std::ostream &out, Particle const &rhs);
};

#endif