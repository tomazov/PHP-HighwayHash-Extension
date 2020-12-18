dnl $Id$
dnl config.m4 for extension highwayhash

PHP_ARG_ENABLE(highwayhash,
    [Enable Google's HighwayHash methods],
    [  --enable-highwayhash           Enable HighwayHash support])

if test "$PHP_HIGHWAYHASH" != "no"; then
  PHP_NEW_EXTENSION(highwayhash, highwayhash-impl.c php_highwayhash.c, $ext_shared)
fi