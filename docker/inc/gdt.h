#ifndef GDT_H
#   define GDT_H

#include "stdint.h"

#define ERROR 1
#define SUCCESS 0
#define FLAG 0xCF
#define LIMIT 0xFFFFFFFF

#define LOWER_16_BITS(x) ((x) & 0xFFFF)
#define BITS_16_TO_20(x) (((x) >> 16) & 0x0F)
#define BITS_16_TO_24(x) (((x) >> 16) & 0xFF)
#define BITS_24_TO_32(x) (((x) >> 24) & 0xFF)
#define ISOLATE_BITS_4_TO_8(x) ((x) & 0xF0)

#define KERNEL_MODE 0x90
#define USER_MODE 0xF0
#define CODE_MODE 0x0A
#define DATA_MODE 0x02

struct  gdt_segment_descriptor_struct {
    short   limit_1;
    short   base_1;
    char    base_2;
    char    access_byte;
    char    flags;
    char    base_3;
}__attribute__((packed));

struct  gdt_ptr_struct {
    short           limit;
    unsigned int    base;
}__attribute__((packed));

static void initGdt();
static void setGdtEntries(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
#endif
