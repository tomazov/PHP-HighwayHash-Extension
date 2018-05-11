#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_highwayhash.h"
#include "highwayhash-impl.h"

#ifndef WORDS_BIGENDIAN
# include <arpa/inet.h>
#endif

#if PHP_MAJOR_VERSION >= 7
typedef size_t strsize_t;
#else
typedef int strsize_t;

# undef  RETURN_STRING
# define RETURN_STRING(s) \
    do { \
        RETVAL_STRING((s), 1); \
        return; \
    } while(0)
#endif

const zend_function_entry highwayhash_functions[] = {
    PHP_FE(highway_hash, NULL)
    PHP_FE(highway_hash32, NULL)
#ifdef PHP_FE_END
    PHP_FE_END
#else
    { NULL, NULL, NULL }
#endif
};

/* {{{ highwayhash_module_entry
 */
zend_module_entry highwayhash_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "highwayhash",
    highwayhash_functions,
    PHP_MINIT(highwayhash),
    PHP_MSHUTDOWN(highwayhash),
    NULL,
    NULL,
    PHP_MINFO(highwayhash),
#if ZEND_MODULE_API_NO >= 20010901
    "1.0",
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SIPHASH
ZEND_GET_MODULE(highwayhash)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(highwayhash)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(highwayhash)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(highwayhash)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "highwayhash support", "enabled");
    php_info_print_table_end();
}
/* }}} */

PHP_FUNCTION(highway_hash)
{
    char     *key = NULL;
    char     *message = NULL;
    struct {
        uint64_t      hash;
        unsigned char eos;
    }         res;
    strsize_t key_size;
    strsize_t message_size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss",
                              &key, &key_size,
                              &message, &message_size) == FAILURE) {
        return;
    }
    if (key_size != 16) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Bad key length");
        RETURN_FALSE;
    }
    if (message_size < 0) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Empty message");
        RETURN_FALSE;
    }
    memset(&res, 0, sizeof res);
    res.hash = highwayhash((unsigned char *) key,
                   (const unsigned char *) message, (size_t) message_size);
#ifdef WORDS_BIGENDIAN
    res.hash = (((uint64_t) htonl((uint32_t) res.hash)) << 32) |
        htonl((uint32_t) (res.hash >> 32));
#endif

    RETURN_STRING((void *) &res);
}

PHP_FUNCTION(highway_hash32)
{
    char     *key = NULL;
    char     *message = NULL;
    uint64_t  hash;
    long      hash32;
    strsize_t key_size;
    strsize_t message_size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss",
                              &key, &key_size,
                              &message, &message_size) == FAILURE) {
        return;
    }
    if (key_size != 16) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Bad key length");
        RETURN_FALSE;
    }
    if (message_size < 0) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Empty message");
        RETURN_FALSE;
    }
    hash = highwayhash((unsigned char *) key,
                   (const unsigned char *) message, (size_t) message_size);
    hash32 = (long) (hash & 0xFFFFFFFF);

    RETURN_LONG(hash32);
}