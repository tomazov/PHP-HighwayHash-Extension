HighwayHash for PHP
===============

Working on porting Google's HighwayHash (https://github.com/google/highwayhash/) to its own PHP PECL Extension.

> HighwayHash is based on a new way of mixing inputs with just a few AVX-2 multiply and permute instructions. We are hopeful that the result is a cryptographically strong pseudorandom function, but new cryptanalysis methods might be needed for analyzing this promising family of hash functions. HighwayHash is significantly faster than SipHash for all measured input sizes, with about 7 times higher throughput at 1 KiB.

Usage:

    highway_hash(key, message)

outputs `highway-2-4(key, message)` as a 8-byte string.

    highway_hash32(key, message)

truncates the value and outputs a 32-bit integer.

The `key` should be a 16 bytes string.

Installation
============

    $ phpize
    $ ./configure --enable-highwayhash
    $ make install

And add `extension=highwayhash.so` to your php.ini configuration file.

PHP 5.6+ and PHP 7.0+ are fully supported.
