#include "vector.hpp"
#include <cmath>
#include <stdexcept>


Vector::Vector() :
x_{0},
y_{0},
z_{0}
{
    //empty constructor
}
Vector::Vector(long double const x, long double const y, long double const z) :
x_{x}, 
y_{y},
z_{z}
{
    //empty constructor
}

Vector::Vector(Vector const &org) :
x_{org.x()}, 
y_{org.y()}, 
z_{org.z()}
{
    //empty constructor
}
Vector::Vector(Vector &&org) :
x_{0}, 
y_{0}, 
z_{0}
{   
    std::swap(x_, org.x_);
    std::swap(y_, org.y_);
    std::swap(z_, org.z_);
}

Vector::~Vector(){
    clear();
}

Vector &Vector::operator=(Vector const &org){
    x_ = org.x();
    y_ = org.y();
    z_ = org.z();

    return *this;
}
Vector &Vector::operator=(Vector &&org){

    x_ = 0;
    y_ = 0;
    z_ = 0;

    std::swap(x_, org.x_);
    std::swap(y_, org.y_);
    std::swap(z_, org.z_);

    return *this;
}

//getter fns

long double Vector::x() const{
    return x_;
}
long double Vector::y() const{
    return y_;
}
long double Vector::z() const{
    return z_;
}

//operators

Vector &Vector::operator+=(Vector const &rhs){
    x_ = x() + rhs.x();
    y_ = y() + rhs.y();
    z_ = z() + rhs.z();

    return *this;
}
Vector &Vector::operator-=(Vector const &rhs){
    x_ = x() - rhs.x();
    y_ = y() - rhs.y();
    z_ = z() - rhs.z();

    return *this;
}
Vector &Vector::operator*=(Vector const &rhs){
    long double new_x{0}, new_y{0}, new_z{0};

    new_x = (y() * rhs.z()) - (z() * rhs.y());
    new_y = (rhs.x() * z()) - (x() * rhs.z());
    new_z = (x() * rhs.y()) - (y() * rhs.x());

    x_ = new_x;
    y_ = new_y;
    z_ = new_z;

    return *this;
}
Vector &Vector::operator*=(long double const k){
    x_ = k * x();
    y_ = k * y();
    z_ = k * z();

    return *this;
}

Vector Vector::operator+(Vector const &rhs) const{
    Vector tmp{*this};
    tmp += rhs;
    return tmp;
}
Vector Vector::operator-(Vector const &rhs) const{
    Vector tmp{*this};
    tmp -= rhs;
    return tmp;
}
Vector Vector::operator*(Vector const &rhs) const{
    Vector tmp{*this};
    tmp *= rhs;
    return tmp;
}
Vector Vector::operator*(long double const k) const{
    Vector tmp{*this};
    tmp *= k;
    return tmp;
}
Vector operator*(long double const k, Vector const &rhs){
    Vector tmp{rhs};
    tmp *= k;
    return tmp;
}
long double Vector::operator%(Vector const &rhs) const{
    return (x() * rhs.x()) + (y() * rhs.y()) + (z() * rhs.z());
}       

long double Vector::operator[](int const idx){

    switch (idx){
        case 0: return x();
        case 1: return y();
        case 2: return z();
        default:
            throw std::domain_error{
                "Err: trying to access vector index out of range. idx: " + std::to_string(idx)
            };
            break;
    }

}

bool Vector::operator==(Vector const &rhs) const{
    // if((x() == rhs.x()) && (y() == rhs.y()) && (z() == rhs.z())) return true;
    //if tolerance needs to be introduced, use this:
    if((std::abs(x() - rhs.x()) < TOLERANCE) && (std::abs(y() - rhs.y()) < TOLERANCE) && (std::abs(z() - rhs.z()) < TOLERANCE)) return true;
    else return false;
}

//fns
Vector &Vector::clear(){
    x_ = 0;
    y_ = 0;
    z_ = 0;

    return *this;
}
long double Vector::norm() const{
    return std::sqrt(std::pow(x(), 2) + std::pow(y(), 2) + std::pow(z(), 2));
}
long double Vector::dist(Vector const &v1, Vector const &v2){
    Vector tmp{v2 - v1};
    return tmp.norm();
}

Vector &Vector::normalize(){
    long double const sc{1.0 / norm()};
    *this *= sc;
    return *this;
}
Vector &Vector::change_mag(long double new_mag){
    normalize();
    *this *= new_mag;
    return *this;
}

std::ostream &operator<<(std::ostream &out, Vector const &rhs){
    out << "["<<rhs.x()<<","<<rhs.y()<<","<<rhs.z()<<"]";
    return out;
}