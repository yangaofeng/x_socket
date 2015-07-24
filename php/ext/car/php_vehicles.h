// php_vehicles.h (2015-07-23)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef PHP_VEHICLES_H 
#define PHP_VEHICLES_H 

#define PHP_VEHICLES_EXTNAME "vehicle"
#define PHP_VEHICLES_EXTVER "1.0"

#ifdef HAVE_CONFIG_H
#include "config.h" 
#endif

extern "C" { 
#include "php.h" 
} 

extern zend_module_entry vehicles_module_entry;
#define phpext_vehicles_ptr &vehicle_module_entry; 

PHP_MINIT_FUNCTION(vehicles); 

#endif /* PHP_VEHICLES_H */

