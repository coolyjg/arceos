
## in redis dir:
CC=aarch64-linux-musl-gcc CFLAGS="-nostdinc -I/home/yanjuguang/OS/arceos/ulib/c_libax/include" USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j >../../../../1.txt 2>&1

REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds /home/yanjuguang/OS/arceos/ulib/c_libax/build_aarch64/libc.a /home/yanjuguang/OS/arceos/target/aarch64-unknown-none-softfloat/release/liblibax_bindings.a'

CC=aarch64-linux-musl-gcc USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds /home/yanjuguang/OS/arceos/ulib/c_libax/build_aarch64/libc.a /home/yanjuguang/OS/arceos/target/aarch64-unknown-none-softfloat/release/liblibax_bindings.a' CFLAGS="-static -no-pie" LDFLAGS="-static -no-pie" -j >../../../../1.txt 2>&1

CC=aarch64-linux-musl-gcc USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds' CFLAGS="-static -no-pie -mno-outline-atomics" LDFLAGS="-static -no-pie" -j >../../../../11.txt 2>&1

CC=aarch64-linux-musl-gcc make MALLOC=libc REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-expansion-to-defined -Wno-implicit-fallthrough -Wno-maybe-uninitialized -Wno-stringop-overflow -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds' CFLAGS="-static -no-pie -mno-outline-atomics" LDFLAGS="-static -no-pie" -j > 11.txt 2>&1

## lua
CC=aarch64-linux-musl-gcc make generic CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-error=implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

## fpconv
CC=aarch64-linux-musl-gcc make CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-error=implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

## hdr_histogram
CC=aarch64-linux-musl-gcc make CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-error=implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

## hiredis
CC=aarch64-linux-musl-gcc make CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

