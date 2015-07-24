PHP_ARG_ENABLE(haha,
        [Whether to enable the "haha" extension],
        [  --enable-haha    Enable "haha" extension support])

if test $PHP_HAHA != "no"; then
    PHP_REQUIRE_CXX()
    PHP_ADD_LIBRARY(stdc++, 1, HAHA_SHARED_LIBADD)
    PHP_SUBST(HAHA_SHARED_LIBADD)
    PHP_NEW_EXTENSION(haha, haha.cc, $ext_shared)
fi

