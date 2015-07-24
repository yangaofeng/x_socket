// php_haha.h (2015-07-23)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __HAHA_H__
#define __HAHA_H__

#ifdef HAVE_CONFIG_H
#include "config.h" 
#endif

extern "C" { 
#include "php.h" 
} 

extern zend_module_entry haha_module_entry;
#define phpext_haha_ptr &haha_module_entry; 

#endif /*__HAHA_H__*/

