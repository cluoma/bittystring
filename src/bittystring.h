//
// bittystring.h
//
// Created by colin on 2020-10-29.
//

#ifndef BITTYSTRING_BITTYSTRING_H
#define BITTYSTRING_BITTYSTRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#define BS_MAX_CAPACITY 0x7FFFFFFFFFFFFFFF
#define BS_MAX_SSO_CAPACITY 23

//typedef enum {
//    BS_SUCCESS = 0,
//    BS_FAIL
//} bstr_ret_val;

#define RETURN_CODES    C(BS_SUCCESS, "All good\n")             \
                        C(BS_FAIL, "Function failed\n")
#define C(k, v) k,
typedef enum { RETURN_CODES } bstr_ret_val;
#undef C

typedef union
{
    struct
    {
        char* buf;
        uint64_t size;  // not including null terminator
        uint64_t capacity;
    };
    struct
    {
        char short_str[24-1];
        uint8_t short_size;  // not including null terminator
    };
} bstr;

/*
 * Creators
 */
bstr * bstr_new();
bstr * bstr_new_from_cstring(const char *cs, uint64_t len);
void bstr_init(bstr *bs);
const char * bstr_error_string(bstr_ret_val r);
/*
 * Freers
 */
void bstr_free(bstr *bs);
void bstr_free_buf(bstr *bs);
/*
 * Accessors
 */
uint64_t bstr_size(bstr *bs);
uint64_t bstr_capacity(bstr *bs);
const char * bstr_cstring(bstr *bs);
/*
 * Modifiers
 */
int bstr_append_from_cstring(bstr *bs, const char *cs, uint64_t len);

#endif //BITTYSTRING_BITTYSTRING_H
