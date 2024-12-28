#include "automation.hpp"
#include <fstream>
#include <string>

std::string get_line(std::size_t const idx){
    std::ifstream Config_file{"config.txt"};

    std::size_t line_idx{0};
    std::string line{};
    while(std::getline(Config_file, line)){
        if(line_idx == idx){
            Config_file.close();
            return line;
        }
        line_idx++;
    }

    Config_file.close();

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
void parse_SPC(Space &space, std::size_t &line_idx){
    line_idx++;
    Vector pos{extract_vector(get_line(line_idx))};
    line_idx++;
    long double q{std::stold(get_line(line_idx))};

    SPC* p_spc{new SPC{pos, q}};
    space.add({p_spc});
    line_idx++;
}

void parse_config(long double &t, long double &dt, std::size_t &line_idx){
    line_idx++;
    t = std::stold(get_line(line_idx));
    line_idx++;
    dt = std::stold(get_line(line_idx));
    line_idx++;
    std::string sim_type{get_line(line_idx)};
    if(sim_type == "RK4 Euler"){
        cfig_sim_type = rk4_euler;
    }else if(sim_type == "RK4 Hybrid"){
        cfig_sim_type = rk4_hybrid;
    }else if(sim_type == "Euler"){
        cfig_sim_type = euler;
    }
    line_idx++;
}


void run_simulation(){
    Space sim_space{};

    long double t{0};
    long double dt{0};

    std::size_t line_idx{0};
    while(get_line(line_idx) != "#"){

        std::string line = get_line(line_idx);
        if(line == "CONFIG"){
            // std::cout<<"Config\n";
            parse_config(t, dt, line_idx);
        }
        else if(line == "P"){
            // std::cout<<"P\n";
            parse_particle(sim_space, line_idx);
        }else if(line == "UMF"){
            // std::cout<<"UMF\n";
            parse_UMF(sim_space, line_idx);
        }else if(line == "UEF"){
            // std::cout<<"UEF\n";
            parse_UEF(sim_space, line_idx);
        }else if(line == "SPC"){
            // std::cout<<"SPC\n";
            parse_SPC(sim_space, line_idx);
        }
    
        line_idx ++;
    }

    std::cout<<sim_space;

    if(t == 0 || dt == 0){
        std::cout<<"Please provide simulation time.\n";
        throw std::domain_error{
            "Err: no sim time or zero step provided."
        };
    }
    sim_space.simulate(t, dt);
}