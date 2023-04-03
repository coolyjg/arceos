REDIS_PATH := $(APP)/redis
# AX_ROOT := $(APP)/../../../arceos
AX_ROOT := $(PWD)
REDIS_CFLAGS_S := '-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I$(AX_ROOT)/ulib/c_libax/include'

# app-objs := redis-server.o $(REDIS_PATH)/src/deps/hiredis/libhiredis.a $(REDIS_PATH)/src/deps/lua/src/liblua.a $(REDIS_PATH)/src/deps/hdr_histogram/libhdrhistogram.a $(REDIS_PATH)/src/deps/fpconv/libfpconv.a

app-objs := redis-server.o

$(APP)/redis-server.o:
	rm -f $(REDIS_PATH)/src/Makefile
	cp $(REDIS_PATH)/../redis_src_makefile $(REDIS_PATH)/src/Makefile
#	$(MAKE) -C $(APP) all
	CC=$(CC) USE_JEMALLOC=no $(MAKE) -C $(REDIS_PATH) V=1 REDIS_CFLAGS=$(REDIS_CFLAGS_S) -j
	cp $(APP)/redis/src/redis-server.o $(APP)/redis-server.o

# $(REDIS_PATH)/src/deps/hiredis/libhiredis.a:

# $(REDIS_PATH)/src/deps/lua/src/liblua.a:

# $(REDIS_PATH)/src/deps/hdr_histogram/libhdrhistogram.a:

# $(REDIS_PATH)/src/deps/fpconv/libfpconv.a: