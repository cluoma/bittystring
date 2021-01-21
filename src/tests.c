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

    return 0;
}
