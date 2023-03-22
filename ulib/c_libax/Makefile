# Arguments
ARCH ?= riscv64
MODE ?= release
FEATURES ?=
APP ?=
CROSS_COMPILE ?= $(ARCH)-linux-musl-

ifeq ($(ARCH), riscv64)
  target := riscv64gc-unknown-none-elf
else ifeq ($(ARCH), aarch64)
  target := aarch64-unknown-none-softfloat
else
  $(error "ARCH" must be "riscv64" or "aarch64")
endif

# Variables for Rust
app_path := ../../apps/c/$(APP)
rust_lib_name := libax_bindings
rust_build_path := ../../target/$(target)/$(MODE)
rust_lib := $(rust_build_path)/lib$(rust_lib_name).a

features := $(FEATURES)
ifneq (,$(wildcard $(app_path)/features.txt))	# check features.txt exists
  features += $(addprefix $(rust_lib_name)/,$(shell cat $(app_path)/features.txt))
endif

crago_build_args := --no-default-features --features "$(features)" --target $(target) -Zbuild-std=core,alloc -Zbuild-std-features=compiler-builtins-mem
ifeq ($(MODE), release)
  crago_build_args += --release
endif

# Variables for C
src_dir := src
obj_dir := build_$(ARCH)
inc_dir := include
hdr_dir := $(app_path)/deps/hdr_histogram
lua_dir := $(app_path)/deps/lua/src
hiredis_dir := $(app_path)/deps/hiredis
line_dir := $(app_path)/deps/line_dir
fpconv_dir := $(app_path)/deps/fpconv
c_lib := $(obj_dir)/libc.a
REDIS_SERVER_OBJ = $(addprefix $(app_path)/src/, adlist.o quicklist.o ae.o anet.o dict.o server.o sds.o zmalloc.o lzf_c.o lzf_d.o pqsort.o zipmap.o sha1.o ziplist.o release.o networking.o util.o object.o db.o replication.o rdb.o t_string.o t_list.o t_set.o t_zset.o t_hash.o config.o aof.o pubsub.o multi.o debug.o sort.o intset.o syncio.o cluster.o crc16.o endianconv.o slowlog.o eval.o bio.o rio.o rand.o memtest.o syscheck.o crcspeed.o crc64.o bitops.o sentinel.o notify.o setproctitle.o blocked.o hyperloglog.o latency.o sparkline.o redis-check-rdb.o redis-check-aof.o geo.o lazyfree.o module.o evict.o expire.o geohash.o geohash_helper.o childinfo.o defrag.o siphash.o rax.o t_stream.o listpack.o localtime.o lolwut.o lolwut5.o lolwut6.o acl.o tracking.o socket.o tls.o sha256.o timeout.o setcpuaffinity.o monotonic.o mt19937-64.o resp_parser.o call_reply.o script_lua.o script.o functions.o function_lua.o strl.o connection.o unix.o logreqres.o)
ALL_SOURCES = $(sort $(patsubst %.o,%.c,$(REDIS_SERVER_OBJ)))
redis_lib := $(obj_dir)/redis_lib.o

all_src := $(wildcard $(src_dir)/*.c)
all_obj := $(patsubst $(src_dir)/%.c,$(obj_dir)/%.o,$(all_src))

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
AR := $(CROSS_COMPILE)ar
RANLIB := $(CROSS_COMPILE)ranlib
CFLAGS := -static -no-pie -fno-builtin -ffreestanding -nostdinc -Wall -I$(inc_dir) -I$(rust_lib_name)

ifeq ($(APP), redis)
  CFLAGS += -I$(hdr_dir) -I$(lua_dir) -I$(hiredis_dir) -I$(line_dir) -I$(fpconv_dir)
endif

LDFLAGS := -nostdlib -T../../modules/axhal/linker_$(ARCH).lds

ifeq ($(MODE), release)
  CFLAGS += -O3
endif

ifneq (,$(wildcard $(app_path)/features.txt))	# check features.txt exists
  CFLAGS += $(addprefix -D AX_CONFIG_,$(shell cat $(app_path)/features.txt | tr 'a-z' 'A-Z'))
endif

ifeq ($(ARCH), riscv64)
  CFLAGS += -march=rv64gc -mabi=lp64d -mcmodel=medany
else ifeq ($(ARCH), aarch64)
#   CFLAGS += -mgeneral-regs-only
endif

# Variables for app
app_package := arceos-$(APP)
app_src := $(app_path)/src/server.c
app_obj := $(rust_build_path)/$(app_package).o
# app_elf := $(rust_build_path)/$(app_package)

# Build commands
all: clean rust_lib c_lib app app_elf

rust_lib:
	@echo
	@echo Building rust static library $(rust_lib_name) ...
	cargo build $(crago_build_args) -p $(rust_lib_name)

c_lib: rust_lib $(obj_dir) $(c_lib)

$(obj_dir):
	@echo
	@echo Building C static library $(c_lib) ...
	mkdir -p $@

$(obj_dir)/%.o: $(src_dir)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(c_lib): $(all_obj)
	rm -f $@
	$(AR) rc $@ $(all_obj)
	$(RANLIB) $@

ifneq ($(APP),)
app: $(app_elf)

$(redis_lib): $(ALL_SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

$(app_obj): $(app_src)
# CFLAGS= LDFLAGS=  make -C $(app_path)
	$(CC) $(CFLAGS) -c -o $@ $<

app_elf: $(c_lib) $(rust_lib)
	@echo
	@echo Building app \"$(app_package)\" ...
# $(LD) $(LDFLAGS) $^ -o $@
	CFLAGS= LDFLAGS= make -C $(app_path)
else
app:
endif

clean:
	rm -rf build_*
	cargo clean -p $(rust_lib_name)

.PHONY: all c_lib rust_lib app clean
