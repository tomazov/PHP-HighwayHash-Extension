#ifndef PHP_HIGHWAYHASH_H
#define PHP_HIGHWAYHASH_H

#define PHP_HIGHWAYHASH_EXTNAME  "highwayhash"
#define PHP_HIGHWAYHASH_EXTVER   "1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

extern zend_module_entry highwayhash_module_entry;
#define phpext_highwayhash_ptr &highwayhash_module_entry;

PHP_FUNCTION(highway_hash);
PHP_FUNCTION(highway_hash32);

PHP_MINIT_FUNCTION(highwayhash);
PHP_MSHUTDOWN_FUNCTION(highwayhash);
PHP_MINFO_FUNCTION(highwayhash);

typedef struct {
        char *input;
} highway_hash;

typedef struct {
        char *input;
} highway_hash32;

#endif /* PHP_HIGHWAYHASH_H */