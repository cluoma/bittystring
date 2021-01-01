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
    assert(strcmp(bstr_cstring((X)), (Y)) == 0);

int
main()
{
    bstr *bs;
    /*
     * Short string
     */
    char * cool_text = "Some really cool text!";

    // Create and append from cstring
    bs = bstr_new();
    bstr_append_from_cstring(bs, cool_text, strlen(cool_text));
    BASIC_ASSERT(bs, cool_text);
    bstr_free(bs);

    // Create from cstring
    bs = bstr_new_from_cstring(cool_text, strlen(cool_text));
    BASIC_ASSERT(bs, cool_text);
    bstr_free(bs);

    // Create and append from printf
    bs = bstr_new();
    bstr_append_from_printf(bs, "%s", cool_text);
    BASIC_ASSERT(bs, cool_text);
    bstr_free(bs);

    /*
     * Long string
     */
    cool_text = "Some really cool text!Some really cool text!";

    // Create and append from cstring
    bs = bstr_new();
    bstr_append_from_cstring(bs, cool_text, strlen(cool_text));
    BASIC_ASSERT(bs, cool_text);
    bstr_free(bs);

    // Create from cstring
    bs = bstr_new_from_cstring(cool_text, strlen(cool_text));
    BASIC_ASSERT(bs, cool_text);
    bstr_free(bs);

    // Create and append from printf
    bs = bstr_new();
    bstr_append_from_printf(bs, "%s", cool_text);
    BASIC_ASSERT(bs, cool_text);
    bstr_free(bs);



    return 0;
}