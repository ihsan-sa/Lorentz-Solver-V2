#ifndef CONFIG_HPP
#define CONFIG_HPP

#define TOLERANCE 10e-40

/***
 * @brief Specifies how to handle the electric field at the point of origin.
 */
enum E_Field_At_Point{
    zero, 
    ignore
};

/***
 * @brief Specifies the numerical method to be used in the simulation.
 */
enum Numerical_Method{
    euler,
    rk4_euler, 
    rk4_hybrid
};

/***
 * @brief Specifies how much debug output should be logged to the console.
 */
enum Output_Config{
    no_output,
    progress,
    debug
};

/***
 * @brief Specifies the simulation type.
 */
enum Simulation_Type{
    lorentz_motion, 
    b_field
};

//global enum declarations

extern E_Field_At_Point cfig_field_at_pt;
extern Numerical_Method cfig_num_method;
extern Output_Config cfig_output;
extern Simulation_Type cfig_sim_type;


#endif