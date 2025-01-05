#include "automation.hpp"

int main(){
    

    Wire *p_w1 = new Wire{Vector{0,0,0}, Vector{0,0,1}, 5};
    Wire w1 = *p_w1;
    std::cout<<w1<<w1.b_field(Vector{0.05,0,0})<<"\n"<<w1.b_field(Vector{0.05,0,0}).norm()<<std::endl;

    Wire *p_w2 = new Wire{Vector{0.1,0,0}, Vector{0,0,-1}, 7};
    Wire w2 = *p_w2;
    std::cout<<w2<<w2.b_field(Vector{0.05,0,0})<<"\n"<<w2.b_field(Vector{0.05,0,0}).norm()<<std::endl;
    
    Space s1{p_w1,p_w2};

    std::cout<<s1<<s1.b_field(Vector{0.05,0,0})<<"\n"<<s1.b_field(Vector{0.05,0,0}).norm()<<std::endl;


    
}