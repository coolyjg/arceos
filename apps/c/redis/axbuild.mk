REDIS_PATH := $(APP)/redis
# AX_ROOT := $(APP)/../../../arceos
# AX_ROOT := $(PWD)
# REDIS_CFLAGS_S := '-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I$(AX_ROOT)/ulib/c_libax/include'

# app-objs := redis-server.o $(REDIS_PATH)/src/deps/hiredis/libhiredis.a $(REDIS_PATH)/src/deps/lua/src/liblua.a $(REDIS_PATH)/src/deps/hdr_histogram/libhdrhistogram.a $(REDIS_PATH)/src/deps/fpconv/libfpconv.a

OBJS := adlist.o quicklist.o ae.o anet.o dict.o server.o sds.o zmalloc.o lzf_c.o lzf_d.o pqsort.o zipmap.o sha1.o ziplist.o release.o networking.o util.o object.o db.o replication.o rdb.o t_string.o t_list.o t_set.o t_zset.o t_hash.o config.o aof.o pubsub.o multi.o debug.o sort.o intset.o syncio.o cluster.o crc16.o endianconv.o slowlog.o eval.o bio.o rio.o rand.o memtest.o syscheck.o crcspeed.o crc64.o bitops.o sentinel.o notify.o setproctitle.o blocked.o hyperloglog.o latency.o sparkline.o redis-check-rdb.o redis-check-aof.o geo.o lazyfree.o module.o evict.o expire.o geohash.o geohash_helper.o childinfo.o defrag.o siphash.o rax.o t_stream.o listpack.o localtime.o lolwut.o lolwut5.o lolwut6.o acl.o tracking.o socket.o tls.o sha256.o timeout.o setcpuaffinity.o monotonic.o mt19937-64.o resp_parser.o call_reply.o script_lua.o script.o functions.o function_lua.o commands.o strl.o connection.o unix.o logreqres.o
ROBJS = $(addprefix $(APP)/redis/src/, $(OBJS))
RSRCS = $(patsubst %.o,%.c,$(ROBJS))

FLAGS := -I$(REDIS_PATH)/deps/hiredis -I$(REDIS_PATH)/deps/lua/src -I$(REDIS_PATH)/deps/hdr_histogram -I$(REDIS_PATH)deps/fpconv

app-objs := $(OBJS)

$(APP)/$(OBJS):
	rm -f $(REDIS_PATH)/src/Makefile
	cp $(REDIS_PATH)/../redis_src_makefile $(REDIS_PATH)/src/Makefile
	$(MAKE) -C $(APP)/redis/
	cp $(ROBJS) $(APP)/
#	$(CC) $(CFLAGS) $(FLAGS) -o $@ -c $<

# pre_make:
# 	rm -f $(REDIS_PATH)/src/Makefile
# 	cp $(REDIS_PATH)/../redis_src_makefile $(REDIS_PATH)/src/Makefile
# 	$(MAKE) -C $(APP)/redis/

# $(OBJS): pre_make

# $(APP)/redis.a: pre_make
# 	cp $(APP)/redis/src/redis.a $(APP)/redis.a
# 	rm -f $(REDIS_PATH)/src/Makefile
# 	cp $(REDIS_PATH)/../redis_src_makefile $(REDIS_PATH)/src/Makefile
# 	$(MAKE) -C $(APP)/redis/
#	$(MAKE) -C $(APP) all
#	CC=$(CC) USE_JEMALLOC=no $(MAKE) -C $(REDIS_PATH) V=1 REDIS_CFLAGS=$(REDIS_CFLAGS_S) -j
# 	cp $(APP)/redis/src/redis.a $(APP)/redis.a

# $(REDIS_PATH)/src/deps/hiredis/libhiredis.a:

# $(REDIS_PATH)/src/deps/lua/src/liblua.a:

# $(REDIS_PATH)/src/deps/hdr_histogram/libhdrhistogram.a:

# $(REDIS_PATH)/src/deps/fpconv/libfpconv.a: