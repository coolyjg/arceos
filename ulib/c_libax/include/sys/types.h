#ifndef __SYS_TYPES_H__
#define __SYS_TYPES_H__

#include <stddef.h>

#include <stddef.h>
#include <stdint.h>

typedef unsigned mode_t;
typedef uint32_t nlink_t;
typedef int64_t off_t;
typedef uint64_t ino_t;
typedef uint64_t dev_t;
typedef long blksize_t;
typedef int64_t blkcnt_t;

typedef long long int off_t;

typedef unsigned int ino_t;
/**
 * https://stackoverflow.com/questions/15976290/how-to-compare-nlink-t-to-int
 */
typedef unsigned int nlink_t;
typedef int blksize_t;
typedef int blkcnt_t;

// typedef unsigned int __off_t;

#endif // __SYS_TYPES_H__
