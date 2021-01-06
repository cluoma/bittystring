# bittystring
A C string library with short-string optimization. Supports short string up to 23 characters (22 + null terminator).

# Examples

### Heap Allocate
```c
char *s = "Cool text";

bstr *bs = bstr_new();
bstr_append_cstring(bs, s, strlen(s));
printf("%s\n", bstr_cstring(bs));
bstr_free(bs);
```

### Stack Allocate
```c
char *s = "Cool text";

bstr bs;
bstr_init(&bs);
bstr_append_cstring(&bs, s, strlen(s));
printf("%s\n", bstr_cstring(&bs));
bstr_free_buf(&bs); // free not strictly necessary here because of short-string, but always a good idea
```
