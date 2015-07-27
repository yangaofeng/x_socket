// bike.h (2015-07-27)
// Yan Gaofeng (yangaofeng@360.cn)
#ifndef VEHICLE_BIKE_H
#define VEHICLE_BIKE_H

// A very simple car class
class Bike {
public:
    Bike(int maxGear);
    void shift(int gear);
    void accelerate();
    void brake();
    int getCurrentSpeed();
    int getCurrentGear();

private:
    int maxGear;
    int currentGear;
    int speed;
};

#endif /* VEHICLE_BIKE_H */

