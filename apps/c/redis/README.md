
# How to run?
- At ArceOS root directory, run `git submodule update --init --recursive` to fetch Redis source code.
- Then run `make A=apps/c/redis/ LOG=info FS=y NET=y ARCH=aarch64 SMP=4 run`

# How to run second?
## Rebuild
- Enter apps/c/redis, run `make clean`
- Return to ArceOS root directory, run `make clean A=apps/c/redis && make A=apps/c/redis/ LOG=info FS=y NET=y ARCH=aarch64 SMP=4 run`
## Or use full command 
  - aarch64:
    - `qemu-system-aarch64 -m 2G -smp 4 -cpu cortex-a72 -machine virt -kernel apps/c/redis//redis_qemu-virt-aarch64.bin -device virtio-blk-device,drive=disk0 -drive id=disk0,if=none,format=raw,file=disk.img -device virtio-net-device,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5555-:5555,hostfwd=udp::5555-:5555 -nographic`
  - x86_64
    - `qemu-system-x86_64 -m 2G -smp 4 -machine q35 -kernel apps/c/redis//redis_pc-x86.elf -device virtio-blk-pci,drive=disk0 -drive id=disk0,if=none,format=raw,file=disk.img -device virtio-net-pci,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5555-:5555,hostfwd=udp::5555-:5555 -nographic -cpu host -accel kvm`

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
- Extend disk.img size to 16G in `utils.mk`
  - `@dd if=/dev/zero of=$(1) bs=1M count=64` -> `@dd if=/dev/zero of=$(1) bs=1G count=16`
  - This seems to be something related to fatfs implementation: 
    - disk_size = 64MB -> file_size <= 512B
    - disk_size = 8GB -> file_size <= 4096B

# Some test result
## AARCH64
### SET and GET:
- Here test `SET` and `GET` throughput.(30 conns, 100k requests like `unikraft`)
- command: 
  - `redis-benchmark -p 5555 -n 100000 -q -t set -c 30`
  - `redis-benchmark -p 5555 -n 100000 -q -t get -c 30`
- 0630

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

- 0710(Extend disk size)
| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| SET | 100K | 30 | 1 | 12740.48 |
| | | | 2 | 13150.97 |
| | | | 3 | 13147.52 |
| | | | 4 | 12898.23 |
| | | | 5 | 12918.23 |
| GET | 100K | 30 | 1 | 13253.81 |
| | | | 2 | 14332.81 |
| | | | 3 | 14600.67 |
| | | | 4 | 13974.29 |
| | | | 5 | 14005.60 |

### Other tests, one round(0704)
- Do other tests. 
- Use `config set save""` to avoid rapidly saving.
- Use `-c 30`

| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| PING_INLINE | 100K | 30 | 1 | 12147.72 |
| INCR | 100K | 30 | 1 | 13097.58 |
| LPUSH | 100K | 30 | 1 | 12955.05 |
| RPUSH | 100K | 30 | 1 | 11339.15 |
| LPOP | 100K | 30 | 1 | 12611.93 |
| RPOP | 100K | 30 | 1 | 13106.16 |
| SADD | 100K | 30 | 1 | 12773.02 |
| HSET | 100K | 30 | 1 | 11531.37 |
| SPOP | 100K | 30 | 1 | 12918.23 |
| ZADD | 100K | 30 | 1 | 10462.44 |
| ZPOPMIN | 100K | 30 | 1 | 12817.23 |
| LRANGE_100 | 100K | 30 | 1 | 6462.45 |
| LRANGE_300 | 100K | 30 | 1 | 3318.84 |
| LRANGE_500 | 100K | 30 | 1 | 2522.13 |
| LRANGE_600 | 100K | 30 | 1 | 1877.30 |
| MSET | 100K | 30 | 1 | 8929.37 |

## X86_64
### SET and GET(0710)
- command: 
  - `redis-benchmark -p 5555 -n 100000 -q -t set -c 30`
  - `redis-benchmark -p 5555 -n 100000 -q -t get -c 30`

| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| SET | 100K | 30 | 1 | 30931.02 |
| | | | 2 | 32258.07 |
| | | | 3 | 30571.69 |
| | | | 4 | 33344.45 |
| | | | 5 | 31655.59 |
| GET | 100K | 30 | 1 | 33523.30 |
| | | | 2 | 33134.53 |
| | | | 3 | 30450.67 |
| | | | 4 | 33178.50 |
| | | | 5 | 32268.47 |

### Other tests(0710)

| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| PING_INLINE | 100K | 30 | 1 | 32992.41 |
| INCR | 100K | 30 | 1 | 32467.53 |
| LPUSH | 100K | 30 | 1 | 29815.14 |
| RPUSH | 100K | 30 | 1 | 30864.20 |
| LPOP | 100K | 30 | 1 | 34094.78 |
| RPOP | 100K | 30 | 1 | 31133.25 |
| SADD | 100K | 30 | 1 | 32948.93 |
| HSET | 100K | 30 | 1 | 31036.62 |
| SPOP | 100K | 30 | 1 | 32916.39 |
| ZADD | 100K | 30 | 1 | 30693.68 |
| ZPOPMIN | 100K | 30 | 1 | 31525.85 |
| LRANGE_100 | 100K | 30 | 1 | 22925.26 |
| LRANGE_300 | 100K | 30 | 1 | 7404.12 |
| LRANGE_500 | 100K | 30 | 1 | 9320.53 |
| LRANGE_600 | 100K | 30 | 1 | 7760.96 |
| MSET | 100K | 30 | 1 | 31269.54 |

- Comparing to local Redis server, approximately 5x gap
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

## Unikraft
### AARCH64:
- `redis-benchmark -h 172.44.0.2 -q -n 100000 -c 30`
- Separately: 
  ```
  SET: 13814.06 requests per second
  GET: 15297.54 requests per second
  ```
- The whole benchmark:
  ```
  PING_INLINE: 14369.88 requests per second
  PING_BULK: 13335.11 requests per second
  SET: 13650.01 requests per second
  GET: 12103.61 requests per second
  INCR: 13395.85 requests per second
  LPUSH: 10279.61 requests per second
  RPUSH: 12536.04 requests per second
  LPOP: 9541.07 requests per second
  RPOP: 12540.76 requests per second
  SADD: 11880.72 requests per second
  HSET: 12318.30 requests per second
  SPOP: 12235.41 requests per second
  ZADD: 12130.03 requests per second
  ZPOPMIN: 12223.45 requests per second
  LPUSH (needed to benchmark LRANGE): 11125.95 requests per second
  LRANGE_100 (first 100 elements): 6791.17 requests per second
  LRANGE_300 (first 300 elements): 3772.30 requests per second
  LRANGE_500 (first 450 elements): 2779.71 requests per second
  LRANGE_600 (first 600 elements): 2230.80 requests per second
  MSET (10 keys): 9215.74 requests per second
  ```
### X86_64
