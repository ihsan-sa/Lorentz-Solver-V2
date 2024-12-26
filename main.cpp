#include "space.hpp"

int main(){
    

    UMF m1{Vector{0,0,1}};
    UEF e1{Vector{0.2,0,0}};

    Particle p1{
        Vector{0,0,0},
        Vector{1,0,1}, 
        1,
        1
    };

    Space sp1{&m1, &p1, &e1};
    std::cout<<sp1;
    sp1.simulate(10,0.01);


}