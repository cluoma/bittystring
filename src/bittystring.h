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

typedef enum {
    BS_SUCCESS = 0,
    BS_FAIL
} bs_str_ret;

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
} bs_str_s;

/*
 * Creators
 */
bs_str_s * bstr_s_new();
bs_str_s * bstr_s_new_from_cstring(const char *cs, uint64_t len);
void bstr_s_init(bs_str_s *bs);
/*
 * Freers
 */
void bstr_s_free(bs_str_s *bs);
/*
 * Accessors
 */
uint64_t bstr_s_get_size(bs_str_s *bs);
uint64_t bstr_s_get_capacity(bs_str_s *bs);
const char * bstr_s_get_cstring(bs_str_s *bs);
/*
 * Modifiers
 */
int bstr_s_append_from_cstring(bs_str_s *bs, const char *cs, uint64_t len);

#endif //BITTYSTRING_BITTYSTRING_H
