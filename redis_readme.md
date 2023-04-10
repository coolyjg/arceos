
## in redis dir:
CC=aarch64-linux-musl-gcc CFLAGS="-nostdinc -I/home/yanjuguang/OS/arceos/ulib/c_libax/include" USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j >../../../../1.txt 2>&1

REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds /home/yanjuguang/OS/arceos/ulib/c_libax/build_aarch64/libc.a /home/yanjuguang/OS/arceos/target/aarch64-unknown-none-softfloat/release/liblibax_bindings.a'

CC=aarch64-linux-musl-gcc USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds' CFLAGS="-static -no-pie -mno-outline-atomics" LDFLAGS="-static -no-pie" -j >../../../../11.txt 2>&1

CC=aarch64-linux-musl-gcc USE_JEMALLOC=no make V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds' CFLGAS+="-DAX_CONFIG_DEFAULT -DAX_CONFIG_ALLOC -DAX_CONFIG_PAGING -static -no-pie -fno-builtin -ffreestanding -nostdinc -fPIC -Wall -Iulib/c_libax/include -Iulib/c_libax/libax_bindings -O3 -static -no-pie -mno-outline-atomics" LDFLAGS+="-nostdlib -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds -static -no-pie" -j > ../../../../rr.txt 2>&1

make clean && rm -f src/.make-settings src/.make-prerequisites && make clean -C deps/fpconv/ && make clean -C deps/hiredis/ && make clean -C deps/hdr_histogram/ && make clean -C deps/lua/

## lua
CC=aarch64-linux-musl-gcc make generic CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-error=implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

## fpconv
CC=aarch64-linux-musl-gcc make CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-error=implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

## hdr_histogram
CC=aarch64-linux-musl-gcc make CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-error=implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

## hiredis
CC=aarch64-linux-musl-gcc make CFLAGS+='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -Wno-implicit-function-declaration -Wno-pedantic -Wno-strict-prototypes -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' -j

