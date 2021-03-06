//
// Created by colin on 2020-10-29.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include "bittystring.h"

#define BASIC_ASSERT(X, Y) \
    assert(bstr_size((X)) == strlen((Y))); \
    assert(strlen(bstr_cstring((X))) == strlen((Y))); \
    assert(strcmp(bstr_cstring((X)), (Y)) == 0)

int
main()
{
    bstr *bs;
    char * cool_text_small = "Some really cool text!";
    char * cool_text_big = "Some really cool text!Some really cool text!";
    char * cool_text_big_abc = "Some really cool text!Some really cool text!abc";
    char * cool_text_big_cba = "cbaSome really cool text!Some really cool text!";


    /*
     * Short string
     */
    // Create and append from cstring
    bs = bstr_new();
    bstr_append_cstring(bs, cool_text_small, strlen(cool_text_small));
    BASIC_ASSERT(bs, cool_text_small);
    bstr_free(bs);

    // Create and prepend from cstring
    bs = bstr_new();
    bstr_prepend_cstring(bs, cool_text_small, strlen(cool_text_small));
    BASIC_ASSERT(bs, cool_text_small);
    bstr_free(bs);

    // Create from cstring
    bs = bstr_new_from_cstring(cool_text_small, strlen(cool_text_small));
    BASIC_ASSERT(bs, cool_text_small);
    bstr_free(bs);

    // Create and append from printf
    bs = bstr_new();
    bstr_append_printf(bs, "%s", cool_text_small);
    BASIC_ASSERT(bs, cool_text_small);
    bstr_free(bs);

    // Create and prepend from printf
    bs = bstr_new();
    bstr_prepend_printf(bs, "%s", cool_text_small);
    BASIC_ASSERT(bs, cool_text_small);
    bstr_free(bs);

    // Create and append from char
    bs = bstr_new();
    bstr_append_char(bs, 'a');
    bstr_append_char(bs, 'b');
    bstr_append_char(bs, 'c');
    BASIC_ASSERT(bs, "abc");
    bstr_free(bs);

    // Create and prepend from char
    bs = bstr_new();
    bstr_prepend_char(bs, 'a');
    bstr_prepend_char(bs, 'b');
    bstr_prepend_char(bs, 'c');
    BASIC_ASSERT(bs, "cba");
    bstr_free(bs);


    /*
     * Long string
     */
    // Create and append from cstring
    bs = bstr_new();
    bstr_append_cstring(bs, cool_text_big, strlen(cool_text_big));
    BASIC_ASSERT(bs, cool_text_big);
    bstr_free(bs);

    // Create and prepend from cstring
    bs = bstr_new();
    bstr_prepend_cstring(bs, cool_text_big, strlen(cool_text_big));
    BASIC_ASSERT(bs, cool_text_big);
    bstr_free(bs);

    // Create from cstring
    bs = bstr_new_from_cstring(cool_text_big, strlen(cool_text_big));
    BASIC_ASSERT(bs, cool_text_big);
    bstr_free(bs);

    // Create and append from printf
    bs = bstr_new();
    bstr_append_printf(bs, "%s", cool_text_big);
    BASIC_ASSERT(bs, cool_text_big);
    bstr_free(bs);

    // Create and prepend from printf
    bs = bstr_new();
    bstr_prepend_printf(bs, "%s", cool_text_big);
    BASIC_ASSERT(bs, cool_text_big);
    bstr_free(bs);

    // Create and append from char
    bs = bstr_new();
    bstr_append_cstring(bs, cool_text_big, strlen(cool_text_big));
    bstr_append_char(bs, 'a');
    bstr_append_char(bs, 'b');
    bstr_append_char(bs, 'c');
    BASIC_ASSERT(bs, cool_text_big_abc);
    bstr_free(bs);

    // Create and prepend from char
    bs = bstr_new();
    bstr_prepend_cstring(bs, cool_text_big, strlen(cool_text_big));
    bstr_prepend_char(bs, 'a');
    bstr_prepend_char(bs, 'b');
    bstr_prepend_char(bs, 'c');
    BASIC_ASSERT(bs, cool_text_big_cba);
    bstr_free(bs);

    /*
     * Stack Allocate
     */
    bstr bstack;
    bstr_init(&bstack);
    bstr_append_printf(&bstack, "%s", cool_text_small);
    BASIC_ASSERT(&bstack, cool_text_small);
    bstr_free_contents(&bstack);

    bstr_init(&bstack);
    bstr_append_printf(&bstack, "%s", cool_text_big);
    BASIC_ASSERT(&bstack, cool_text_big);
    bstr_free_contents(&bstack);

    /*
     * Const str macro
     */
    bs = bstr_new();
    bstr_append_cstring(bs, bstr_const_str("hello _world!"));
    bstr_prepend_cstring(bs, bstr_const_str("BYE!"));
    BASIC_ASSERT(bs, "BYE!hello _world!");
    bstr_free(bs);

    /*
     * Move
     */
    char *qq = malloc(35);
    qq[0] = '\0';
    strcat(qq, "l;kajsdfdiowien;knvf;dsi12345");
    bs = bstr_new_move(qq, strlen(qq));
    printf("aa: %s\n", bstr_cstring(bs));
    bstr_append_cstring_nolen(bs, "\nsometexttoaskjlfiojisdjflskdjflsdf666");
    printf("aa: %s\n", bstr_cstring(bs));
    qq = malloc(35);
    qq[0] = '\0';
    strcat(qq, "something super cool and sneaky");
    bstr_replace_move(bs, qq, strlen(qq));
    printf("aa: %s\n", bstr_cstring(bs));
    bstr_free(bs);

    return 0;
}
