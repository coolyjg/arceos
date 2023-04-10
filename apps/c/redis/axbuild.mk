redis-objs := adlist.o quicklist.o ae.o anet.o dict.o server.o sds.o zmalloc.o lzf_c.o lzf_d.o pqsort.o zipmap.o sha1.o ziplist.o release.o networking.o util.o object.o db.o replication.o rdb.o t_string.o t_list.o t_set.o t_zset.o t_hash.o config.o aof.o pubsub.o multi.o debug.o sort.o intset.o syncio.o cluster.o crc16.o endianconv.o slowlog.o eval.o bio.o rio.o rand.o memtest.o syscheck.o crcspeed.o crc64.o bitops.o sentinel.o notify.o setproctitle.o blocked.o hyperloglog.o latency.o sparkline.o redis-check-rdb.o redis-check-aof.o geo.o lazyfree.o module.o evict.o expire.o geohash.o geohash_helper.o childinfo.o defrag.o siphash.o rax.o t_stream.o listpack.o localtime.o lolwut.o lolwut5.o lolwut6.o acl.o tracking.o socket.o tls.o sha256.o timeout.o setcpuaffinity.o monotonic.o mt19937-64.o resp_parser.o call_reply.o script_lua.o script.o functions.o function_lua.o commands.o strl.o connection.o unix.o logreqres.o
pre-objs := $(addprefix $(APP)/redis/src/, $(redis-objs))

app-objs := redis_server.o libhiredis.a liblua.a libhdrhistogram.a libfpconv.a

hiredis-objs = alloc.o net.o hiredis.o sds.o async.o read.o sockcompat.o
hiredis-objs-pre = $(addprefix $(APP)/redis/deps/hiredis/, $(hiredis-objs))

lua-objs = lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o strbuf.o fpconv.o lauxlib.o lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o lstrlib.o loadlib.o linit.o lua_cjson.o lua_struct.o lua_cmsgpack.o lua_bit.o
lua-objs-pre = $(addprefix $(APP)/redis/deps/lua/src/, $(lua-objs))

hdr-objs = $(APP)/redis/deps/hdr_histogram/hdr_histogram.o

fpconv-objs = $(APP)/redis/deps/fpconv/fpconv_dtoa.o

AR = aarch64-linux-musl-ar

$(pre-objs):
	@echo "--------pre-building redis--------"
	rm -f $(APP)/redis/src/Makefile
	rm -f $(APP)/redis/deps/fpconv/Makefile
	rm -f $(APP)/redis/deps/hdr_histogram/Makefile
	rm -f $(APP)/redis/deps/hiredis/Makefile
	rm -f $(APP)/redis/deps/lua/src/Makefile
	cp $(APP)/redis_src_makefile $(APP)/redis/src/Makefile
	cp $(APP)/redis_fpconv_makefile $(APP)/redis/deps/fpconv/Makefile
	cp $(APP)/redis_hdr_makefile $(APP)/redis/deps/hdr_histogram/Makefile
	cp $(APP)/redis_hiredis_makefile $(APP)/redis/deps/hiredis/Makefile
	cp $(APP)/redis_lua_makefile $(APP)/redis/deps/lua/src/Makefile
	cd $(APP)/redis && CC=aarch64-linux-musl-gcc USE_JEMALLOC=no $(MAKE) V=1 REDIS_CFLAGS='-Werror -Wno-unused-parameter -Wno-int-conversion -Wno-restrict -Wno-format -Wno-unused-variable -nostdinc -fno-builtin -I/home/yanjuguang/OS/arceos/ulib/c_libax/include' REDIS_LDFLAGS+='-nostdlib -static -T/home/yanjuguang/OS/arceos/modules/axhal/linker_aarch64.lds' CFLAGS="-static -no-pie -mno-outline-atomics" LDFLAGS="-static -no-pie"

$(APP)/redis_server.o: $(pre-objs)
	aarch64-linux-musl-ld -r -o $@ $^

$(APP)/libhiredis.a: $(hiredis-objs-pre)
	$(AR) rcs $@ $^

$(APP)/liblua.a: $(lua-objs-pre)
	$(AR) rcu $@ $^

$(APP)/libhdrhistogram.a: $(hdr-objs)
	$(AR) rcs $@ $^

$(APP)/libfpconv.a: $(fpconv-objs)
	$(AR) rcs $@ $^