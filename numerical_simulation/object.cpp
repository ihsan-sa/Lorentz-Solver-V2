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

//SUMF

SUMF::SUMF() :
b_field_{Vector{}}
{
    //empty
}

SUMF::SUMF(Vector const &b_field, std::initializer_list<Vector> corners) :
b_field_{b_field}, 
corners_{}
{
    int idx{0};
    for(Vector corner : corners){
        corners_[idx] = corner;
        idx++;
    }
}
SUMF::SUMF(SUMF const &org) :
b_field_{org.b_field()}, 
corners_{}
{
    for(int idx{0}; idx < 8; idx++){
        corners_[idx] = org.corners()[idx];
    }
}
SUMF::SUMF(SUMF &&org) :
b_field_{Vector{}}
{
    std::swap(b_field_, org.b_field_);
    std::swap(corners_, org.corners_);
}
SUMF::~SUMF(){
    b_field_.clear();
    for(int idx{0}; idx < 8; idx++){
        corners_[idx] = Vector{};
    }
}

Vector SUMF::b_field() const{
    return b_field_;
}
Vector const * const SUMF::corners() const{
    return corners_;
}
Vector SUMF::e_field(Vector const &pos) const{
    return Vector{};
}

bool SUMF::is_in_region(Vector const &pos) const{
    long double x_max{corners()[0].x()}, x_min{corners()[0].x()};
    long double y_max{corners()[0].y()}, y_min{corners()[0].y()};
    long double z_max{corners()[0].z()}, z_min{corners()[0].z()};

    for(int idx{1}; idx < 8; idx++){
        long double x{corners()[idx].x()};
        long double y{corners()[idx].y()};
        long double z{corners()[idx].z()};

        x_max = std::max(x_max, x);
        x_min = std::min(x_min, x);
        y_max = std::max(y_max, y);
        y_min = std::min(y_min, y);
        z_max = std::max(z_max, z);
        z_min = std::min(z_min, z);
    }

    if(pos.x() >= x_min && pos.x() <= x_max && pos.y() >= y_min && pos.y() <= y_max && pos.z() >= z_min && pos.z() <= z_max) return true;
    else return false;

}

Vector SUMF::b_field(Vector const &pos) const{
    if(is_in_region(pos)) return b_field();
    else return Vector{};
}

bool SUMF::is_particle() const{
    return false;
}

std::ostream &operator<<(std::ostream &out, SUMF const &rhs){
    out<<"Uniform Magnetic Field (SUMF)\n";
    out<<"\te_field: "<<rhs.e_field({0,0,0})<<"\n";
    out<<"\tb_field: "<<rhs.b_field(Vector{0,0,0});
    out<<"\n\tcorners:";
    for(int idx{0}; idx < 8; idx++){
        out<<"\n\t\t"<<rhs.corners()[idx];
    }
    out<<std::endl;
    return out;
}

void SUMF::print() const{
    std::cout<<"\tUniform Magnetic Field (SUMF)\n";
    std::cout<<"\t\te_field: "<<e_field({0,0,0})<<"\n";
    std::cout<<"\t\tb_field: "<<b_field(Vector{0,0,0});
    std::cout<<"\n\t\tcorners:";
    for(int idx{0}; idx < 8; idx++){
        std::cout<<"\n\t\t\t"<<corners()[idx];
    }
    std::cout<<std::endl;
}

//WIRE

Wire::Wire() :
org_{Vector{}}, 
dir_{Vector{}},
i_wire_{0}{
    //empty constructor
}
Wire::Wire(Vector const &org, Vector const &dir, long double const i_wire) :
org_{org},
dir_{dir}, 
i_wire_{i_wire}{
    dir_.normalize();
}
Wire::~Wire() {
    org_ = Vector{};
    dir_ = Vector{};
    i_wire_ = 0;
}

Wire::Wire(Wire const &org) :
org_{org.org()},
dir_{org.dir()}, 
i_wire_{org.i_wire()}
{
    dir_.normalize(); //ensure that the direction vector is normalized
}
Wire::Wire(Wire &&org) :
org_{Vector{}},
dir_{Vector{}}, 
i_wire_{0}{
    std::swap(org_, org.org_);
    std::swap(dir_, org.dir_);
    std::swap(i_wire_, org.i_wire_);
}

Vector Wire::org() const {
    return org_;
}
Vector Wire::dir() const {
    return dir_;
}
long double Wire::i_wire() const {
    return i_wire_;
}

bool Wire::is_particle() const {
    return false;
}
Vector Wire::e_field(Vector const &pos) const {
    return Vector{};
}
Vector Wire::b_field(Vector const &pos) const {
    Vector OP{pos - org()};
    Vector R{OP.perp(dir())};

    if(cfig_field_at_pt == zero && R == Vector{}){
        return Vector{};
    }

    long double b_field_strength = (MU_0_DIV_4PI * 2)*(i_wire()/R.norm());

    Vector field_dir{dir()*R.normalize()};
    
    //other approach

    // Vector d{dir()};
    // Vector r_hat{OP};
    // r_hat.normalize();

    // // Corrected cross product approach
    // Vector b_field = (MU_0_DIV_4PI * i_wire()) * (d *r_hat) * (1/ (r.norm() * r.norm()));
    // std::cout<<"Other approach: "<<b_field<<std::endl;

    return b_field_strength*field_dir;
}

void Wire::print() const{
    std::cout<<"\tWire";
    std::cout<<"\n\t\torg: "<<org();
    std::cout<<"\n\t\tdir: "<<dir();
    std::cout<<"\n\t\tcurrent: "<<i_wire();
    std::cout<<std::endl;
}
std::ostream &operator<<(std::ostream &out, Wire const &rhs){
    out<<"Wire";
    out<<"\n\torg: "<<rhs.org();
    out<<"\n\tdir: "<<rhs.dir();
    out<<"\n\tcurrent: "<<rhs.i_wire();
    out<<std::endl;

    return out;
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