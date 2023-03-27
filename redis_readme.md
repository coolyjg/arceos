
## in redis dir:
CC=aarch64-linux-musl-gcc CFLAGS="-nostdinc -I/home/yanjuguang/OS/arceos/ulib/c_libax/include" USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j >