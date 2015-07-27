// bike.cc (2015-07-27)
// Yan Gaofeng (yangaofeng@360.cn)

#include "bike.h" 

Bike::Bike(int maxGear) { 
    this->maxGear = maxGear; 
    this->currentGear = 1; 
    this->speed = 0; 
} 

void Bike::shift(int gear) { 
    if (gear < 1 || gear > maxGear) { 
        return; 
    } 
    
    currentGear = gear; 
} 

void Bike::accelerate() { 
    speed += (2 * this->getCurrentGear()); 
} 

void Bike::brake() { 
    speed -= (2 * this->getCurrentGear()); 
} 

int Bike::getCurrentSpeed() { 
    return speed; 
} 

int Bike::getCurrentGear() { 
    return currentGear; 
}

