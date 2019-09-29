/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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

/* $Id$ */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <gnu/lib-names.h> 
       
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xlencrypt.h"

/* If you declare any globals in php_xlencrypt.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(xlencrypt)
*/

/* True global resources - no need for thread safety here */
static int le_xlencrypt;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("xlencrypt.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_xlencrypt_globals, xlencrypt_globals)
    STD_PHP_INI_ENTRY("xlencrypt.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_xlencrypt_globals, xlencrypt_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_xlencrypt_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_xlencrypt_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "xlencrypt", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(sha1hash)
{
	char *arg = NULL;
	size_t arg_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}
    
    void * handle = dlopen("libxlencrypt.so",RTLD_LAZY);
    if(!handle){
        printf("%s\n",dlerror());
        return ;
    }
    typedef char* (* _sha1hash_t)(char*);
    _sha1hash_t _sha1hash = (_sha1hash_t)dlsym(handle,"sha1hash");
    const char * dlsym_error = dlerror();
    if(dlsym_error){
        printf("%s\n",dlerror());
        dlclose(handle);
        return ;
    }
    char * res = _sha1hash(arg);
    dlclose(handle);
    RETURN_STRING(res);
    return ;
}


PHP_FUNCTION(aesencode)
{
    char *_key = NULL;
	size_t _keylen;
    char *_src = NULL;
	size_t _srclen;
    
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &_key, &_keylen, &_src, &_srclen) == FAILURE) {
		return;
	}
    
    void * handle = dlopen("libxlencrypt.so",RTLD_LAZY);
    if(!handle){
        printf("%s\n",dlerror());
        return ;
    }
    typedef char* (* _aesencode_t)(char*,char*);
    _aesencode_t _aesencode = (_aesencode_t)dlsym(handle,"aesencode");
    const char * dlsym_error = dlerror();
    if(dlsym_error){
        printf("%s\n",dlerror());
        dlclose(handle);
        return ;
    }
    char * res = _aesencode(_key,_src);
    dlclose(handle);
    RETURN_STRING(res);
    return ;
    
}


PHP_FUNCTION(aesdecode)
{
    
    char *_key = NULL;
	size_t _keylen;
    char *_src = NULL;
	size_t _srclen;
    
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &_key, &_keylen, &_src, &_srclen) == FAILURE) {
		return;
	}
    
    
    void * handle = dlopen("libxlencrypt.so",RTLD_LAZY);
    if(!handle){
        printf("%s\n",dlerror());
        return ;
    }
    typedef char* (* _aesdecode_t)(char*,char*);
    _aesdecode_t _aesdecode = (_aesdecode_t)dlsym(handle,"aesencode");
    const char * dlsym_error = dlerror();
    if(dlsym_error){
        printf("%s\n",dlerror());
        dlclose(handle);
        return ;
    }
    char * res = _aesdecode(_key,_src);
    dlclose(handle);
    RETURN_STRING(res);
    return ;
    
}

/* {{{ php_xlencrypt_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_xlencrypt_init_globals(zend_xlencrypt_globals *xlencrypt_globals)
{
	xlencrypt_globals->global_value = 0;
	xlencrypt_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(xlencrypt)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(xlencrypt)
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
PHP_RINIT_FUNCTION(xlencrypt)
{
#if defined(COMPILE_DL_XLENCRYPT) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(xlencrypt)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(xlencrypt)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xlencrypt support", "enabled");
	php_info_print_table_row(2, "Author", "xianglou");
	php_info_print_table_row(2, "weixin", "xianglou");
	php_info_print_table_row(2, "QQ", "316686606");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ xlencrypt_functions[]
 *
 * Every user visible function must have an entry in xlencrypt_functions[].
 */
const zend_function_entry xlencrypt_functions[] = {
	PHP_FE(confirm_xlencrypt_compiled,	NULL)		/* For testing, remove later. */
    PHP_FE(sha1hash,NULL)
    PHP_FE(aesencode,NULL)
    PHP_FE(aesdecode,NULL)
	PHP_FE_END	/* Must be the last line in xlencrypt_functions[] */
};
/* }}} */

/* {{{ xlencrypt_module_entry
 */
zend_module_entry xlencrypt_module_entry = {
	STANDARD_MODULE_HEADER,
	"xlencrypt",
	xlencrypt_functions,
	PHP_MINIT(xlencrypt),
	PHP_MSHUTDOWN(xlencrypt),
	PHP_RINIT(xlencrypt),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(xlencrypt),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(xlencrypt),
	PHP_XLENCRYPT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_XLENCRYPT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(xlencrypt)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
