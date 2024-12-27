#ifndef CONFIG_HPP
#define CONFIG_HPP

#define TOLERANCE 10e-40

enum E_Field_At_Point{
    zero, 
    ignore
};

enum Simulation_Type{
    euler,
    rk4_euler, 
    rk4_hybrid
};

enum Output_Config{
    no_output,
    progress,
    debug
};


extern E_Field_At_Point cfig_field_at_pt;
extern Simulation_Type cfig_sim_type;
extern Output_Config cfig_output;

#endif