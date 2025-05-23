#include "automation.hpp"
#include <fstream>
#include <string>

std::string get_line(std::size_t const idx){
    std::ifstream Config_file{"config.txt"};

    std::size_t line_idx{0};
    std::string line{};
    while(std::getline(Config_file, line)){

        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

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
void parse_SUMF(Space &space, std::size_t &line_idx){
    line_idx++;
    Vector field{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c1{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c2{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c3{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c4{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c5{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c6{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c7{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector c8{extract_vector(get_line(line_idx))};

    SUMF* p_m{new SUMF{field, {c1,c2,c3,c4,c5,c6,c7,c8}}};
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

void parse_config(long double &t, long double &dt, Vector &c1, Vector &c2, long double &spacing, std::vector<Vector> &target_positions, std::size_t &line_idx){
    line_idx++;
    std::string sim_type{get_line(line_idx)};
    if(sim_type == "Lorentz Motion"){
        cfig_sim_type = lorentz_motion;
        line_idx++;
        t = std::stold(get_line(line_idx));
        line_idx++;
        dt = std::stold(get_line(line_idx));
        line_idx++;
        std::string method_type{get_line(line_idx)};
        if(method_type == "RK4 Euler"){
            cfig_num_method = rk4_euler;
        }else if(method_type == "RK4 Hybrid"){
            cfig_num_method = rk4_hybrid;
        }else if(method_type == "Euler"){
            cfig_num_method = euler;
        }else{
            throw std::domain_error{
                "ERR: Provide simulation method (eg. RK4)"
            };
        }
    }else if(sim_type == "B Field"){
        cfig_sim_type = b_field;
        line_idx++;
        c1 = extract_vector(get_line(line_idx));
        line_idx++;
        c2 = extract_vector(get_line(line_idx));
        line_idx++;
        spacing = std::stold(get_line(line_idx));
    } else if(sim_type == "Static"){
        cfig_sim_type = static_compute;
        do{
            line_idx++;
            Vector pos{extract_vector(get_line(line_idx))};
            target_positions.push_back(pos);
        } while(get_line(line_idx + 1) != "");
    }
    line_idx++;
}

void parse_wire(Space &space, std::size_t &line_idx){
    line_idx++;
    Vector org{extract_vector(get_line(line_idx))};
    line_idx++;
    Vector dir{extract_vector(get_line(line_idx))};
    line_idx++;
    long double i_wire{std::stold(get_line(line_idx))};

    Wire *p_wire{new Wire{org, dir, i_wire}};
    space.add({p_wire});
    line_idx++;
}

void run_simulation(){
    Space sim_space{};

    //vars needed for various sims
    //lorentz motion
    long double t{0};
    long double dt{0};

    //b field
    Vector c1{};
    Vector c2{};
    long double spacing{};

    //static 
    std::vector<Vector> target_positions;

    std::size_t line_idx{0};

    while(get_line(line_idx) != "#"){

        std::string line = get_line(line_idx);

        if(line == "CONFIG"){
            // std::cout<<"Config\n";
            parse_config(t, dt, c1, c2, spacing, target_positions, line_idx);
        }
        else if(line == "P"){
            // std::cout<<"P\n";
            parse_particle(sim_space, line_idx);
        }else if(line == "UMF"){
            // std::cout<<"UMF\n";
            parse_UMF(sim_space, line_idx);
        }else if(line == "SUMF"){
            parse_SUMF(sim_space, line_idx);
        }else if(line == "UEF"){
            // std::cout<<"UEF\n";
            parse_UEF(sim_space, line_idx);
        }else if(line == "SPC"){
            // std::cout<<"SPC\n";
            parse_SPC(sim_space, line_idx);
        }else if(line == "W"){
            parse_wire(sim_space, line_idx);
        }
        line_idx ++;

    }

    std::cout<<sim_space;

    if(cfig_sim_type == lorentz_motion){
        if(t == 0 || dt == 0){
            std::cout<<"Please provide simulation time.\n";
            throw std::domain_error{
                "Err: no sim time or zero step provided."
            };
        }
        sim_space.simulate(t, dt);
    }else if(cfig_sim_type == b_field){
        std::cout<<"Running bfield sim: \n\t"<<c1<<"\n\t"<<c2<<"\n\t"<<spacing<<'\n';
        sim_space.b_vector_field(c1, c2, spacing);
    }else if(cfig_sim_type == static_compute){
        std::cout<<"\n\nStatic simulation"<<std::endl;
        for(Vector position : target_positions){
            std::cout<<"Position: "<<position<<" E field: "<<sim_space.e_field(position)<<" B field: "<<sim_space.b_field(position)<<std::endl;
        }
    }
}