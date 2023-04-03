REDIS_PATH := $(PWD)/redis
AX_ROOT := $(PWD)/../../../../arceos
REDIS_CFLAGS_S := '-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I$(AX_ROOT)/ulib/c_libax/include'
CC := aarch64-linux-musl-gcc

all:
	rm -f $(REDIS_PATH)/src/Makefile
	cp $(PWD)/redis_src_makefile $(REDIS_PATH)/src/Makefile
	CC=$(CC) USE_JEMALLOC=no $(MAKE) -C $(REDIS_PATH) V=1 REDIS_CFLAGS=$(REDIS_CFLAGS_S) -j

clean:
	$(MAKE) -C $(REDIS_PATH) clean
	$(MAKE) -C $(REDIS_PATH)/deps/fpconv/ clean
	$(MAKE) -C $(REDIS_PATH)/deps/hdr_histogram/ clean
	$(MAKE) -C $(REDIS_PATH)/deps/hiredis/ clean
	$(MAKE) -C $(REDIS_PATH)/deps/lua/src/ clean
	rm -f redis-server.o
	rm -f redis/src/redis-server.o

.PHONY: all