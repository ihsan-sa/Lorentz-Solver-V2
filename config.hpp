#ifndef CONFIG_HPP
#define CONFIG_HPP

#define TOLERANCE 10e-40

enum E_Field_At_Point{
    Zero, 
    Ignore
};

enum Simulation_Type{
    Euler,
    RK4, 
    RK4_Hybrid
};


extern E_Field_At_Point FIELD_AT_PT;
extern Simulation_Type SIM_TYPE;

#endif