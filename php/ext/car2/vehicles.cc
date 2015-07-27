
#include "php_vehicles.h" 
#include "zend_2_cpp.h"

#include "car_php.cc"
#include "bike_php.cc"

#define CPP_CLASS_DEC(name) \
    zend_class_entry name##_ce; \
    INIT_CLASS_ENTRY(name##_ce, #name, g_##name##_methods); \
    g_##name##_ce = zend_register_internal_class(&name##_ce TSRMLS_CC); \
    g_##name##_ce->create_object = create_handler<Car, &g_##name##_oh>; \
    memcpy(&g_##name##_oh, \
            zend_get_std_object_handlers(), sizeof(zend_object_handlers)); \
    g_##name##_oh.clone_obj = NULL;


PHP_MINIT_FUNCTION(vehicles) { 
    CPP_CLASS_DEC(Car)
    CPP_CLASS_DEC(Bike)
    return SUCCESS;
}

zend_module_entry vehicles_module_entry = { 
#if ZEND_MODULE_API_NO >= 20010901 
    STANDARD_MODULE_HEADER, 
#endif 
    PHP_VEHICLES_EXTNAME, 
    NULL, /* Functions */ 
    PHP_MINIT(vehicles), 
    NULL, /* MSHUTDOWN */ 
    NULL, /* RINIT */ 
    NULL, /* RSHUTDOWN */ 
    NULL, /* MINFO */ 
#if ZEND_MODULE_API_NO >= 20010901 
    PHP_VEHICLES_EXTVER, 
#endif
    STANDARD_MODULE_PROPERTIES 
}; 

#ifdef COMPILE_DL_VEHICLES 
extern "C" { 
    ZEND_GET_MODULE(vehicles) 
}
#endif

