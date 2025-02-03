#ifndef AUTOMATION_HPP
#define AUTOMATION_HPP

#include "space.hpp"

void run_simulation(); //will parse the configuration file and run the simulation

void parse_particle(Space &space, std::size_t &line_idx); //parses the information in a particle block
void parse_UMF(Space &space, std::size_t &line_idx); //parses the information in a UMF block
void parse_SUMF(Space &space, std::size_t &line_idx); //parses the information in a SUMF block
void parse_UEF(Space &space, std::size_t &line_idx); //parses the information in a UEF block
void parse_config(long double &t, long double &dt, Vector &c1, Vector &c2, long double &spacing, std::size_t &line_idx); //parses the information in a config block
void parse_wire(Space &space, std::size_t &line_idx); //parses the information in a wire block

std::string get_line(std::size_t const idx); //gets the specified line in the config file

Vector extract_vector(std::string line); //parses and extracts a vector from a string


#endif