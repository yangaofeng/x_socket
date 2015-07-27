// zend_2_cpp.h (2015-07-27)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __ZEND_2_CPP_H__
#define __ZEND_2_CPP_H__

#include "php_vehicles.h" 

template<class T>
struct Zend2Cpp {
    zend_object zo;
    T *co; //c++ object pointer
};

template <class T>
void free_storage(void *object TSRMLS_DC)
{
    Zend2Cpp<T> *obj = (Zend2Cpp<T> *)object;
    delete obj->co; 

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

template <class T, zend_object_handlers *handlers>
zend_object_value create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    Zend2Cpp<T> *obj = (Zend2Cpp<T> *)emalloc(sizeof(Zend2Cpp<T>));
    memset(obj, 0, sizeof(Zend2Cpp<T>));
    obj->zo.ce = type;

    ALLOC_HASHTABLE(obj->zo.properties);
    zend_hash_init(obj->zo.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->zo.properties, &type->default_properties,
            (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
            free_storage<T>, NULL TSRMLS_CC);
    retval.handlers = handlers;

    return retval;
}

template <class T>
void set_co(zval *obj, T *co)
{
    ((Zend2Cpp<T> *)zend_object_store_get_object(obj TSRMLS_CC))->co = co;
}

template <class T>
T *get_co(zval *obj)
{
    return ((Zend2Cpp<T> *)zend_object_store_get_object(obj TSRMLS_CC))->co;
}

#endif /*__ZEND_2_CPP_H__*/

