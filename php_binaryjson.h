/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
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

#ifndef PHP_BINARYJSON_H
#define PHP_BINARYJSON_H

#define PHP_BINARYJSON_VERSION "0.1"
#define PHP_BINARYJSON_EXTNAME "binaryjson"

extern zend_module_entry binaryjson_module_entry;
#define phpext_binaryjson_ptr &binaryjson_module_entry

#ifdef PHP_WIN32
#	define PHP_BINARYJSON_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BINARYJSON_API __attribute__ ((visibility("default")))
#else
#	define PHP_BINARYJSON_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(binaryjson);
PHP_MSHUTDOWN_FUNCTION(binaryjson);
PHP_RINIT_FUNCTION(binaryjson);
PHP_RSHUTDOWN_FUNCTION(binaryjson);
PHP_MINFO_FUNCTION(binaryjson);

#ifdef WIN32
# ifndef int64_t
typedef __int64 int64_t;
# endif
#endif

typedef struct {
	char *start;
	char *pos;
	char *end;
} buffer;

#define BUF_REMAINING (buf->end-buf->pos)

#define CREATE_BUF(buf, size) \
	buf.start = (char*)emalloc(size); \
	buf.pos = buf.start; \
	buf.end = buf.start + size;

#define PHP_BINARYJSON_SERIALIZE_KEY(type) \
	php_binaryjson_set_type(buf, type); \
	php_binaryjson_serialize_key(buf, name, name_len, prep TSRMLS_CC); \
	if (EG(exception)) { \
		return ZEND_HASH_APPLY_STOP; \
	}

#define DEFAULT_MAX_MESSAGE_SIZE  (32 * 1024 * 1024)
#define DEFAULT_MAX_DOCUMENT_SIZE (16 * 1024 * 1024)

#define INITIAL_BUF_SIZE 4096
#define INT_32 4
#define INT_64 8
#define DOUBLE_64 8
#define BYTE_8 1

#define PREP 1
#define NO_PREP 0

PHP_FUNCTION(binaryjson_encode);
PHP_FUNCTION(binaryjson_decode);

ZEND_BEGIN_MODULE_GLOBALS(binaryjson)
	char *cmd_char;
	long native_long;
	long long_as_object;
	long allow_empty_keys;
ZEND_END_MODULE_GLOBALS(binaryjson)

/* In every utility function you add that needs to use variables 
   in php_binaryjson_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as BINARYJSON_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define BINARYJSON_G(v) TSRMG(binaryjson_globals_id, zend_binaryjson_globals *, v)
#else
#define BINARYJSON_G(v) (binaryjson_globals.v)
#endif

#include "bullsoft_php.h"

#endif	/* PHP_BINARYJSON_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
