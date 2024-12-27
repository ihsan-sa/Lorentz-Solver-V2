#include "automation.hpp"
#include <fstream>
#include <string>

std::string get_line(std::size_t const idx){
    std::ifstream Config_file{"config.txt"};

    std::size_t line_idx{0};
    std::string line{};
    while(std::getline(Config_file, line)){
        if(line_idx == idx){
            return line;
        }
        line_idx++;
    }

    return "";
}

Vector extract_vector(std::string line){
    long double x{0};
    long double y{0};
    long double z{0};

    std::string s_x{};
    std::string s_y{};
    std::string s_z{};

    //read x
    std::size_t idx{1};
    for(; line[idx] != ','&& line[idx] != ']'; idx++){
        s_x += line[idx];
    }
    idx++;
    for(; line[idx] != ','&& line[idx] != ']'; idx++){
        s_y += line[idx];
    }
    idx++;
    for(; line[idx] != ','&& line[idx] != ']'; idx++){
        s_z += line[idx];
    }
    x = std::stold(s_x);
    y = std::stold(s_y);
    z = std::stold(s_z);
    
    return Vector{x,y,z};
}

void parse_particle(Space &space, std::size_t &line_idx){
    line_idx++;
    
    //read the position vector
    Vector pos{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector vel{extract_vector(get_line(line_idx))};
    line_idx++;
    long double q{std::stold(get_line(line_idx))};
    line_idx++;
    long double m{std::stold(get_line(line_idx))};

    Particle *p_p{new Particle{pos, vel, q, m}};

    space.add({p_p});
    line_idx++;
}
void parse_UMF(Space &space, std::size_t &line_idx){
    line_idx++;
    Vector field{extract_vector(get_line(line_idx))};

    UMF* p_m{new UMF{field}};
    space.add({p_m});
    line_idx++;
}
void parse_UEF(Space &space, std::size_t &line_idx){
    line_idx++;
    Vector field{extract_vector(get_line(line_idx))};

    UEF* p_e{new UEF{field}};
    space.add({p_e});
    line_idx++;
}


void run_simulation(){
    Space sim_space{};

    std::size_t line_idx{0};
    while(get_line(line_idx) != "#"){

        std::string line = get_line(line_idx);

        if(line == "P"){
            parse_particle(sim_space, line_idx);
        }else if(line == "UMF"){
            parse_UMF(sim_space, line_idx);
        }else if(line == "UEF"){
            parse_UEF(sim_space, line_idx);
        }
    
        line_idx ++;
    }

    std::cout<<sim_space;

    sim_space.simulate(10, 0.01);
}