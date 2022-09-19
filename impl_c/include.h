#ifndef __IMPL_C_INCLUDE__H__
#define __IMPL_C_INCLUDE__H__
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

#ifdef EMBEDDED
    // TODO: 适用于单片机的动态内存分配
#else
    #define MEM_ALLOC(size) malloc(size)
    #define MEM_FREE(ptr) free(ptr)
#endif

#define debug(...) {if (DEBUG)printf(__VA_ARGS__);}

// 头文件汇总
#include "conv2d.h"
#include "dataLoadSave.h"

#endif
