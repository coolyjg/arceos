
# How to run?
- At ArceOS root directory, run `git submodule update --init --recursive` to fetch Redis source code.
- Then run 
  - `make A=apps/c/redis/ LOG=info BLK=y NET=y ARCH=aarch64 SMP=4 run`(for aarch64)
  - `make A=apps/c/redis/ LOG=info BLK=y NET=y ARCH=x86_64 SMP=4 run`(for x86_64)

# How to run secondly?
## Rebuild
- Enter apps/c/redis, run `make clean`
- Return to ArceOS root directory, run `make clean A=apps/c/redis && make A=apps/c/redis/ LOG=info BLK=y NET=y ARCH=aarch64 SMP=4 run`
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
- Use `SMP=xxx`.
- Must run `make clean`, this may be changed later.
- Enlarge memory size in `qemu.mk` and `qemu-virt-aarch64.toml` to 2G.
- Extend fd number to 4096, and comment out corresponding checks in `flatten_objects`. 

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

- 0714(Update net implementation, maximum: 2.9w(set))

| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| SET | 100K | 30 | 1 | 25713.55 |
| | | | 2 | 25246.15 |
| | | | 3 | 24968.79 |
| | | | 4 | 25018.76 |
| | | | 5 | 25348.54 |
| GET | 100K | 30 | 1 | 27917.37 |
| | | | 2 | 28360.75 |
| | | | 3 | 27525.46 |
| | | | 4 | 27901.79 |
| | | | 5 | 27495.19 |

### Other tests, one round
- Do other tests. 
- Use `config set save ""` to avoid rapidly saving.
- Use `-c 30`

- 0704

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

- 0714
```
PING_INLINE: 28768.70 requests per second
PING_BULK: 31347.96 requests per second
SET: 23185.72 requests per second
GET: 25700.33 requests per second
INCR: 25746.65 requests per second
LPUSH: 20416.50 requests per second
RPUSH: 20868.12 requests per second
LPOP: 20370.75 requests per second
RPOP: 19956.10 requests per second
SADD: 25361.40 requests per second
HSET: 21431.63 requests per second
SPOP: 25438.82 requests per second
ZADD: 23820.87 requests per second
ZPOPMIN: 26954.18 requests per second
LPUSH (needed to benchmark LRANGE): 26385.22 requests per second
LRANGE_100 (first 100 elements): 23912.00 requests per second
LRANGE_300 (first 300 elements): 22665.46 requests per second
LRANGE_500 (first 450 elements): 23369.95 requests per second
LRANGE_600 (first 600 elements): 22256.84 requests per second
MSET (10 keys): 18460.40 requests per second
```

## X86_64
### SET and GET
- command: 
  - `redis-benchmark -p 5555 -n 100000 -q -t set -c 30`
  - `redis-benchmark -p 5555 -n 100000 -q -t get -c 30`

- 0710

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

- 0714

| Operation | Op number | Concurrency | Round | Result(request per seconds) |
|-|-|-|-|-|
| SET | 100K | 30 | 1 | 105263.16 |
| | | | 2 | 105263.16 |
| | | | 3 | 103950.10 |
| | | | 4 | 107758.62 |
| | | | 5 | 105820.11 |
| GET | 100K | 30 | 1 | 103199.18 |
| | | | 2 | 104058.27 |
| | | | 3 | 99502.48 |
| | | | 4 | 106951.88 |
| | | | 5 | 105263.16 |

### Other tests

- 0710

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

- 0714

```
PING_INLINE: 111607.14 requests per second
PING_BULK: 102880.66 requests per second
SET: 80971.66 requests per second
GET: 103519.66 requests per second
INCR: 98425.20 requests per second
LPUSH: 70274.07 requests per second
RPUSH: 108108.11 requests per second
LPOP: 53561.86 requests per second
RPOP: 100200.40 requests per second
SADD: 62150.41 requests per second
HSET: 99009.90 requests per second
SPOP: 104712.05 requests per second
ZADD: 105263.16 requests per second
ZPOPMIN: 110497.24 requests per second
LPUSH (needed to benchmark LRANGE): 74682.60 requests per second
LRANGE_100 (first 100 elements): 62305.30 requests per second
LRANGE_300 (first 300 elements): 8822.23 requests per second
LRANGE_500 (first 450 elements): 22446.69 requests per second
LRANGE_600 (first 600 elements): 17280.11 requests per second
MSET (10 keys): 92081.03 requests per second
```

- Comparing to local Redis server
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

# Run ArceOS-Redis On PC

## Compile and Run

- `make A=apps/c/redis LOG=info NET=y BLK=y PLATFORM=x86_64-pc-oslab APP_FEATURES=use-ramdisk IP=10.2.2.2 GW=10.2.2.1 SMP=4 ARCH=x86_64`
- Copy `redis_x86_64-pc-oslab.elf` to `/boot`, then reboot.
- Enter `grub` then boot the PC by ArceOS Redis.
- `server.c` line 2344 should be changed to `0.0.0.0`
- Connect to ArceOS-Redis server by:
  - `redis-cli -p 5555 -h 10.2.2.2`
  - `redis-benchmark -p 5555 -h 10.2.2.2`

## Other notification

- Comment out `spt_init()`.
