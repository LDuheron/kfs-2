#ifndef GDT_H
#   define GDT_H

#include "stdint.h"

struct  gdt_segment_descriptor_struct {
    short   limit;
    short   base_1;
    char    base_2;
    char    access_byte;
    char    limit_2;
    char    flags;
    char    base_3;
};

#endif
