#ifndef AUTOMATION_HPP
#define AUTOMATION_HPP

#include "space.hpp"

void run_simulation(); //will parse the configuration file and run the simulation
void parse_particle(Space &space, std::size_t &line_idx);
void parse_UMF(Space &space, std::size_t &line_idx);
void parse_UEF(Space &space, std::size_t &line_idx);


std::string get_line(std::size_t const idx);
Vector extract_vector(std::string line);


#endif