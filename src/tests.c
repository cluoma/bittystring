//
// Created by colin on 2020-10-29.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include "bittystring.h"

int
main()
{
    bstr *bs = bstr_new();

    char * cool_text = "Some really cool text!";
    printf("test string: %s (%lu chars)\n", cool_text, strlen(cool_text));

    for (int i = 0; i < 100000; i++)
    {
        bstr_append_from_cstring(bs, cool_text, strlen(cool_text));
    }
//    assert(strcmp("Some really cool text!", bstr_cstring(bs)) == 0);

    printf("buffer size: %" PRIu64 "\n", bstr_capacity(bs));
    printf("string length: %" PRIu64 "\n", bstr_size(bs));
    printf("NULL char?: '%d'\n", *(bstr_cstring(bs) + bstr_size(bs)));

//    int x = snprintf(NULL, 0, "%d", 123);
//    printf("%d\n", x);

    int x = bstr_append_from_cstring(bs, "aa", 0x7FFFFFFFFFFFFFFF);
    printf("Return int (%d) string: %s\n", x, bstr_error_string(x));

    bstr_free(bs);

//    /*
//     * Short string variant
//     */
//    bstr * bss = bstr_new_s();
//
//    for (int i = 0; i < 100; i++)
//    {
//        bstr_append_from_cstring(bss, "a", 1);
//        if (i >= 22)
//            printf("string: %s\n", bss->buf);
//    }
//
//    bstr_free(bss);

    return 0;
}