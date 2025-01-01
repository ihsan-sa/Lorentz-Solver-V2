#ifndef CONFIG_HPP
#define CONFIG_HPP

#define TOLERANCE 10e-40

enum E_Field_At_Point{
    zero, 
    ignore
};

enum Numerical_Method{
    euler,
    rk4_euler, 
    rk4_hybrid
};

enum Output_Config{
    no_output,
    progress,
    debug
};

enum Simulation_Type{
    lorentz_motion, 
    b_field
};


extern E_Field_At_Point cfig_field_at_pt;
extern Numerical_Method cfig_num_method;
extern Output_Config cfig_output;
extern Simulation_Type cfig_sim_type;


#endif