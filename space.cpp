#include "space.hpp"
#include <fstream>
Space::~Space(){
    for(Object *p_object : p_objects_){
        delete p_object;
        p_object = nullptr;
    }
}

Space::Space(std::initializer_list<Object *> p_objects){
    for(Object* p_object : p_objects){
        p_objects_.push_back(p_object);
        if(p_object->is_particle()){
            p_particles_.push_back((Particle*)p_object);
        }
    }
}
void Space::add(std::initializer_list<Object *> p_objects){
    for(Object* p_object : p_objects){
        p_objects_.push_back(p_object);
        if(p_object->is_particle()){
            p_particles_.push_back((Particle*)p_object);
        }
    }
}

bool Space::is_particle() const{
    return false;
}

Vector Space::e_field(Vector const &pos) const{
    Vector e_field_total{};
    //now we loop through the elements. If pos is equal to the position of a particle, we don't include it

    for(Object *p_object : p_objects_){

        if(cfig_field_at_pt == ignore){
            //if we choose to ignore the pt, then we do this
            if(p_object->is_particle()){
                Particle *p_particle = (Particle*) p_object; //typecast is to a particle
                if(p_particle->pos() == pos){
                    //then don't include this particle in the total calculation
                    continue;
                }
            }
        }

        e_field_total += p_object->e_field(pos);
    }

    return e_field_total;
}
Vector Space::b_field(Vector const &pos) const{
    Vector b_field_total{};

    for(Object *p_object : p_objects_){
        b_field_total += p_object->b_field(pos);
    }

    return b_field_total;
}

void Space::simulate(long double const t, long double const dt) const{

    //first open the file

    std::ofstream File{"data.csv"};

    //print the column headers

    std::size_t p_idx{0};
    for(Particle* p_particle : p_particles_){
        std::string x{"x"};
        std::string y{"y"};
        std::string z{"z"};

        x += std::to_string(p_idx);
        y += std::to_string(p_idx);
        z += std::to_string(p_idx);
        File<<x<<','<<y<<','<<z<<",";
        p_idx++;
    }
    File<<"\n";
    for(Particle* p_particle : p_particles_){
        File<<p_particle->pos().x()<<","<<p_particle->pos().y()<<","<<p_particle->pos().z()<<",";
    }
    File<<"\n";

    //now we loop through the simulation iteratons
    unsigned long long N = t/dt;
    std::cout<<"Number of iterations: "<<N<<std::endl;
    for(unsigned long long n{0}; n < N; n++){
        if(cfig_output != no_output) std::cout<<(long double)n/N<<"%\n";
        //compute the fields at the positions of the particles and then set the next_positions
        for(Particle* p_P : p_particles_){

            //implementing the algorithm
            //euler first
            if(cfig_num_method == euler){

                //compute the lorentz force and accereation 
                // Vector f_lorentz{p_P->q() * (e_field(p_P->pos()) + (p_P->vel() * b_field(p_P->pos())))};
                // Vector a_lorentz{f_lorentz * (1/p_P->m())};
                
                Vector a_lorentz{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel(), e_field(p_P->pos()), b_field(p_P->pos()))};

                Vector new_vel{p_P->vel() + (a_lorentz*dt)};;
                Vector new_pos{p_P->pos() + (new_vel + p_P->vel())*(dt/2)}; //using an average
                p_P->update_vel(new_vel);
                p_P->update_next_pos(new_pos);
                // std::cout<<"Euler: "<<new_pos<<p_P->next_pos()<<new_vel<<"\n";
            }
            else if(cfig_num_method == rk4_euler){

                //approximate velocity using rk4
                Vector a1{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel(), e_field(p_P->pos()), b_field(p_P->pos()))};
                Vector a2{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel() + ((dt/2) * a1), e_field(p_P->pos()), b_field(p_P->pos()))};
                Vector a3{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel() + ((dt/2) * a2), e_field(p_P->pos()), b_field(p_P->pos()))};
                Vector a4{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel() + (dt* a3), e_field(p_P->pos()), b_field(p_P->pos()))};

                Vector new_vel{p_P->vel() + ((dt/6)*(a1 + (2*a2) + (2*a3) + a4))};

                //now approximate position
                //using euler
                Vector new_pos{p_P->pos() + (new_vel * dt)};
                
                p_P->update_vel(new_vel);
                p_P->update_next_pos(new_pos);
                
            }
            else if(cfig_num_method == rk4_hybrid){

                Vector a1{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel(), e_field(p_P->pos()), b_field(p_P->pos()))};
                Vector v1 = p_P->vel();
                Vector a2{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel() + ((dt/2) * a1), e_field(p_P->pos()), b_field(p_P->pos()))};
                Vector v2 = v1 + ((dt/2)*a1);
                Vector a3{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel() + ((dt/2) * a2), e_field(p_P->pos()), b_field(p_P->pos()))};
                Vector v3 = v1 + ((dt/2)*a2);
                Vector a4{comp_a_lorentz(p_P->q(), p_P->m(), p_P->vel() + (dt* a3), e_field(p_P->pos()), b_field(p_P->pos()))};
                Vector v4 = v1 + (dt*a3);

                Vector new_vel{p_P->vel() + ((dt/6)*(a1 + (2*a2) + (2*a3) + a4))};
                Vector new_pos{p_P->pos() + ((dt/6) * (v1 + (2*v2) + (2*v3) + v4))};

                p_P->update_vel(new_vel);
                p_P->update_next_pos(new_pos);
            }

        }

        //update all the positions

        for(Particle* p_P : p_particles_){
            p_P->update_pos();
            File<<p_P->pos().x()<<","<<p_P->pos().y()<<","<<p_P->pos().z()<<",";
        }
        File<<"\n";

    }
}
Vector comp_a_lorentz(long double const q, long double const m, Vector const &v, Vector const &E, Vector const &B){
    return Vector{(q/m)*(E + (v*B))};
}

void Space::b_vector_field(Vector const &c1, Vector const &c2, long double const spacing) const{
    std::ofstream File{"data.csv"};
    File<<"x,y,z,xf,yf,zf"<<std::endl;

    long double x_range{c2.x() - c1.x()};
    long double y_range{c2.y() - c1.y()};
    long double z_range{c2.z() - c1.z()};

    unsigned long long N_x{(unsigned long long)(x_range/spacing)};
    unsigned long long N_y{(unsigned long long)(y_range/spacing)};
    unsigned long long N_z{(unsigned long long)(z_range/spacing)};

    //now, we loop through everything
    for(unsigned long long n_x{0}; n_x < N_x; n_x++){
        for(unsigned long long n_y{0}; n_y < N_y; n_y++){
            for(unsigned long long n_z{0}; n_z < N_z; n_z++){

                Vector offset{n_z*spacing, n_y*spacing, n_z*spacing};
                Vector pos{c1 + offset};

                File<<pos.x()<<","<<pos.y()<<","<<pos.z()<<","<<b_field(pos).x()<<","<<b_field(pos).y()<<","<<b_field(pos).z()<<std::endl;

            }
        }
    }


}


std::ostream &operator<<(std::ostream &out, Space const &rhs){
    std::cout<<"Space: \n";
    for(Object *p_object : rhs.p_objects_){
        p_object->print();
    }
    return out;
}
void Space::print() const{
    std::cout<<*this;
}