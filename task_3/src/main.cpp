#include "methods.hpp"

int main(){
    for(int i = 10; i <= 10; i++){
        SweepMethod_tableOutput(i);
        YakobiMethod_tableOutput(i);
        ZeidelMethod_tableOutput(i);
        relaxationMethod_tableOutput(i);
    }
    return 0;
}
