
## in redis dir:
CC=aarch64-linux-musl-gcc CFLAGS="-nostdinc -I/home/yanjuguang/OS/arceos/ulib/c_libax/include" USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j >../../../../1.txt 2>&1