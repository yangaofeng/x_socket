// car_php.cc (2015-07-27)
// Yan Gaofeng (yangaofeng@360.cn)

#include "car.h"


PHP_METHOD(Car, __construct) {

    long maxGear;
    Car *car = NULL;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &maxGear) == FAILURE) {
        RETURN_NULL();
    }

    car = new Car(maxGear);
    Zend2Cpp<Car> *obj = (Zend2Cpp<Car> *)zend_object_store_get_object(object TSRMLS_CC);
    obj->co = car;
} 

PHP_METHOD(Car, shift) {
} 

PHP_METHOD(Car, accelerate) {
    Car *car;
    Zend2Cpp<Car> *obj = (Zend2Cpp<Car> *)zend_object_store_get_object(
            getThis() TSRMLS_CC);
    car = obj->co;
    if (car != NULL) {
        car->accelerate();
    }
} 

PHP_METHOD(Car, brake) {
} 

PHP_METHOD(Car, getCurrentSpeed) {
    Car *car;
    Zend2Cpp<Car> *obj = (Zend2Cpp<Car> *)zend_object_store_get_object(
            getThis() TSRMLS_CC);
    car = obj->co;
    if (car != NULL) {
        RETURN_LONG(car->getCurrentSpeed());
    }
    RETURN_NULL();
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

