/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author:                                                              |
   +----------------------------------------------------------------------+
   */

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_helloworld.h"

/*
 * 在调用该函数的php脚本生命周期内创建一个变量foo
 * foo变量在php脚本中直接可用，见test.php
 * */
PHP_FUNCTION(create_foo)
{
    zval *foo;
    MAKE_STD_ZVAL(foo);
    ZVAL_STRING(foo, "hello world", 1);
    ZEND_SET_SYMBOL(EG(active_symbol_table), "foo", foo);
}

/*
 * 返回一个变量给调用者
 * */
PHP_FUNCTION(return_string)
{
    RETURN_STRING("hello world", 1);
}

/*
 * 判断是否是引用调用，如果是，修改变量的值
 * php函数的定义形式如下：
 * function ref_call($a)
 * 调用形式：
 * ref_call(&$a)
 * */
PHP_FUNCTION(call_time_ref_call)
{
    zval *a;

    //我们我接收的参数传给zval *a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a) == FAILURE)
    {
        RETURN_NULL();
    }

    //如果a不是以应用的方式传递的。
    //zval的is_ref__gc这个成员是用来判断是否是引用，不是用来判断引用计数的
    //谨记
    if (!a->is_ref__gc)
    {
        return;
    }

    //将a转成字符串
    convert_to_string(a);

    //更改数据
    ZVAL_STRING(a," (modified by call time ref!)", 1);
    return;
}

/*
 * 编译时引用调用，php函数定义形式如下：
 * function ref_call(&$a)
 * 调用形式：
 * ref_call($a)
 * */
ZEND_BEGIN_ARG_INFO(compile_time_ref_call_arginfo, 0)
	ZEND_ARG_INFO(1, a)
ZEND_END_ARG_INFO()

PHP_FUNCTION(compile_time_ref_call)
{
    zval *a;

    //我们我接收的参数传给zval *a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a) == FAILURE)
    {
        RETURN_NULL();
    }

    //注意与call_time_ref_call函数的区别，
    //因为我们声明了arginfo这里不再需要通过is_ref__gc来判断参数是不是引用传递
    //如果a不是以应用的方式传递的。
    //zval的is_ref__gc这个成员是用来判断是否是引用，不是用来判断引用计数的
    //谨记
    //if (!a->is_ref__gc)
    //{
    //    return;
    //}

    //将a转成字符串
    convert_to_string(a);

    //更改数据
    ZVAL_STRING(a," (modified by compile time ref!)", 1);
    return;
}

ZEND_FUNCTION(return_array)
{
    zval *subarray;

    array_init(return_value);

    /* Add some scalars */
    add_assoc_long(return_value, "life", 42);
    add_index_bool(return_value, 123, 1);
    add_next_index_double(return_value, 3.1415926535);

    /* Toss in a static string, dup'd by PHP */
    add_next_index_string(return_value, "Foo", 1);

    /* Now a manually dup'd string */
    add_next_index_string(return_value, estrdup("Bar"), 0);

    /* Create a subarray */
    MAKE_STD_ZVAL(subarray);
    array_init(subarray);

    /* Populate it with some numbers */
    add_next_index_long(subarray, 1);
    add_next_index_long(subarray, 20);
    add_next_index_long(subarray, 300);

    /* Place the subarray in the parent */
    add_index_zval(return_value, 444, subarray);
}



PHP_FUNCTION(print_array)
{
    zval *z_array; // 外部传入的数组
    int count, i;
    zval **z_item;
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &z_array)) {
        return;
    }

    //获取数组大小
    count = zend_hash_num_elements(Z_ARRVAL_P(z_array));

    //将数组的内部指针指向第一个单元
    zend_hash_internal_pointer_reset(Z_ARRVAL_P(z_array));
    for (i = 0; i < count; i ++) {
        char* key;
        unsigned long idx;
        // 获取当前数据
        zend_hash_get_current_data(Z_ARRVAL_P(z_array), (void**) &z_item);
        convert_to_string_ex(z_item);

        if (zend_hash_get_current_key(Z_ARRVAL_P(z_array), &key, &idx, 0) == HASH_KEY_IS_STRING) {
            // KEY为字符串
            php_printf("array[%s] = %s", key, Z_STRVAL_PP(z_item));
        } else {
            // KEY为数字
            php_printf("array[%d] = %s", idx, Z_STRVAL_PP(z_item));
        }
        // 将数组中的内部指针向前移动一位
        zend_hash_move_forward(Z_ARRVAL_P(z_array));
    }
}

//演示用hashtable api操作数组
//php array same as:
//array("fam1"=>array("col1"=>"val1", "col2"=>"val2"))
ZEND_FUNCTION(hashtable_array)
{
    zval *subarray;
    zval *val1;
    zval *val2;

    MAKE_STD_ZVAL(val1);
    ZVAL_STRING(val1, "val1", 1);
    MAKE_STD_ZVAL(val2);
    ZVAL_STRING(val2, "val2", 1);

    /* Create a subarray */
    MAKE_STD_ZVAL(subarray);
    array_init(subarray);

    php_printf("subarray: %p\n", subarray);

    zend_hash_add(Z_ARRVAL_P(subarray), "col1", sizeof("col1"), &val1, sizeof(zval *), NULL);
    zend_hash_add(Z_ARRVAL_P(subarray), "col2", sizeof("col2"), &val2, sizeof(zval *), NULL);

    array_init(return_value);
    zend_hash_add(Z_ARRVAL_P(return_value), "fam1", sizeof("fam1"), &subarray, sizeof(zval *), NULL);

    //注意，这里必须是**，否则有会问题
    zval **tmp;
    if (zend_hash_find(Z_ARRVAL_P(return_value), "fam1", sizeof("fam1"), (void **)&tmp) == FAILURE) {
        php_printf("create fam1 array element failed\n");
    } else {
        php_printf("create fam1 array element ok, tmp: %p\n", *tmp);
    }
}

///////////////////////////////////////////////////////////////////////////////////////

/* If you declare any globals in php_helloworld.h uncomment this:
   ZEND_DECLARE_MODULE_GLOBALS(helloworld)
   */

/* True global resources - no need for thread safety here */
static int le_helloworld;

/* {{{ helloworld_functions[]
 *
 * Every user visible function must have an entry in helloworld_functions[].
 */
const zend_function_entry helloworld_functions[] = {
    PHP_FE(confirm_helloworld_compiled,	NULL)		/* For testing, remove later. */
    PHP_FE(create_foo, NULL)
    PHP_FE(return_string, NULL)
    PHP_FE(call_time_ref_call, NULL)
    PHP_FE(compile_time_ref_call, compile_time_ref_call_arginfo)
    PHP_FE(return_array, NULL)
    PHP_FE(hashtable_array, NULL)
    {NULL, NULL, NULL}	/* Must be the last line in helloworld_functions[] */
};
/* }}} */

/* {{{ helloworld_module_entry
*/
zend_module_entry helloworld_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "helloworld",
    helloworld_functions,
    PHP_MINIT(helloworld),
    PHP_MSHUTDOWN(helloworld),
    PHP_RINIT(helloworld),		/* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(helloworld),	/* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(helloworld),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1", /* Replace with version number for your extension */
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HELLOWORLD
ZEND_GET_MODULE(helloworld)
#endif

    /* {{{ PHP_INI
    */
    /* Remove comments and fill if you need to have entries in php.ini
       PHP_INI_BEGIN()
       STD_PHP_INI_ENTRY("helloworld.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_helloworld_globals, helloworld_globals)
       STD_PHP_INI_ENTRY("helloworld.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_helloworld_globals, helloworld_globals)
       PHP_INI_END()
       */
    /* }}} */

    /* {{{ php_helloworld_init_globals
    */
    /* Uncomment this function if you have INI entries
       static void php_helloworld_init_globals(zend_helloworld_globals *helloworld_globals)
       {
       helloworld_globals->global_value = 0;
       helloworld_globals->global_string = NULL;
       }
       */
    /* }}} */

    /* {{{ PHP_MINIT_FUNCTION
    */
PHP_MINIT_FUNCTION(helloworld)
{
    /* If you have INI entries, uncomment these lines 
       REGISTER_INI_ENTRIES();
       */
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(helloworld)
{
    /* uncomment this line if you have INI entries
       UNREGISTER_INI_ENTRIES();
       */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
*/
PHP_RINIT_FUNCTION(helloworld)
{
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
*/
PHP_RSHUTDOWN_FUNCTION(helloworld)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(helloworld)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "helloworld support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
       DISPLAY_INI_ENTRIES();
       */
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_helloworld_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_helloworld_compiled)
{
    char *arg = NULL;
    int arg_len, len;
    char *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }

    len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "helloworld", arg);
    RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
   */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

