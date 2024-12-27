#ifndef CONFIG_HPP
#define CONFIG_HPP

#define TOLERANCE 10e-40

enum E_Field_At_Point{
    zero, 
    ignore
};

enum Simulation_Type{
    euler,
    rk4, 
    rk4_Hybrid
};


extern E_Field_At_Point cfig_field_at_pt;
extern Simulation_Type cfig_sim_type;

#endif