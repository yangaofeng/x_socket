// bike_php.cc (2015-07-27)
// Yan Gaofeng (yangaofeng@360.cn)

#include "bike.h"


PHP_METHOD(Bike, __construct) {

    long maxGear;
    Bike *bike = NULL;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &maxGear) == FAILURE) {
        RETURN_NULL();
    }

    bike = new Bike(maxGear);
    Zend2Cpp<Bike> *obj = (Zend2Cpp<Bike> *)zend_object_store_get_object(object TSRMLS_CC);
    obj->co = bike;
} 

PHP_METHOD(Bike, shift) {
} 

PHP_METHOD(Bike, accelerate) {
    Bike *bike;
    Zend2Cpp<Bike> *obj = (Zend2Cpp<Bike> *)zend_object_store_get_object(
            getThis() TSRMLS_CC);
    bike = obj->co;
    if (bike != NULL) {
        bike->accelerate();
    }
} 

PHP_METHOD(Bike, brake) {
} 

PHP_METHOD(Bike, getCurrentSpeed) {
    Bike *bike;
    Zend2Cpp<Bike> *obj = (Zend2Cpp<Bike> *)zend_object_store_get_object(
            getThis() TSRMLS_CC);
    bike = obj->co;
    if (bike != NULL) {
        RETURN_LONG(bike->getCurrentSpeed());
    }
    RETURN_NULL();
} 

PHP_METHOD(Bike, getCurrentGear) {
} 

function_entry g_Bike_methods[] = { 
    PHP_ME(Bike, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR) 
    PHP_ME(Bike, shift, NULL, ZEND_ACC_PUBLIC) 
    PHP_ME(Bike, accelerate, NULL, ZEND_ACC_PUBLIC) 
    PHP_ME(Bike, brake, NULL, ZEND_ACC_PUBLIC) 
    PHP_ME(Bike, getCurrentSpeed, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Bike, getCurrentGear, NULL, ZEND_ACC_PUBLIC) 
    {NULL, NULL, NULL}
};

zend_class_entry *g_Bike_ce; 
zend_object_handlers g_Bike_oh;

