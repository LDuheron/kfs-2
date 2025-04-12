#ifndef GDT_H
#   define GDT_H

#include "stdint.h"

#define ERROR 1
#define SUCCESS 0
#define FLAG 0xCF
#define LIMIT 0xFFFFFFFF

struct  gdt_segment_descriptor_struct {
    short   limit_1;
    short   base_1;
    char    base_2;
    char    access_byte;
    char    limit_2;
    char    flags;
    char    base_3;
};

struct  gdt_ptr_struct {
    short           limit;
    unsigned int    base;
};

#endif
