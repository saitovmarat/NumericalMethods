#include "methods.hpp"

int main(){
    for(int i = 10; i <= 20; i+=10){
        std::cout << "n == " << i << "\n";
        SweepMethod_tableOutput(i);
        YakobiMethod_tableOutput(i);
        ZeidelMethod_tableOutput(i);
        relaxationMethod_tableOutput(i);
        descentMethod_tableOutput(i);
        std::cout << "--------\n";
    }
    return 0;
}
