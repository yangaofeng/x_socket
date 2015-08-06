// car.h (2015-07-23)
// Yan Gaofeng (yangaofeng@360.cn)
#ifndef VEHICLE_CAR_H
#define VEHICLE_CAR_H

// A very simple car class
class Car {
public:
    Car(int maxGear);
    ~Car();

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

#endif /* VEHICLE_CAR_H */

