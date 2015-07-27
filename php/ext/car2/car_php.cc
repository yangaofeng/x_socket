// car_php.cc (2015-07-27)
// Yan Gaofeng (yangaofeng@360.cn)

#include "car.h"
#include "zend_2_cpp.h"


PHP_METHOD(Car, __construct) {

    long maxGear;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &maxGear) == FAILURE) {
        RETURN_NULL();
    }

    set_co<Car>(getThis(), new Car(maxGear));
} 

PHP_METHOD(Car, shift) {
} 

PHP_METHOD(Car, accelerate) {
    get_co<Car>(getThis())->accelerate();
} 

PHP_METHOD(Car, brake) {
} 

PHP_METHOD(Car, getCurrentSpeed) {
    int speed = get_co<Car>(getThis())->getCurrentSpeed();
    RETURN_LONG(speed);
} 

PHP_METHOD(Car, getCurrentGear) {
} 

function_entry g_Car_methods[] = { 
    PHP_ME(Car, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR) 
    PHP_ME(Car, shift, NULL, ZEND_ACC_PUBLIC) 
    PHP_ME(Car, accelerate, NULL, ZEND_ACC_PUBLIC) 
    PHP_ME(Car, brake, NULL, ZEND_ACC_PUBLIC) 
    PHP_ME(Car, getCurrentSpeed, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Car, getCurrentGear, NULL, ZEND_ACC_PUBLIC) 
    {NULL, NULL, NULL}
};

zend_class_entry *g_Car_ce; 
zend_object_handlers g_Car_oh;

