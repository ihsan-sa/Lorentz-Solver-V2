#include "vector.hpp"

int main(){
    Vector v1{};
    Vector v2{};

    if(v1 == v2){
        std::cout<<"Equal";
    }else{
        std::cout<<"Not equal";
    }

    std::cout<<Vector::dist(v1, v2)<<" "<<v1.norm()<<std::endl;
    v1.normalize();
    std::cout<<v1<<" "<<v1.norm()<<std::endl;
    v1.change_mag(10);
    std::cout<<v1<<" "<<v1.norm()<<" "<<v1.change_mag(3)<<v1.norm()<<std::endl;
    
}