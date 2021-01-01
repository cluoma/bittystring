//
// bittystring.c
//
// Created by colin on 2020-10-29.
//

#include "bittystring.h"

#define BS_MALLOC(X) malloc(X)
#define BS_REALLOC(X, Y) realloc((X), (Y))
#define BS_FREE(X) free(X)

#define BSTR_S_IS_SSO(X) ((X)->short_size >> 7)
#define SSO_SET_MASK 0x80
#define SSO_UNSET_MASK 0x7F
#define BSTR_S_SET_SSO(X) ((X)->short_size |= SSO_SET_MASK)
#define BSTR_S_UNSET_SSO(X) ((X)->short_size &= SSO_UNSET_MASK)
#define BSTR_S_SSO_SIZE(X) ((X)->short_size & SSO_UNSET_MASK)

uint64_t
next_power2(uint64_t x)
// Returns the smallest power of 2 greater than x
// GCC builtin is undefined for 0. Don't use this function for 0.
{
    // if (x == 0) return 0;
#ifdef __GNUC__
//    printf("unsigned long long: %llu bytes\n", (uint64_t)sizeof(unsigned long long)*8);
//    printf("x: %llu\n", x);
//    printf("builtin of x: %d\n", __builtin_clzll(x));
//    printf("bytes minus builtin: %llu\n", sizeof(unsigned long long)*8 - (uint64_t)__builtin_clzll(x));
//    printf("next pow 2: %llu\n", (uint64_t)1 << ((sizeof(unsigned long long)*8) - __builtin_clzll(x)));
    return (uint64_t)1 << ((sizeof(unsigned long long)*8) - __builtin_clzll(x));
#else
    uint32_t power = 0;
    while (x > 0)
    {
        x >>= 1;
        power += 1;
    }
    return 1 << power;
#endif
}

void
bstr_s_set_sso_size(bs_str_s *bs, uint8_t size)
{
    bs->short_size = size;
    BSTR_S_SET_SSO(bs);
}

uint64_t
bstr_s_get_size(bs_str_s *bs)
{
    if (BSTR_S_IS_SSO(bs))
    {
        return (uint64_t)BSTR_S_SSO_SIZE(bs);
    }
    else
    {
        return bs->size;
    }
}

uint64_t
bstr_s_get_capacity(bs_str_s *bs)
{
    if (BSTR_S_IS_SSO(bs))
    {
        return (uint64_t)BS_MAX_SSO_CAPACITY;
    }
    else
    {
        return bs->capacity;
    }
}

const char *
bstr_s_get_cstring(bs_str_s *bs)
{
    if (BSTR_S_IS_SSO(bs))
    {
        return bs->short_str;
    }
    else
    {
        return bs->buf;
    }
}

bs_str_s *
bstr_s_new()
{
    bs_str_s *bs = BS_MALLOC(sizeof(bs_str_s));
    if (bs == NULL)
        return NULL;

    bstr_s_init(bs);

    return bs;
}

bs_str_s *
bstr_s_new_from_cstring(const char *cs, uint64_t len)
{
    bs_str_s *bs = bstr_s_new();
    if (bs == NULL)
        return NULL;

    if (bstr_s_append_from_cstring(bs, cs, len) != BS_SUCCESS)
    {
        bstr_s_free(bs);
        return NULL;
    }

    return bs;
}

void
bstr_s_init(bs_str_s *bs)
{
    memset(bs, 0, 24);
    BSTR_S_SET_SSO(bs);
    bstr_s_set_sso_size(bs, 0);
}

int
bstr_s_resize_buffer(bs_str_s *bs, uint64_t new_capacity)
{
    char * new_buf = BS_REALLOC(bs->buf, new_capacity);
    if (new_buf == NULL)
    {
        return BS_FAIL;
    }

    bs->buf = new_buf;
    bs->capacity = new_capacity;
    return BS_SUCCESS;
}

uint64_t
bstr_s_next_capacity(uint64_t size)
{
    uint64_t capacity = next_power2(size);
    if (capacity > BS_MAX_CAPACITY)
        capacity = BS_MAX_CAPACITY;
    return capacity;
}

int
bstr_s_expand(bs_str_s *bs, uint64_t len)
{
#ifdef DEBUG
    if (BSTR_S_IS_SSO(bs))
        printf("original size: %" PRIu8 "\n", BSTR_S_SSO_SIZE(bs));
    else
        printf("original size: %" PRIu64 "\n", bs->size);
#endif
    if (BSTR_S_IS_SSO(bs))
    {
        uint8_t sso_size = BSTR_S_SSO_SIZE(bs);
        if (sso_size + len + 1 > BS_MAX_SSO_CAPACITY)
        {
            uint64_t initial_capacity = bstr_s_next_capacity(sso_size + len + 1);
            if (sso_size + len + 1 > initial_capacity)
            {
                fprintf(stderr, "Request length is too large\n");
                return BS_FAIL;
            }

            char * buf = BS_MALLOC(initial_capacity);
            if (!buf)
            {
                fprintf(stderr, "Failed to allocate buffer\n");
                return BS_FAIL;
            }
            memcpy(buf, bs->short_str, sso_size);
            buf[sso_size] = '\0';
            bs->buf = buf;
            bs->size = sso_size;
            bs->capacity = initial_capacity;
        }
    }
    else
    {
        if (bs->size + len + 1 > bs->capacity)
        {
            uint64_t next_capacity = bstr_s_next_capacity(bs->size + len + 1);
            if (bs->size + len + 1 > next_capacity)
            {
                fprintf(stderr, "Request length is too large\n");
                return BS_FAIL;
            }
            if (bstr_s_resize_buffer(bs, next_capacity) != BS_SUCCESS)
            {
                fprintf(stderr, "Failed to expand buffer\n");
                return BS_FAIL;
            }
        }
    }
#ifdef DEBUG
    if (BSTR_S_IS_SSO(bs))
        printf("new size: %" PRIu8 "\n", BSTR_S_SSO_SIZE(bs));
    else
        printf("new size: %" PRIu64 "\n", bs->size);
#endif
    return BS_SUCCESS;
}

int
bstr_s_append_from_cstring(bs_str_s *bs, const char *cs, uint64_t len)
{
#ifdef DEBUG
    for (int i = 0; i < 24; i++)
    {
        printf("[%d]: %" PRIu8 "\n", i, bs->short_str[i]);
    }
    printf("[23]: %" PRIu64 "\n", bs->capacity);
#endif
    int r = bstr_s_expand(bs, len);
    if (r != BS_SUCCESS)
        return BS_FAIL;

    if (BSTR_S_IS_SSO(bs))
    {
        uint8_t sso_size = BSTR_S_SSO_SIZE(bs);
        memcpy(bs->short_str + sso_size, cs, len);
        bs->short_str[sso_size + len] = '\0';
        bstr_s_set_sso_size(bs, sso_size+len);
    }
    else
    {
        memcpy(bs->buf + bs->size, cs, len);
        bs->buf[bs->size + len] = '\0';
        bs->size += len;
    }

    return BS_SUCCESS;
}

void
bstr_s_free(bs_str_s *bs)
{
    if (!BSTR_S_IS_SSO(bs) && bs->buf)
        BS_FREE(bs->buf);

    BS_FREE(bs);
}