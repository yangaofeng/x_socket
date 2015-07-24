// haha.cc (2015-07-23)
// Yan Gaofeng (yangaofeng@360.cn)

#include "php_haha.h"


zend_class_entry *baby_ce;

void haha_call_user_function(zend_class_entry *ce, char *method_name)
{
    zval *obj;
    zval *retval;
    zval *method;

    MAKE_STD_ZVAL(obj);
    MAKE_STD_ZVAL(retval);
    MAKE_STD_ZVAL(method);
    object_init_ex(obj, ce);

    ZVAL_STRING(method, method_name, 1); //用ZVAL_STRINGL 更快，请看前面教程

    //如果确认此类没有构造函数就不用调用了。
    call_user_function(NULL, &obj, method, retval, 0, NULL TSRMLS_CC);

    zval_ptr_dtor(&obj);
    zval_ptr_dtor(&method);
    return;
}


ZEND_METHOD(baby, __construct)
{
    printf("a new baby!\n");
}

ZEND_METHOD(baby, hello)
{
    printf("hello world!!!!!\n");
}

static zend_function_entry baby_method[] = {
    ZEND_ME(baby, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    ZEND_ME(baby, hello, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

ZEND_FUNCTION(test_call)
{
    //如果确认此类没有构造函数就不用调用了。
    haha_call_user_function(baby_ce, "__construct");
    haha_call_user_function(baby_ce, "hello");

    return;
}

ZEND_FUNCTION(test_return)
{
    zval *obj;
    MAKE_STD_ZVAL(obj);
    object_init_ex(obj, baby_ce);
    haha_call_user_function(baby_ce, "__construct");
    RETURN_ZVAL(obj, 1, 0);
}

PHP_MINIT_FUNCTION(haha) { 
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "baby", baby_method);
    baby_ce = zend_register_internal_class(&ce TSRMLS_CC);

    return SUCCESS;
}

static zend_function_entry haha_function[] = {
    ZEND_FE(test_call, NULL)
    ZEND_FE(test_return, NULL)
    {NULL,NULL,NULL}
};

zend_module_entry haha_module_entry = { 
#if ZEND_MODULE_API_NO >= 20010901 
    STANDARD_MODULE_HEADER, 
#endif 
    "haha",
    haha_function, /* Functions */ 
    PHP_MINIT(haha), 
    NULL, /* MSHUTDOWN */ 
    NULL, /* RINIT */ 
    NULL, /* RSHUTDOWN */ 
    NULL, /* MINFO */ 
#if ZEND_MODULE_API_NO >= 20010901
    "1.0",
#endif
    STANDARD_MODULE_PROPERTIES 
}; 

#ifdef COMPILE_DL_HAHA
extern "C" { 
    ZEND_GET_MODULE(haha) 
}
#endif

