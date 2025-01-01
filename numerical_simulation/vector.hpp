#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "config.hpp"

class Vector;

class Vector{
    long double x_;
    long double y_;
    long double z_;

public:
    Vector();
    Vector(long double const x, long double const y, long double const z);

    Vector(Vector const &org); //copy constructor
    Vector(Vector &&org); //move constructor

    ~Vector();

    Vector &operator=(Vector const &org); //copy assignment
    Vector &operator=(Vector &&org); //move assignment

    //getter fns

    long double x() const; //returns x
    long double y() const; //returns y
    long double z() const; //returns z

    //operators

    Vector &operator+=(Vector const &rhs); //add rhs to *this and then returns *this by reference
    Vector &operator-=(Vector const &rhs); //subtract rhs to *this and then returns *this by reference
    Vector &operator*=(Vector const &rhs); //performs cross product, stores in *this and returns by ref
    Vector &operator*=(long double const k); //multiplies by scalar k and returns *this by ref
    
    Vector operator+(Vector const &rhs) const; //adds and returns new vector
    Vector operator-(Vector const &rhs) const; //subs and returns new vector
    Vector operator*(Vector const &rhs) const; //cross product and returns new vector
    Vector operator*(long double const k) const; //multiplies by scalar k and returns new vector
    friend Vector operator*(long double const k, Vector const &rhs); //multiplies by scalar k and returns new vector
    long double operator%(Vector const &rhs) const; //returns the dot product
    bool operator==(Vector const &rhs) const; //returns true if all the components are equal
    long double operator[](int const idx); //returns value at idx (x: 0, y: 1, z: 2)

    //fns
    Vector &clear();
    long double norm() const; //returns the norm of the vector
    static long double dist(Vector const &v1, Vector const &v2); //returns the distance between two vectors
    Vector &normalize(); //normalizes the vector
    Vector &change_mag(long double new_mag); //changes the magnitude of the vector

    
    friend std::ostream &operator<<(std::ostream &out, Vector const &rhs); //for printing vectors

};



#endif