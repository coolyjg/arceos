
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
- Extend disk.img size to 1G in `utils.mk`
  - `@dd if=/dev/zero of=$(1) bs=1M count=64` -> `@dd if=/dev/zero of=$(1) bs=1M count=1024`

# Some test result
## 0630(test for 5 rounds):
- Here test `SET` and `GET` throughput.(30 conns, 100k requests like `unikraft`)
- command: 
  - `redis-benchmark -p 5555 -n 100000 -q -t set -c 30`
  - `redis-benchmark -p 5555 -n 100000 -q -t get -c 30`

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

## 0704(other tests, 1 round)
- Do other tests. (`LPUSH` and `RPUSH` has unkown bug when finishing, and so does `LRANGE_*`)

| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| PING_INLINE | 100K | 30 | 1 | 12147.72 |
| INCR | 100K | 30 | 1 | 13097.58 |
| LPUSH | 100K | 30 | 1 | 10866.02 |
| RPUSH | 100K | 30 | 1 | 11339.15 |
| LPOP | 100K | 30 | 1 | 12611.93 |
| RPOP | 100K | 30 | 1 | 13106.16 |
| SADD | 100K | 30 | 1 | 12773.02 |
| HSET | 100K | 30 | 1 | 11531.37 |
| SPOP | 100K | 30 | 1 | 12918.23 |
| ZADD | 100K | 30 | 1 | 10462.44 |
| ZPOPMIN | 100K | 30 | 1 | 12817.23 |
| *LRANGE_100 | 100K | 30 | 1 | 5840.78 |
| *LRANGE_300 | 100K | 30 | 1 | 3269.79 |
| *LRANGE_500 | 100K | 30 | 1 | 2412.89 |
| *LRANGE_600 | 100K | 30 | 1 | 1877.30 |
| MSET | 100K | 30 | 1 | 8929.37 |

- Comparing to local Redis server, approximately 10x gap
```
PING_INLINE: 176056.33 requests per second
PING_BULK: 173611.12 requests per second
SET: 175131.36 requests per second
GET: 174825.17 requests per second
INCR: 177304.97 requests per second
LPUSH: 176678.45 requests per second
RPUSH: 176056.33 requests per second
LPOP: 178253.12 requests per second
RPOP: 176678.45 requests per second
SADD: 175746.92 requests per second
HSET: 176991.16 requests per second
SPOP: 176991.16 requests per second
ZADD: 177619.89 requests per second
ZPOPMIN: 176056.33 requests per second
LPUSH (needed to benchmark LRANGE): 178253.12 requests per second
LRANGE_100 (first 100 elements): 113895.21 requests per second
LRANGE_300 (first 300 elements): 50942.43 requests per second
LRANGE_500 (first 450 elements): 35186.49 requests per second
LRANGE_600 (first 600 elements): 28320.59 requests per second
MSET (10 keys): 183150.19 requests per second
```
