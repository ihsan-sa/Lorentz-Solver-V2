#include "space.hpp"
#include <fstream>

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

        if(FIELD_AT_PT == Ignore){
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

    for(Particle* p_particle : p_particles_){
        File<<"x,y,z,";
    }
    File<<"\n";
    for(Particle* p_particle : p_particles_){
        File<<p_particle->pos().x()<<","<<p_particle->pos().y()<<","<<p_particle->pos().z()<<",";
    }
    File<<"\n";
    //now we loop through iterations
    unsigned long long N = t/dt;
    for(unsigned long long n{0}; n < N; n++){
        //compute the fields at the positions of the particles and then set the next_positions
        for(Particle* p_particle : p_particles_){
        
            Vector f_lorentz{p_particle->q() * (e_field(p_particle->pos()) + (p_particle->vel() * b_field(p_particle->pos())))};
            Vector a_lorentz{f_lorentz * (1/p_particle->m())};
            // std::cout<<f_lorentz<<" "<<a_lorentz;

            //implementing euler's first
            if(SIM_TYPE == Euler){
                
                Vector new_vel{p_particle->vel() + (a_lorentz*dt)};;
                Vector new_pos{p_particle->pos() + (new_vel + p_particle->vel())*(dt/2)};
                p_particle->update_vel(new_vel);
                p_particle->update_next_pos(new_pos);
                // std::cout<<"Euler: "<<new_pos<<p_particle->next_pos()<<new_vel<<"\n";
            }

        }

        //update all the positions

        for(Particle* p_particle : p_particles_){
            p_particle->update_pos();
            File<<p_particle->pos().x()<<","<<p_particle->pos().y()<<","<<p_particle->pos().z()<<",";
        }
        File<<"\n";

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