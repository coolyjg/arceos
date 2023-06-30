
# How to run?
- At ArceOS root directory, run `git submodule update --init --recursive` to fetch Redis source code.
- Then run `make A=apps/c/redis/ LOG=info FS=y NET=y ARCH=aarch64 SMP=4 run`

# How to run second?
## Rebuild
- Enter apps/c/redis, run `make clean`
- Return to ArceOS root directory, run `make clean A=apps/c/redis && make A=apps/c/redis/ LOG=info FS=y NET=y ARCH=aarch64 SMP=4 run`
## Or use full command 
  - `qemu-system-aarch64 -m 2G -smp 4 -cpu cortex-a72 -machine virt -kernel apps/c/redis//redis_qemu-virt-aarch64.bin -device virtio-blk-device,drive=disk0 -drive id=disk0,if=none,format=raw,file=disk.img -device virtio-net-device,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5555-:5555,hostfwd=udp::5555-:5555 -nographic`

# How to test?
- Use `redis-cli -p 5555` to connect to redis-server, and enjoy ArceOS-Redis world!
- Use `redis-benchmark -p 5555` and other optional parameters to run the benchmark.
    - Like: `redis-benchmark -p 5555 -n 5 -q -c 10`, this command issues 5 requests for each commands (like `set`, `get`, etc.), with 10 concurrency.
    - `LRANGE_xxx` test may fail because of running out of memory(Follow notes 4, 5). 

# Notes
- Only test "aarch64".
- Must use `SMP=xxx`.
- Must run `make clean`, this may be changed later.
- Enlarge memory size in `qemu.mk` and `qemu-virt-aarch64.toml` to 2G to support big operation number
- Extend fd number to 4096, and cancel corresponed checks in flatten_objects. 

# Some test result
## 0630(test for 5 rounds):

| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| SET | 100K | 30 | 1 | 11921.79 |
| | | | 2 | 11873.66 |
| | | | 3 | 11499.54 |
| | | | 4 | 12001.92 |
| | | | 5 | 11419.44 |
| GET | 100K | 30 | 1 | 13002.21 |
| | | | 2 | 12642.23 |
| | | | 3 | 13674.28 |
| | | | 4 | 12987.01 |
| | | | 5 | 12853.47 |
