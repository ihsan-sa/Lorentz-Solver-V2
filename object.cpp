#include "object.hpp"
#include <cmath>

//UEF

UEF::UEF() :
e_field_{Vector{}}
{
    //empty
}

UEF::UEF(Vector const &e_field) :
e_field_{e_field}
{
    //empty
}
UEF::UEF(UEF const &org) :
e_field_{org.e_field()}
{
    //empty
}
UEF::UEF(UEF &&org) :
e_field_{Vector{}}
{
    std::swap(e_field_, org.e_field_);
}
UEF::~UEF(){
    e_field_.clear();
}

Vector UEF::e_field() const{
    return e_field_;
}
Vector UEF::e_field(Vector const &pos) const{
    return e_field();
}
Vector UEF::b_field(Vector const &pos) const{
    return Vector{};
}

bool UEF::is_particle() const{
    return false;
}

std::ostream &operator<<(std::ostream &out, UEF const &rhs){
    out<<"Uniform Electric Field (UEF)\n";
    out<<"\te_field: "<<rhs.e_field(Vector{0,0,0})<<"\n";
    out<<"\tb_field: "<<rhs.b_field(Vector{0,0,0});
    out<<std::endl;
    return out;
}

void UEF::print() const{
    std::cout<<"\tUniform Electric Field (UEF)\n";
    std::cout<<"\t\te_field: "<<e_field(Vector{0,0,0})<<"\n";
    std::cout<<"\t\tb_field: "<<b_field(Vector{0,0,0});
    std::cout<<std::endl;
}



//UMF

UMF::UMF() :
b_field_{Vector{}}
{
    //empty
}

UMF::UMF(Vector const &b_field) :
b_field_{b_field}
{
    //empty
}
UMF::UMF(UMF const &org) :
b_field_{org.b_field()}
{
    //empty
}
UMF::UMF(UMF &&org) :
b_field_{Vector{}}
{
    std::swap(b_field_, org.b_field_);
}
UMF::~UMF(){
    b_field_.clear();
}

Vector UMF::b_field() const{
    return b_field_;
}
Vector UMF::e_field(Vector const &pos) const{
    return Vector{};
}
Vector UMF::b_field(Vector const &pos) const{
    return b_field();
}

bool UMF::is_particle() const{
    return false;
}

std::ostream &operator<<(std::ostream &out, UMF const &rhs){
    out<<"Uniform Magnetic Field (UMF)\n";
    out<<"\te_field: "<<rhs.e_field({0,0,0})<<"\n";
    out<<"\tb_field: "<<rhs.b_field(Vector{0,0,0});
    out<<std::endl;
    return out;
}

void UMF::print() const{
    std::cout<<"\tUniform Magnetic Field (UMF)\n";
    std::cout<<"\t\te_field: "<<e_field({0,0,0})<<"\n";
    std::cout<<"\t\tb_field: "<<b_field(Vector{0,0,0});
    std::cout<<std::endl;
}

//PARTICLE

Particle::Particle() :
pos_{Vector{}}, 
vel_{Vector{}},
q_{0},
m_{0},
next_pos_{Vector{}}{
    //empty
}
Particle::Particle(Vector const &pos, Vector const &vel, long double const q, long double const m) :
pos_{pos}, 
vel_{vel}, 
q_{q}, 
m_{m},
next_pos_{Vector{}}{
    //empty
}
Particle::~Particle(){
    pos_.clear();
    vel_.clear();
    next_pos_.clear();
    q_ = 0;
    m_ = 0;
}

Particle::Particle(Particle const &org) :
pos_{org.pos()}, 
vel_{org.vel()},
q_{org.q()},
m_{org.m()}, 
next_pos_{org.next_pos()}{
    //empty
}

Particle::Particle(Particle &&org) :
pos_{Vector{}}, 
vel_{Vector{}},
q_{0},
m_{0}, 
next_pos_{Vector{}}{
    std::swap(pos_, org.pos_);
    std::swap(vel_, org.vel_);
    std::swap(q_, org.q_);
    std::swap(m_, org.m_);
    std::swap(next_pos_, org.next_pos_);
}


Vector Particle::pos() const{
    return pos_;
}
Vector Particle::vel() const{
    return vel_;
}
long double Particle::q() const{
    return q_;
}
long double Particle::m() const{
    return m_;
}
Vector Particle::next_pos() const{
    return next_pos_;
}


void Particle::update_pos(){
    pos_ = next_pos();
}
void Particle::update_next_pos(Vector const &next_pos){
    next_pos_ = next_pos;
}
void Particle::update_vel(Vector const &next_vel){
    vel_ = next_vel;
}

bool Particle::is_particle() const{
    return true;
}
Vector Particle::e_field(Vector const &new_pos) const{
    //using E = kq/r^2
    long double const r{Vector::dist(pos(), new_pos)};

    if(cfig_field_at_pt == zero){
        if(std::abs(r) < TOLERANCE) return Vector{0,0,0}; //if the distance is zero, we return the zero vector instead of infinity
    }

    long double const e_field_strength{K * q() / std::pow(r, 2)};
    Vector dir{new_pos - pos()}; //vector from 
    return dir.change_mag(e_field_strength);
}
Vector Particle::b_field(Vector const &pos) const{
    return Vector{};
}

std::ostream &operator<<(std::ostream &out, Particle const &rhs){
    out<<"Particle\n";
    out<<"\tpos: "<<rhs.pos()<<"\n";
    out<<"\tvel: "<<rhs.vel()<<"\n";
    out<<"\tq: "<<rhs.q()<<"\n";
    out<<"\tm: "<<rhs.m()<<std::endl;
    return out;
}

void Particle::print() const{
    std::cout<<"\tParticle\n";
    std::cout<<"\t\tpos: "<<pos()<<"\n";
    std::cout<<"\t\tvel: "<<vel()<<"\n";
    std::cout<<"\t\tq: "<<q()<<"\n";
    std::cout<<"\t\tm: "<<m()<<std::endl;
}



//SPC

SPC::SPC() :
pos_{Vector{}}, 
q_{0}{
    //empty
}
SPC::SPC(Vector const &pos, long double const q) : 
pos_{pos}, 
q_{q}{
    //empty
}
SPC::~SPC(){
    pos_ = Vector{};
    q_ = 0;
}

SPC::SPC(SPC const &org) :
pos_{org.pos()}, 
q_{org.q()}
{
    //empty
}
SPC::SPC(SPC &&org) :
pos_{Vector{}}, 
q_{0}
{
    std::swap(pos_, org.pos_);
    std::swap(q_, org.q_);
}

Vector SPC::pos() const{
    return pos_;
}
long double SPC::q() const{
    return q_;
}

void SPC::print() const {
    std::cout<<"\tSPC\n";
    std::cout<<"\t\tpos: "<<pos()<<"\n";
    std::cout<<"\t\tq: "<<q()<<std::endl;
}
bool SPC::is_particle() const {
    return false;
}
Vector SPC::e_field(Vector const &new_pos) const {
    //using E = kq/r^2
    long double const r{Vector::dist(pos(), new_pos)};

    //is it necessary to add this? 
    if(cfig_field_at_pt == zero){
        if(std::abs(r) < TOLERANCE) return Vector{0,0,0}; //if the distance is zero, we return the zero vector instead of infinity
    }

    long double const e_field_strength{K * q() / std::pow(r, 2)};
    Vector dir{new_pos - pos()}; //vector from 
    return dir.change_mag(e_field_strength);
}
Vector SPC::b_field(Vector const &pos) const {
    return Vector{};
}

std::ostream &operator<<(std::ostream &out, SPC const &rhs){
    out<<"SPC\n";
    out<<"\tpos: "<<rhs.pos()<<"\n";
    out<<"\tq: "<<rhs.q()<<std::endl;
    return out;
}